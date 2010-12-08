#include "ui_editconnection.h"
#include "editconnection.h"


EditConnection::EditConnection(Connection *conn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditConnection)
{
    ui->setupUi(this);
    connection = conn;
    ui->nameLE->setText(connection->name());
    if(connection->local()) {
        ui->localRB->setChecked(true);
        ui->remoteRB->setChecked(false);
        ui->socketLE->setText(connection->socket());
    } else {
        ui->localRB->setChecked(false);
        ui->remoteRB->setChecked(true);
    }
}

EditConnection::~EditConnection()
{
    delete ui;
}

void EditConnection::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void EditConnection::on_buttonBox_accepted()
{
    qDebug("edit conneciton accepted");
    connection->setName(ui->nameLE->text());
    connection->setSocket(ui->socketLE->text());
}

void EditConnection::on_buttonBox_rejected()
{
    qDebug("edit conneciton rejected");
}
