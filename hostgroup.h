#ifndef HOSTGROUP_H
#define HOSTGROUP_H

#include <QObject>
#include <QHash>

/*! \brief Hostgroup represents a hostgroup entity from nagios.
 *
 * One host can be in multiple groups.
 */
class Hostgroup : public QObject
{
Q_OBJECT
public:
    explicit Hostgroup(QObject *parent = 0);

    //! Dictionary of attributes from livestatus
    QHash<QString, QString> attributes;

protected:


signals:

public slots:

};



#endif // HOSTGROUP_H
