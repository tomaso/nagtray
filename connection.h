#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QList>
//#include <QMap>
#include <QList>
#include <QLocalSocket>
#include "host.h"

#define MYPROP(type, name, upname) \
    type name() { return _##name; } \
    void set##upname(type name) { _##name = name; }

typedef enum { RT_NONE, RT_HOSTS, RT_SERVICES } tRequest;

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
    tRequest reqType;           //!< Type of the processed request


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

    QList<Host *> liveHosts;

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


signals:
    void liveHostsRefreshed(Connection *);
    void liveServicesRefreshed(Connection *);


public slots:
    void connected();
    void disconnected();
    void handleError(QLocalSocket::LocalSocketError);
    void readData();
};

#endif // CONNECTION_H
