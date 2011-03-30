#include "host.h"
#include "hostgroup.h"

QHash<QString, class Host *> Host::hostHash;

Host::Host(QObject *parent) :
    QObject(parent)
{
}


Hostgroup::Hostgroup(QObject *parent) :
    QObject(parent)
{
}
