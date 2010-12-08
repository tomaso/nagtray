#include "connection.h"

QList<Connection *> Connection::List;

Connection::Connection() :
        _name("New connection"),
        _local(true),
        _socket("/var/lib/nagios/rw/live")
{
    Connection::List.append(this);
}

Connection::~Connection()
{
    Connection::List.removeOne(this);
}

