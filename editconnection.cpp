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
        ui->hostLE->setText(connection->host());
        ui->portLE->setText(QString(connection->port()));
        ui->sslCB->setChecked(connection->useSSL());
        if(connection->useSSL())
            ui->pkcsLE->setText(connection->pkcs12());
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
    connection->setName(ui->nameLE->text());
    connection->setLocal(ui->localRB->isChecked());
    connection->setSocket(ui->socketLE->text());
    connection->setHost(ui->hostLE->text());
    connection->setPort(ui->portLE->text().toInt());
    connection->setUseSSL(ui->sslCB->isChecked());
    connection->setPkcs12(ui->pkcsLE->text());
}

void EditConnection::on_buttonBox_rejected()
{
}

void EditConnection::on_sslCB_clicked()
{
    ui->pkcsLE->setEnabled(ui->sslCB->isChecked());
}

void EditConnection::on_localRB_clicked()
{
    ui->socketL->setEnabled(ui->localRB->isChecked());
    ui->socketLE->setEnabled(ui->localRB->isChecked());
    ui->hostL->setEnabled(ui->remoteRB->isChecked());
    ui->hostLE->setEnabled(ui->remoteRB->isChecked());
    ui->portL->setEnabled(ui->remoteRB->isChecked());
    ui->portLE->setEnabled(ui->remoteRB->isChecked());
}

void EditConnection::on_remoteRB_clicked()
{
    this->on_localRB_clicked();
}
