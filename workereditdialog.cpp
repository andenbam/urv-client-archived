#include "workereditdialog.h"
#include "ui_workereditdialog.h"
#include "scheduledialog.h"
#include "messagedropper.h"
#include <QPair>
#include <QTime>

WorkerEditDialog::WorkerEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkerEditDialog)
{
    ui->setupUi(this);
    timespan =  new QVector<QPair<QTime, QTime>>();
    daysToUpdate = new QVector<bool>();
}

void WorkerEditDialog::setListDialog(WorkersListDialog *wld){
    this -> wld = wld;
    ui->positionComboBox->addItems(*(sqlWorker->getAllPosisDesc()));
}

void WorkerEditDialog::setWorker(int workerId){

    this -> workerId = workerId;
    ui->nameLine->setText(sqlWorker->getWorkerName(workerId));
    ui->positionComboBox->setCurrentIndex(sqlWorker->getWorkerPosis(workerId)-1);

    sqlWorker->getWorkerSchedule(workerId, timespan, daysToUpdate);

}

void WorkerEditDialog::makeWorker(){
    this->workerId = sqlWorker->getWorkersMaxId() + 1;
    sqlWorker->addWorker(workerId,
                         ui->nameLine->text(),
                         sqlWorker->getPosisfromDesc(ui->positionComboBox->currentText()));

    sqlWorker->makeWorkerSchedule(workerId);
}

WorkerEditDialog::~WorkerEditDialog()
{
    delete ui;
}

void WorkerEditDialog::on_buttonBox_accepted()
{
     if (ui->nameLine->text() == ""){
         MessageDropper::DropThis("Empty NameField", "Cannot Save Worker without a Name");
         return;
     }
    if (mode){

        sqlWorker->setWorkerName(workerId, ui->nameLine->text());
        sqlWorker->setWorkerPosis(workerId, sqlWorker->getPosisfromDesc(ui->positionComboBox->currentText()));

    wf->update();

    } else {

        makeWorker();
        wld->addNeweyToList(workerId);
    }

    if (updateSchedule)
        sqlWorker->setWorkerSchedule(workerId, timespan, daysToUpdate);
}

void WorkerEditDialog::on_scheduleButton_clicked()
{
    ScheduleDialog* sd = new ScheduleDialog();
    sd->setSQLWorker(sqlWorker);
    sd->setModal(true);
    sd->setEditDialog(this);
    sd->exec();
}
