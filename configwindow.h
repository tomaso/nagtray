#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class ConfigWindow;
}

class ConfigWindow : public QDialog {
    Q_OBJECT
public:
    ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConfigWindow *ui;
    QStandardItemModel modelConnections;

private slots:


private slots:
    void on_buttonBox_rejected();
    void on_listView_doubleClicked(QModelIndex index);
    void on_removeButton_clicked();
    void on_editButton_clicked();
    void on_addButton_clicked();
};


#endif // CONFIGWINDOW_H
