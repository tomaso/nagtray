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
        refreshAfterConnected(false)
{
    Connection::List.append(this);
}


Connection::~Connection()
{
    Connection::List.removeOne(this);
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


void Connection::connected()
{
    isConnected = true;
    if(refreshAfterConnected)
       this->refreshLiveHosts();
    refreshAfterConnected = false;
}


void Connection::disconnected()
{
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
}


void Connection::handleError(QLocalSocket::LocalSocketError error)
{
    switch (error) {
    case QLocalSocket::ServerNotFoundError:
        QMessageBox::information(NULL, tr("Communication error"),
                                 tr("The socket was not found. Please check the "
                                    "socket file exists."));
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
}
