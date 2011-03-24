/********************************************************************************
** Form generated from reading UI file 'editconnection.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONNECTION_H
#define UI_EDITCONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditConnection
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout;
    QRadioButton *remoteRB;
    QLabel *hostL;
    QLineEdit *hostLE;
    QLabel *portL;
    QLineEdit *portLE;
    QCheckBox *sslCB;
    QLabel *pkcsL;
    QLineEdit *pkcsLE;
    QLabel *socketL;
    QRadioButton *localRB;
    QLineEdit *socketLE;
    QLineEdit *nameLE;
    QLabel *nameL;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditConnection)
    {
        if (EditConnection->objectName().isEmpty())
            EditConnection->setObjectName(QString::fromUtf8("EditConnection"));
        EditConnection->resize(400, 300);
        verticalLayout = new QVBoxLayout(EditConnection);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(EditConnection);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        remoteRB = new QRadioButton(frame);
        remoteRB->setObjectName(QString::fromUtf8("remoteRB"));

        gridLayout->addWidget(remoteRB, 2, 0, 1, 2);

        hostL = new QLabel(frame);
        hostL->setObjectName(QString::fromUtf8("hostL"));
        hostL->setEnabled(false);

        gridLayout->addWidget(hostL, 2, 2, 1, 1);

        hostLE = new QLineEdit(frame);
        hostLE->setObjectName(QString::fromUtf8("hostLE"));
        hostLE->setEnabled(false);

        gridLayout->addWidget(hostLE, 2, 3, 1, 1);

        portL = new QLabel(frame);
        portL->setObjectName(QString::fromUtf8("portL"));
        portL->setEnabled(false);

        gridLayout->addWidget(portL, 3, 2, 1, 1);

        portLE = new QLineEdit(frame);
        portLE->setObjectName(QString::fromUtf8("portLE"));
        portLE->setEnabled(false);

        gridLayout->addWidget(portLE, 3, 3, 1, 1);

        sslCB = new QCheckBox(frame);
        sslCB->setObjectName(QString::fromUtf8("sslCB"));

        gridLayout->addWidget(sslCB, 4, 3, 1, 1);

        pkcsL = new QLabel(frame);
        pkcsL->setObjectName(QString::fromUtf8("pkcsL"));
        pkcsL->setEnabled(false);

        gridLayout->addWidget(pkcsL, 5, 1, 1, 2);

        pkcsLE = new QLineEdit(frame);
        pkcsLE->setObjectName(QString::fromUtf8("pkcsLE"));
        pkcsLE->setEnabled(false);

        gridLayout->addWidget(pkcsLE, 5, 3, 1, 1);

        socketL = new QLabel(frame);
        socketL->setObjectName(QString::fromUtf8("socketL"));

        gridLayout->addWidget(socketL, 1, 2, 1, 1);

        localRB = new QRadioButton(frame);
        localRB->setObjectName(QString::fromUtf8("localRB"));
        localRB->setChecked(true);

        gridLayout->addWidget(localRB, 1, 0, 1, 1);

        socketLE = new QLineEdit(frame);
        socketLE->setObjectName(QString::fromUtf8("socketLE"));

        gridLayout->addWidget(socketLE, 1, 3, 1, 1);

        nameLE = new QLineEdit(frame);
        nameLE->setObjectName(QString::fromUtf8("nameLE"));

        gridLayout->addWidget(nameLE, 0, 3, 1, 1);

        nameL = new QLabel(frame);
        nameL->setObjectName(QString::fromUtf8("nameL"));

        gridLayout->addWidget(nameL, 0, 2, 1, 1);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(EditConnection);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        hostL->setBuddy(hostLE);
        portL->setBuddy(portLE);
        pkcsL->setBuddy(pkcsLE);
        socketL->setBuddy(socketLE);
        nameL->setBuddy(nameLE);
#endif // QT_NO_SHORTCUT

        retranslateUi(EditConnection);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditConnection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditConnection, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditConnection);
    } // setupUi

    void retranslateUi(QDialog *EditConnection)
    {
        EditConnection->setWindowTitle(QApplication::translate("EditConnection", "Edit connection", 0, QApplication::UnicodeUTF8));
        remoteRB->setText(QApplication::translate("EditConnection", "&Remote", 0, QApplication::UnicodeUTF8));
        hostL->setText(QApplication::translate("EditConnection", "&Host", 0, QApplication::UnicodeUTF8));
        portL->setText(QApplication::translate("EditConnection", "&Port", 0, QApplication::UnicodeUTF8));
        sslCB->setText(QApplication::translate("EditConnection", "&Use SSL", 0, QApplication::UnicodeUTF8));
        pkcsL->setText(QApplication::translate("EditConnection", "p&kcs12 file", 0, QApplication::UnicodeUTF8));
        socketL->setText(QApplication::translate("EditConnection", "&Socket", 0, QApplication::UnicodeUTF8));
        localRB->setText(QApplication::translate("EditConnection", "&Local", 0, QApplication::UnicodeUTF8));
        socketLE->setText(QString());
        nameLE->setText(QString());
        nameL->setText(QApplication::translate("EditConnection", "&Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditConnection: public Ui_EditConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONNECTION_H
