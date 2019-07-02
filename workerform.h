#ifndef WORKERFORM_H
#define WORKERFORM_H

#include <QWidget>
#include "sqlworker.h"
#include "workerslistdialog.h"
namespace Ui {
class WorkerForm;
}

class WorkerForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerForm(QWidget *parent = 0);
    void set(int id);
    void update();
    void setListDialog(WorkersListDialog* wld){this->wld = wld;}
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    ~WorkerForm();

private slots:

    void on_setButton_clicked();
    void on_deleteButton_clicked();

private:
    int workerId;
    WorkersListDialog* wld;
    SQLWorker* sqlWorker;
    Ui::WorkerForm *ui;
};

#endif // WORKERFORM_H
