#include <QtXml/QDomDocument>
#include <QFile>
#include <QMessageBox>
#include "connection.h"
#include "globalconfig.h"


Request::Request(tRequestType _type) : type(_type), id(0)
{
    //pass
}


Request::Request(tRequestType _type, int _id) : type(_type), id(_id)
{
    //pass
}


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
    dataRefreshPending(false)
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
        bytesWritten = ls->write("GET hostgroups\nKeepAlive: on\nResponseHeader: fixed16\nSeparators: "
                                 DATASET_SEPARATOR_STRING
                                 " "
                                 FIELD_SEPARATOR_STRING
                                 " "
                                 LIST_SEPARATOR_STRING
                                 " "
                                 HOST_SERVICE_SEPARATOR_STRING
                                 "\n\n");
        qDebug("bytesWritten: %d", bytesWritten);
        reqQueue.append(Request(RT_HOSTGROUPS, 0));

        bytesWritten = ls->write("GET hosts\nKeepAlive: on\nResponseHeader: fixed16\nSeparators: "
                                 DATASET_SEPARATOR_STRING
                                 " "
                                 FIELD_SEPARATOR_STRING
                                 " "
                                 LIST_SEPARATOR_STRING
                                 " "
                                 HOST_SERVICE_SEPARATOR_STRING
                                 "\n\n");
        qDebug("bytesWritten: %d", bytesWritten);
        reqQueue.append(Request(RT_HOSTS, 0));

        bytesWritten = ls->write("GET services\nKeepAlive: on\nResponseHeader: fixed16\nSeparators: "
                                 DATASET_SEPARATOR_STRING
                                 " "
                                 FIELD_SEPARATOR_STRING
                                 " "
                                 LIST_SEPARATOR_STRING
                                 " "
                                 HOST_SERVICE_SEPARATOR_STRING
                                 "\n\n");
        qDebug("bytesWritten: %d", bytesWritten);
        reqQueue.append(Request(RT_SERVICES, 0));

        readingHeader = true;
        headerBuffer.clear();
    } else {
        connect(ls, SIGNAL(connected()), this, SLOT(connected()));
        connect(ls, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(ls, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(handleError(QLocalSocket::LocalSocketError)));
        connect(ls, SIGNAL(readyRead()), this, SLOT(readData()));
        dataRefreshPending = true;
        ls->connectToServer(this->socket());
    }
}


void Connection::disconnected()
{
    // pretty much nothing right now
}


void Connection::connected()
{
    if(dataRefreshPending)
        this->liveRefreshData();
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
    do {
        if(readingHeader) {
            headerBuffer.append(ls->readLine());
            if(headerBuffer.length()==16) {
                readingHeader = false;
                QStringList headerList = headerBuffer.split(" ", QString::SkipEmptyParts);
                responseCode = headerList.at(0).toInt();
                qDebug("response code: %d", responseCode);
                dataLength = headerList.at(1).toInt();
                headerBuffer.clear();
            } else {
                // wait for another data from header
                return;
            }
        }

        readBuffer.append(ls->read(dataLength-readBuffer.length()));
        if(readBuffer.length()!=dataLength) {
            // wait for another data from data body
            return;
        } else {
            readingHeader = true;
        }

        //   qDebug("READ: %s", readBuffer.toAscii().constData());
        Request &req = reqQueue.front();
        switch(req.type) {
        case RT_HOSTGROUPS:
            parseBufferHostgroups();
            break;

        case RT_HOSTS:
            parseBufferHosts();
            break;

        case RT_SERVICES:
            parseBufferServices();
            break;

        default:
            break;
        }
        reqQueue.pop_front();
    } while(ls->bytesAvailable()>0);
}


void Connection::parseBufferHostgroups()
{
    for(int i=0;i<liveHostgroups.size();i++)
        delete liveHostgroups[i];
    liveHostgroups.clear();

    QStringList lines = readBuffer.split("\n");
    QStringList keys = lines[0].split(FIELD_SEPARATOR_CHAR);
    for(int i=1;i<lines.size();i++) {
        QStringList values = lines[i].split(FIELD_SEPARATOR_CHAR);
        if(keys.size() != values.size())
            continue;
        Hostgroup *newhostgroup = new Hostgroup;
        for(int j=0;j<keys.size();j++) {
            newhostgroup->attributes.insert(keys[j], values[j]);
        }
        liveHostgroups.append(newhostgroup);
    }
    readBuffer.clear();
    emit liveHostgroupsRefreshed(this);
}


void Connection::parseBufferHosts()
{
    for(int i=0;i<liveHosts.size();i++)
        delete liveHosts[i];
    liveHosts.clear();

    // TODO: this parsing should be replaced with json (livestatus can return json data)
    // TODO: beware of host status checkers (e.g. check_ipmi) when they produce multiline output
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
    readBuffer.clear();
    emit liveHostsRefreshed(this);
}


void Connection::parseBufferServices()
{
    for(int i=0;i<liveServices.size();i++)
        delete liveServices[i];
    liveServices.clear();

    QStringList lines = readBuffer.split("\n");
    QStringList keys = lines[0].split(FIELD_SEPARATOR_CHAR);
    for(int i=1;i<lines.size();i++) {
        QStringList values = lines[i].split(FIELD_SEPARATOR_CHAR);
        if(keys.size() != values.size())
            continue;
        Service *newservice = new Service;
        for(int j=0;j<keys.size();j++) {
            newservice->attributes.insert(keys[j], values[j]);
        }
        liveServices.append(newservice);
    }
    readBuffer.clear();
    emit liveServicesRefreshed(this);
}
