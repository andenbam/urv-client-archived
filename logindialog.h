#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setMW(MainWindow* mw){this->mw = mw;}
    ~LoginDialog();


private slots:
    void on_loginButton_clicked();

    void on_LoginDialog_rejected();

    void on_pathButton_clicked();
private:
    QString connectionSettings;
    void saveSettings();
    void loadSettings();
    MainWindow* mw;
    SQLWorker* sqlWorker = NULL;
    Ui::LoginDialog *ui;
    bool loginSuccessful = false;
    QString dbString;
    QString acc;
    QString password;
};

#endif // LOGINDIALOG_H
