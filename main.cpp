#include <QtGui/QApplication>
#include <QtGui>
#include "mainwindow.h"
#include "connection.h"
#include "globalconfig.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(nagtray);
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    //Commented out for debugging
    //QApplication::setQuitOnLastWindowClosed(false);

    if(!Connection::LoadListFromXML(CONNECTIONS_FILE)) {
        QMessageBox::critical(NULL, QApplication::tr("Starting error"),
                              QApplication::tr("Cannot load saved connections - will start with empty list.")
                              );
    }

    MainWindow w;
    w.show();
    return a.exec();
}
