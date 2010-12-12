#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QHash>

/*! \brief Host represents one host retrieved from livestatus
 */
class Host : public QObject
{
Q_OBJECT
public:
    explicit Host(QObject *parent = 0);

    //! Dictionary of attributes from livestatus
    QHash<QString, QString> attributes;

protected:


signals:

public slots:

};

#endif // HOST_H
