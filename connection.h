#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QList>

#define MYPROP(type, name, upname) \
    type name() { return _##name; } \
    void set##upname(type name) { _##name = name; }

/*! \brief Represents connection to a livestatus daemon.
 *
 */
class Connection {
protected:
    QString _name;           //!< Name of this connection
    bool _local;             //!< Otherwise remote
    QString _socket;         //!< Path to the unix socket of livestatus
    QString _host;
    unsigned int _port;
    bool _useSSL;
    QString _pkcs12;

public:
    Connection();
    ~Connection();

    MYPROP(QString, name, Name);
    MYPROP(bool, local, Local);
    MYPROP(QString, socket, Socket);
    MYPROP(QString, host, Host);
    MYPROP(int, port, Port);
    MYPROP(bool, useSSL, UseSSL);
    MYPROP(QString, pkcs12, Pkcs12);

    static QList<Connection *> List;
};

#endif // CONNECTION_H
