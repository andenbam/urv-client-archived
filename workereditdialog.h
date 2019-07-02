#ifndef WORKEREDITDIALOG_H
#define WORKEREDITDIALOG_H

#include <QDialog>
#include "sqlworker.h"
#include "workerform.h"
#include "workerslistdialog.h"

namespace Ui {
class WorkerEditDialog;
}

class WorkerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkerEditDialog(QWidget *parent = 0);
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setForm(WorkerForm* wf){this->wf = wf;}
    void setListDialog (WorkersListDialog* wld);
    void setMode(bool mode){this->mode = mode;}
    bool getMode() {return mode;}
    void setUpdateSchedule(){updateSchedule = true;}
    void setWorker(int workerId);
    int getWorker() {return  workerId;}

    QVector<QPair<QTime, QTime>>* timespan;
    QVector<bool>* daysToUpdate;

    ~WorkerEditDialog();

private slots:
    void on_buttonBox_accepted();

    void on_scheduleButton_clicked();

private:
    bool mode;
    bool updateSchedule = false;
    int workerId;

    WorkerForm* wf;
    WorkersListDialog* wld;
    void makeWorker();
    SQLWorker* sqlWorker;
    Ui::WorkerEditDialog *ui;
};

#endif // WORKEREDITDIALOG_H
