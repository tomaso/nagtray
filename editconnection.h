#ifndef EDITCONNECTION_H
#define EDITCONNECTION_H

#include <QDialog>
#include "connection.h"


namespace Ui {
    class EditConnection;
}

class EditConnection : public QDialog {
    Q_OBJECT
public:
    EditConnection(Connection *conn, QWidget *parent = 0);
    ~EditConnection();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EditConnection *ui;
    Connection *connection;

private slots:


private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_sslCB_clicked();
    void on_localRB_clicked();
    void on_remoteRB_clicked();
};


#endif // EDITCONNECTION_H
