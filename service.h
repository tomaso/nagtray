#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QHash>

/*! \brief Service represents one service retrieved from livestatus
 */
class Service : public QObject
{
Q_OBJECT
public:
    explicit Service(QObject *parent = 0);

    //! Dictionary of attributes from livestatus
    QHash<QString, QString> attributes;

protected:


signals:

public slots:

};

#endif // SERVICE_H
