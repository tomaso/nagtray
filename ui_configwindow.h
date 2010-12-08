/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWindow
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *connectionTab;
    QHBoxLayout *horizontalLayout;
    QListView *listView;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *enableButton;
    QPushButton *disableButton;
    QSpacerItem *verticalSpacer;
    QWidget *alertStyleTab;
    QWidget *filteringTab;

    void setupUi(QDialog *ConfigWindow)
    {
        if (ConfigWindow->objectName().isEmpty())
            ConfigWindow->setObjectName(QString::fromUtf8("ConfigWindow"));
        ConfigWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(ConfigWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(ConfigWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        connectionTab = new QWidget();
        connectionTab->setObjectName(QString::fromUtf8("connectionTab"));
        horizontalLayout = new QHBoxLayout(connectionTab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listView = new QListView(connectionTab);
        listView->setObjectName(QString::fromUtf8("listView"));

        horizontalLayout->addWidget(listView);

        frame = new QFrame(connectionTab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        addButton = new QPushButton(frame);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout_2->addWidget(addButton);

        editButton = new QPushButton(frame);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        verticalLayout_2->addWidget(editButton);

        removeButton = new QPushButton(frame);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout_2->addWidget(removeButton);

        enableButton = new QPushButton(frame);
        enableButton->setObjectName(QString::fromUtf8("enableButton"));

        verticalLayout_2->addWidget(enableButton);

        disableButton = new QPushButton(frame);
        disableButton->setObjectName(QString::fromUtf8("disableButton"));

        verticalLayout_2->addWidget(disableButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame);

        tabWidget->addTab(connectionTab, QString());
        alertStyleTab = new QWidget();
        alertStyleTab->setObjectName(QString::fromUtf8("alertStyleTab"));
        tabWidget->addTab(alertStyleTab, QString());
        filteringTab = new QWidget();
        filteringTab->setObjectName(QString::fromUtf8("filteringTab"));
        tabWidget->addTab(filteringTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ConfigWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConfigWindow);
    } // setupUi

    void retranslateUi(QDialog *ConfigWindow)
    {
        ConfigWindow->setWindowTitle(QApplication::translate("ConfigWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("ConfigWindow", "&Add", 0, QApplication::UnicodeUTF8));
        editButton->setText(QApplication::translate("ConfigWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("ConfigWindow", "&Remove", 0, QApplication::UnicodeUTF8));
        enableButton->setText(QApplication::translate("ConfigWindow", "E&nable", 0, QApplication::UnicodeUTF8));
        disableButton->setText(QApplication::translate("ConfigWindow", "&Disable", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(connectionTab), QApplication::translate("ConfigWindow", "Connection", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(alertStyleTab), QApplication::translate("ConfigWindow", "Alerting", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(filteringTab), QApplication::translate("ConfigWindow", "Filtering", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigWindow: public Ui_ConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
