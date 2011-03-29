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

    ui->hostgroupView->setModel(&this->modelHostgroups);
    ui->hostView->setModel(&this->modelHosts);
    ui->serviceView->setModel(&this->modelServices);

    Connection *c;
    foreach(c, Connection::List) {
        connect(c, SIGNAL(liveHostgroupsRefreshed(Connection*)), this, SLOT(hostgroupsRefreshed(Connection*)));
        connect(c, SIGNAL(liveHostsRefreshed(Connection*)), this, SLOT(hostsRefreshed(Connection*)));
        connect(c, SIGNAL(liveServicesRefreshed(Connection*)), this, SLOT(servicesRefreshed(Connection*)));
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


void MainWindow::hostgroupsRefreshed(Connection *c)
{
    Hostgroup *lhg;
    QStandardItem *newitem;

    foreach (lhg, c->liveHostgroups) {
        newitem = new QStandardItem(lhg->attributes.value("alias"));
        newitem->setEditable(false);
        modelHostgroups.appendRow(newitem);
    }
}


void MainWindow::hostsRefreshed(Connection *c)
{
    Host *lh;
    QList<QStandardItem *> row;

    modelHosts.insertColumns(0,2);
    modelHosts.setHeaderData(0,Qt::Horizontal,QString("hostname"));
    modelHosts.setHeaderData(0,Qt::Horizontal,QString("status"));

    foreach (lh, c->liveHosts) {
        row.append(new QStandardItem(lh->attributes.value("name")));
        row.append(new QStandardItem(lh->attributes.value("last_hard_state")));
        modelHosts.appendRow(row);
        row.clear();
    }
}


void MainWindow::servicesRefreshed(Connection *c)
{
    Service *ls;
    QStandardItem *newitem;

    foreach (ls, c->liveServices) {
        newitem = new QStandardItem(QString("%1 - %2").arg(ls->attributes.value("host_display_name")).arg(ls->attributes.value("display_name")));
        newitem->setEditable(false);
        modelServices.appendRow(newitem);
    }
}
