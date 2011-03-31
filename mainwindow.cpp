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

    hostsDelegate = new LabelDelegate;

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
    ui->hostView->setItemDelegateForColumn(1,hostsDelegate);
    ui->serviceView->setModel(&this->modelServices);

    Connection *c;
    foreach(c, Connection::List) {
        connect(c, SIGNAL(liveHostgroupsRefreshed(Connection*)), this, SLOT(hostgroupsRefreshed(Connection*)));
        connect(c, SIGNAL(liveHostsRefreshed(Connection*)), this, SLOT(hostsRefreshed(Connection*)));
        connect(c, SIGNAL(liveServicesRefreshed(Connection*)), this, SLOT(servicesRefreshed(Connection*)));
    }
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

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
    int i;
    QString hostname;
    QStandardItem *newitem;

    ui->hostView->header()->setResizeMode(QHeaderView::ResizeToContents);
    modelHosts.insertColumns(0,2);
    modelHosts.setHeaderData(0,Qt::Horizontal,QString("hostname"));
    modelHosts.setHeaderData(1,Qt::Horizontal,QString("status"));

    i=0;
    modelHosts.insertRows(0,c->liveHosts.length());
    foreach (lh, c->liveHosts) {    
        hostname = lh->attributes.value("name");
        Host::hostHash.insert(hostname, lh);
        modelHosts.setData(modelHosts.index(i, 0), hostname);

        int state=lh->attributes.value("last_hard_state").toInt();
        if(state)
            modelHosts.setData(modelHosts.index(i, 1), QString("<font style='color: #f30'>%1</font>").arg(state));
        else
            modelHosts.setData(modelHosts.index(i, 1), QString("%1").arg(state));
        lh->host_index = modelHosts.index(i,0);
        i++;
    }

    // Link services under hosts if available
    Service *ls;
    foreach (ls, c->liveServices) {
        hostname = ls->attributes.value("host_display_name");
        if(Host::hostHash.contains(hostname)) {
            lh = Host::hostHash.value(hostname);
            newitem = new QStandardItem(QString("%1").arg(ls->attributes.value("display_name")));
            newitem->setEditable(false);
            modelHosts.itemFromIndex(lh->host_index)->insertRow(0, newitem);
        }
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

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        trayIcon->showMessage("Head", "Body", QSystemTrayIcon::Information, 3000);

        break;
    case QSystemTrayIcon::DoubleClick:
        //TODO: show main window
        break;
    default:
        ;
    }
}
