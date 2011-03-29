/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionShowMain;
    QAction *actionShowConfiguration;
    QAction *action_Refresh;
    QAction *action_Quit;
    QAction *action_About;
    QAction *action_Configuration;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QTreeView *hostgroupView;
    QWidget *tabHosts;
    QVBoxLayout *verticalLayout_3;
    QTreeView *hostView;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTreeView *serviceView;
    QMenuBar *menuBar;
    QMenu *menu_Help;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(433, 350);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/error.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionShowMain = new QAction(MainWindow);
        actionShowMain->setObjectName(QString::fromUtf8("actionShowMain"));
        actionShowConfiguration = new QAction(MainWindow);
        actionShowConfiguration->setObjectName(QString::fromUtf8("actionShowConfiguration"));
        action_Refresh = new QAction(MainWindow);
        action_Refresh->setObjectName(QString::fromUtf8("action_Refresh"));
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_Configuration = new QAction(MainWindow);
        action_Configuration->setObjectName(QString::fromUtf8("action_Configuration"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        hostgroupView = new QTreeView(tab_2);
        hostgroupView->setObjectName(QString::fromUtf8("hostgroupView"));

        verticalLayout_4->addWidget(hostgroupView);

        tabWidget->addTab(tab_2, QString());
        tabHosts = new QWidget();
        tabHosts->setObjectName(QString::fromUtf8("tabHosts"));
        verticalLayout_3 = new QVBoxLayout(tabHosts);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        hostView = new QTreeView(tabHosts);
        hostView->setObjectName(QString::fromUtf8("hostView"));

        verticalLayout_3->addWidget(hostView);

        tabWidget->addTab(tabHosts, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        serviceView = new QTreeView(tab);
        serviceView->setObjectName(QString::fromUtf8("serviceView"));

        verticalLayout_2->addWidget(serviceView);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 433, 19));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Help->addAction(action_About);
        menu_File->addAction(action_Refresh);
        menu_File->addSeparator();
        menu_File->addAction(action_Configuration);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Refresh);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Nagtray", 0, QApplication::UnicodeUTF8));
        actionShowMain->setText(QApplication::translate("MainWindow", "ShowMain", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowMain->setToolTip(QApplication::translate("MainWindow", "Show main window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShowConfiguration->setText(QApplication::translate("MainWindow", "ShowConfiguration", 0, QApplication::UnicodeUTF8));
        action_Refresh->setText(QApplication::translate("MainWindow", "&Refresh", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        action_Configuration->setText(QApplication::translate("MainWindow", "&Configuration", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Hostgroups", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabHosts), QApplication::translate("MainWindow", "Hosts", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Services", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
