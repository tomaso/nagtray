#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStandardItemModel>
#include "connection.h"

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
    QStandardItemModel modelHosts;

public slots:
    void connectionRefreshed(Connection *c);

private slots:
    void on_action_Refresh_triggered();
    void on_action_Configuration_triggered();
    void on_action_Quit_triggered();
};

#endif // MAINWINDOW_H
