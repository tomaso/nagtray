#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QHash>
#include <QModelIndex>

/*! \brief Host represents one host retrieved from livestatus
 */
class Host : public QObject
{
Q_OBJECT
public:
    explicit Host(QObject *parent = 0);

    //! Dictionary of attributes from livestatus
    QHash<QString, QString> attributes;

    QModelIndex host_index;

    static QHash<QString, class Host *> hostHash;

protected:


signals:

public slots:

};


/*! \brief Hashtable of all hosts identified by their hostname
 */

#endif // HOST_H
