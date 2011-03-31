#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStandardItemModel>
#include "connection.h"
#include "labeldelegate.h"

class QMenu;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;
    QStandardItemModel modelHostgroups;
    QStandardItemModel modelHosts;
    QStandardItemModel modelServices;

    LabelDelegate *hostsDelegate;

public slots:
    void hostgroupsRefreshed(Connection *c);
    void hostsRefreshed(Connection *c);
    void servicesRefreshed(Connection *c);

private slots:
    void on_action_Refresh_triggered();
    void on_action_Configuration_triggered();
    void on_action_Quit_triggered();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWINDOW_H
