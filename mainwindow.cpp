#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "connection.h"
#include "globalconfig.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionShowMain);
    trayIconMenu->addAction(ui->actionShowConfiguration);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->action_Quit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/error.svg"));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    ui->hostView->setModel(&this->modelHosts);

    Connection *c;
    foreach(c, Connection::List) {
        connect(c, SIGNAL(liveHostsRefreshed(Connection*)), this, SLOT(connectionRefreshed(Connection*)));
        //connect(c, SIGNAL(liveServicesRefreshed(Connection*)), this, SLOT(connectionRefreshed(Connection*)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_action_Quit_triggered()
{
    qApp->quit();
}

void MainWindow::on_action_Configuration_triggered()
{
    ConfigWindow cw;
    cw.exec();
}

void MainWindow::on_action_Refresh_triggered()
{
    Connection *c;

    foreach (c, Connection::List) {
        c->liveRefreshData();
    }
}

void MainWindow::connectionRefreshed(Connection *c)
{
    Host *lh;
    QStandardItem *newitem;

    foreach (lh, c->liveHosts) {
        newitem = new QStandardItem(lh->attributes.value(LIVESTATUS_HOST_KEY));
        newitem->setEditable(false);
        modelHosts.appendRow(newitem);
    }
}
