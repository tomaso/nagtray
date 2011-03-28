#include <QtXml/QDomDocument>
#include <QFile>
#include <QMessageBox>
#include "connection.h"
#include "globalconfig.h"

QList<Connection *> Connection::List;

bool Connection::LoadListFromXML(QString filename)
{
    QDomDocument domDocument;
    QFile f(filename);
    QByteArray content;
    QString errorMsg;
    int errorLine;

    if(!f.open(QIODevice::ReadOnly|QIODevice::Text)) {
        qCritical("Cannot open file %s.", filename.toAscii().data());
        return false;
    }
    if(!domDocument.setContent(&f, &errorMsg, &errorLine, NULL)) {
        qCritical("Cannot parse file %s, error '%s' on line %d.",
                  filename.toAscii().data(), errorMsg.toAscii().data(), errorLine);
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "connections") {
        qCritical("Root element is not 'connections' - the file with connections is probably corrupted.");
        return false;
    }

    Connection *con;
    QDomElement child = root.firstChildElement("connection");
    while (!child.isNull()) {
        if(!child.hasAttribute("name")) {
            qCritical("Attribute 'name' is mandatory.");
            return false;
        }
        con = new Connection();
        con->setName(child.attribute("name"));
        con->setLocal(child.attribute("local", "yes")=="yes");
        con->setSocket(child.attribute("socket"));
        con->setHost(child.attribute("host"));
        con->setPort(child.attribute("port").toInt());
        con->setUseSSL(child.attribute("useSSL", "no")=="yes");
        con->setPkcs12(child.attribute("pkcs12"));

        child = child.nextSiblingElement("connection");
    }

    return true;
}


Connection::Connection() :
        _enabled(true),
        _name("New connection"),
        _local(true),
        _socket("/var/lib/nagios/rw/live"),
        isConnected(false),
        refreshAfterConnected(false),
        dataRefreshPending(false),
        reqType(RT_NONE)
{
    Connection::List.append(this);
    ls = new QLocalSocket();
}


Connection::~Connection()
{
    delete ls;
    Connection::List.removeOne(this);
}


void Connection::liveRefreshData()
{
    if(ls->state()==QLocalSocket::ConnectedState) {
        int bytesWritten;
        bytesWritten = ls->write("GET hosts\nKeepAlive: on\nSeparators: "
                                 DATASET_SEPARATOR_STRING
                                 " "
                                 FIELD_SEPARATOR_STRING
                                 " "
                                 LIST_SEPARATOR_STRING
                                 " "
                                 HOST_SERVICE_SEPARATOR_STRING
                                 "\n\n");
        qDebug("bytesWritten: %d", bytesWritten);
        reqType = RT_HOSTS;
    } else {
        connect(ls, SIGNAL(connected()), this, SLOT(connected()));
        connect(ls, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(ls, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(handleError(QLocalSocket::LocalSocketError)));
        connect(ls, SIGNAL(readyRead()), this, SLOT(readData()));
        ls->connectToServer(this->socket());
        dataRefreshPending = true;
    }
}

void Connection::disconnected()
{
    // pretty much nothing right now
/*
    int i,j;

    for(i=0;i<liveHosts.size();i++) {
        delete liveHosts[i];
    }
    liveHosts.clear();
    if(!readBuffer.isEmpty()) {
        // TODO: this parsing should be replaced with json (livestatus can return json data)
        QStringList lines = readBuffer.split("\n");
        QStringList keys = lines[0].split(FIELD_SEPARATOR_CHAR);
        for(i=1;i<lines.size();i++) {
            QStringList values = lines[i].split(FIELD_SEPARATOR_CHAR);
            if(keys.size() != values.size())
                continue;
            Host *newhost = new Host;
            for(j=0;j<keys.size();j++) {
                newhost->attributes.insert(keys[j], values[j]);
            }
            liveHosts.append(newhost);
        }
    }
    emit liveHostsRefreshed(this);
    isConnected = false;
    readBuffer.clear();
*/
}



void Connection::connected()
{
    if(dataRefreshPending)
        this->liveRefreshData();
}




bool Connection::refreshLiveHosts()
{
//    QIODevice *d;

    if(isConnected) {
        if(local()) {
            int bytesWritten;
            bytesWritten = ls->write("GET hosts\nSeparators: "
                                     DATASET_SEPARATOR_STRING
                                     " "
                                     FIELD_SEPARATOR_STRING
                                     " "
                                     LIST_SEPARATOR_STRING
                                     " "
                                     HOST_SERVICE_SEPARATOR_STRING
                                     "\n\n");
            qDebug("bytesWritten: %d", bytesWritten);
        } else {
            // tcp connection
        }
    } else {
        refreshAfterConnected = true;

        if(local()) {
            ls = new QLocalSocket();
            if(ls == NULL)
                return false;
            connect(ls, SIGNAL(connected()), this, SLOT(connected()));
            connect(ls, SIGNAL(disconnected()), this, SLOT(disconnected()));
            connect(ls, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(handleError(QLocalSocket::LocalSocketError)));
            connect(ls, SIGNAL(readyRead()), this, SLOT(readData()));
            ls->abort();
            ls->connectToServer(socket());
        } else {
            // tcp connection
        }
    }
    return true;
}




void Connection::handleError(QLocalSocket::LocalSocketError error)
{
    switch (error) {
    case QLocalSocket::ServerNotFoundError:
        QMessageBox::information(NULL, tr("Communication error"),
                                 tr("The socket was not found. Please check the "
                                    "socket file exists: %1").arg(this->socket())
                                 );
        break;
    case QLocalSocket::ConnectionRefusedError:
        QMessageBox::information(NULL, tr("Communication error"),
                                 tr("The connection was refused by the socket. "
                                    "Make sure the socket file exists and its "
                                    "permissions are correct."));
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        QMessageBox::information(NULL, tr("Communication error"),
                                 tr("The following error occurred: %1.").arg(ls->errorString())
                                 );
    }
}


void Connection::readData()
{
    readBuffer.append(ls->readAll());
    qDebug("READ: %s", readBuffer.toAscii().constData());
    switch(reqType) {
    case RT_HOSTS:
        for(int i=0;i<liveHosts.size();i++) {
            delete liveHosts[i];
        }
        liveHosts.clear();
        if(!readBuffer.isEmpty()) {
            // TODO: this parsing should be replaced with json (livestatus can return json data)
            QStringList lines = readBuffer.split("\n");
            QStringList keys = lines[0].split(FIELD_SEPARATOR_CHAR);
            for(int i=1;i<lines.size();i++) {
                QStringList values = lines[i].split(FIELD_SEPARATOR_CHAR);
                if(keys.size() != values.size())
                    continue;
                Host *newhost = new Host;
                for(int j=0;j<keys.size();j++) {
                    newhost->attributes.insert(keys[j], values[j]);
                }
                liveHosts.append(newhost);
            }
        }
        readBuffer.clear();
        emit liveHostsRefreshed(this);
        break;
    default:
        break;
    }
}
