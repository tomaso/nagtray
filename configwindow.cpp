#include "ui_configwindow.h"
#include "configwindow.h"
#include "connection.h"
#include "editconnection.h"


ConfigWindow::ConfigWindow(QWidget *parent) : 
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    ui->listView->setModel(&this->modelConnections);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::changeEvent(QEvent *e)
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

void ConfigWindow::on_addButton_clicked()
{
    QStandardItem *newitem;
    Connection *newconnection = new Connection();
    EditConnection ec(newconnection);
    if(ec.exec() == QDialog::Accepted) {
        newitem = new QStandardItem(newconnection->name());
        modelConnections.appendRow(newitem);
    } else {
        delete newconnection;
    }
}

void ConfigWindow::on_editButton_clicked()
{
    QModelIndex current = ui->listView->currentIndex();
    int c = current.row();
    if (c==-1 || c>=Connection::List.size())
        return;
    Connection *con = Connection::List.at(current.row());
    EditConnection ec(con);
    ec.exec();
    modelConnections.item(c)->setText(con->name());
}

void ConfigWindow::on_removeButton_clicked()
{
    QModelIndex current = ui->listView->currentIndex();
    int c = current.row();
    if (c==-1 || c>=Connection::List.size())
        return;
    Connection *con = Connection::List.at(c);
    modelConnections.removeRow(current.row());
    delete(con);
}