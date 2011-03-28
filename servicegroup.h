#ifndef SERVICEGROUP_H
#define SERVICEGROUP_H

#include <QObject>
#include <QHash>

/*! \brief Servicegroup represents a servicegroup entity from nagios.
 *
 * One service can be in multiple groups.
 */
class Servicegroup : public QObject
{
Q_OBJECT
public:
    explicit Servicegroup(QObject *parent = 0);

    //! Dictionary of attributes from livestatus
    QHash<QString, QString> attributes;

protected:


signals:

public slots:

};



#endif // SERVICEGROUP_H
