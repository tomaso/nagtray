#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QList>
//#include <QMap>
#include <QList>
#include <QLocalSocket>
#include "hostgroup.h"
#include "servicegroup.h"
#include "host.h"
#include "service.h"

#define MYPROP(type, name, upname) \
    type name() { return _##name; } \
    void set##upname(type name) { _##name = name; }

#define RESPONSE_CODE_OK                 200
#define RESPONSE_CODE_INVALID_HEADER     400
#define RESPONSE_CODE_UNAUTHORIZED       403
#define RESPONSE_CODE_NOT_FOUND          404
#define RESPONSE_CODE_INCOMPLETE_REQUEST 451
#define RESPONSE_CODE_INVALID_REQUEST    452
#define RESPONSE_CODE_UNKNOWN_COLUMN     450


typedef enum { RT_HOSTGROUPS, RT_HOSTS, RT_SERVICES, RT_HOSTGROUP, RT_HOST, RT_SERVICE } tRequestType;

/*! \brief Request for data that is issued to the livestatus connection
 *
 */
class Request {
public:
    tRequestType type;   //!< Type of the request
    int id;                                                     //!< Id of the host or service that should be refreshed
public:
    Request(tRequestType _type);
    Request(tRequestType _type, int _id);
};

/*! \brief Represents connection to a livestatus daemon.
 *
 */
class Connection : public QObject {
Q_OBJECT
protected:
    bool _enabled;
    QString _name;           //!< Name of this connection
    bool _local;             //!< Otherwise remote
    QString _socket;         //!< Path to the unix socket of livestatus
    QString _host;
    unsigned int _port;
    bool _useSSL;
    QString _pkcs12;
    QString _password;       //!< Password for the pkcs key, not saved

    bool isConnected;
    bool refreshAfterConnected;
    QLocalSocket *ls;
    QString readBuffer;
    // This might be a queue of requests in the future
    bool dataRefreshPending;    //!< Should we update data when the connection is established?
    QList<Request> reqQueue;           //!< Type of the processed request

    bool readingHeader;         //!< Reading header (true) or data body (false)
    QString headerBuffer;
    int responseCode;
    int dataLength;

public:
    Connection();
    ~Connection();

    MYPROP(bool, enabled, Enabled);
    MYPROP(QString, name, Name);
    MYPROP(bool, local, Local);
    MYPROP(QString, socket, Socket);
    MYPROP(QString, host, Host);
    MYPROP(int, port, Port);
    MYPROP(bool, useSSL, UseSSL);
    MYPROP(QString, pkcs12, Pkcs12);
    MYPROP(QString, password, Password);

    QList<Hostgroup *> liveHostgroups;
    QList<Host *> liveHosts;
    QList<Service *> liveServices;

    //! Connects to the host and get info about the hosts
    bool refreshLiveHosts();

    //! List of all connections
    static QList<Connection *> List;

    /*! \brief Loads all connections from XML file
     * \return true/false If the loading was successful.
     */
    static bool LoadListFromXML(QString filename);

    /*! \brief Instruct connection to refresh overview data.
     *  Emits FIXME when new data is available.
     */
    void liveRefreshData();

    void parseBufferHostgroups();
    void parseBufferHosts();
    void parseBufferServices();

signals:
    void liveHostgroupsRefreshed(Connection *);
    void liveHostsRefreshed(Connection *);
    void liveServicesRefreshed(Connection *);

public slots:
    void connected();
    void disconnected();
    void handleError(QLocalSocket::LocalSocketError);
    void readData();
};

#endif // CONNECTION_H
