#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

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


private slots:
    void on_action_Quit_triggered();
    void on_actionQuit_triggered();
};

#endif // MAINWINDOW_H
