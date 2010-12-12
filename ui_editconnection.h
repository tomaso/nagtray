/********************************************************************************
** Form generated from reading UI file 'editconnection.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.6.3
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
    QLabel *label_2;
    QLineEdit *hostLE;
    QLabel *label_3;
    QLineEdit *portLE;
    QCheckBox *sslCB;
    QLabel *label_4;
    QLineEdit *pkcsLE;
    QLabel *label;
    QRadioButton *localRB;
    QLineEdit *socketLE;
    QLineEdit *nameLE;
    QLabel *label_5;
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

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        hostLE = new QLineEdit(frame);
        hostLE->setObjectName(QString::fromUtf8("hostLE"));

        gridLayout->addWidget(hostLE, 2, 3, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 2, 1, 1);

        portLE = new QLineEdit(frame);
        portLE->setObjectName(QString::fromUtf8("portLE"));

        gridLayout->addWidget(portLE, 3, 3, 1, 1);

        sslCB = new QCheckBox(frame);
        sslCB->setObjectName(QString::fromUtf8("sslCB"));

        gridLayout->addWidget(sslCB, 4, 3, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 1, 1, 2);

        pkcsLE = new QLineEdit(frame);
        pkcsLE->setObjectName(QString::fromUtf8("pkcsLE"));

        gridLayout->addWidget(pkcsLE, 5, 3, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);

        localRB = new QRadioButton(frame);
        localRB->setObjectName(QString::fromUtf8("localRB"));

        gridLayout->addWidget(localRB, 1, 0, 1, 1);

        socketLE = new QLineEdit(frame);
        socketLE->setObjectName(QString::fromUtf8("socketLE"));

        gridLayout->addWidget(socketLE, 1, 3, 1, 1);

        nameLE = new QLineEdit(frame);
        nameLE->setObjectName(QString::fromUtf8("nameLE"));

        gridLayout->addWidget(nameLE, 0, 3, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(EditConnection);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(hostLE);
        label_3->setBuddy(portLE);
        label_4->setBuddy(pkcsLE);
        label->setBuddy(socketLE);
        label_5->setBuddy(nameLE);
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
        label_2->setText(QApplication::translate("EditConnection", "&Host", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditConnection", "&Port", 0, QApplication::UnicodeUTF8));
        sslCB->setText(QApplication::translate("EditConnection", "&Use SSL", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("EditConnection", "p&kcs12 file", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditConnection", "&Socket", 0, QApplication::UnicodeUTF8));
        localRB->setText(QApplication::translate("EditConnection", "&Local", 0, QApplication::UnicodeUTF8));
        socketLE->setText(QString());
        nameLE->setText(QString());
        label_5->setText(QApplication::translate("EditConnection", "&Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditConnection: public Ui_EditConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONNECTION_H
