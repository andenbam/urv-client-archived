#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>
#include "sqlworker.h"
#include "workereditdialog.h"
#include "dayadapter.h"
namespace Ui {
class ScheduleDialog;
}

class ScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleDialog(QWidget *parent = 0);
    ~ScheduleDialog();
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setEditDialog(WorkerEditDialog* wed);

private slots:
    void on_buttonBox_accepted();

    void on_everydayCheckBox_stateChanged(int a);

private:
    QVector<DayAdapter*> days;
    SQLWorker* sqlWorker;
    WorkerEditDialog* wed;
    Ui::ScheduleDialog *ui;
};

#endif // SCHEDULEDIALOG_H
