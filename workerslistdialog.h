#ifndef WORKERSLISTDIALOG_H
#define WORKERSLISTDIALOG_H

#include <QDialog>
#include <QtSql/qsqldatabase.h>
#include "sqlworker.h"
#include "mainwindow.h"
#include <QVBoxLayout>
namespace Ui {
class WorkersListDialog;
}

class WorkersListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkersListDialog(QWidget *parent = 0);
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setMainWindow(MainWindow* mw){this->mw = mw;}
    void setList();
    void adjustAmount();
    void addNeweyToList(int id);
    ~WorkersListDialog();

private slots:
    void on_addButton_clicked();

private:
    QVBoxLayout* layout;
    MainWindow* mw;
    SQLWorker* sqlWorker;
    Ui::WorkersListDialog *ui;
};

#endif // WORKERSLISTDIALOG_H
