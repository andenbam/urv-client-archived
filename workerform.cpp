#include "workerform.h"
#include "ui_workerform.h"
#include "workereditdialog.h"
#include "messagedropper.h"

WorkerForm::WorkerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerForm)
{
    ui->setupUi(this);
}

WorkerForm::~WorkerForm()
{
    delete ui;
}

void WorkerForm::set(int id){

    workerId = id;
    ui->namelabel->setText(sqlWorker->getWorkerName(id));
    ui->postitionlabel->setText(sqlWorker->getPosDesc(sqlWorker->getWorkerPosis(id)));
    ui->hourslabel->setText(QString::number(sqlWorker->getWorkerHours(id))+"hrs");
}

void WorkerForm::update(){

    set(workerId);
}


void WorkerForm::on_setButton_clicked()
{
    WorkerEditDialog wed;
    wed.setForm(this);
    wed.setMode(true);
    wed.setSQLWorker(sqlWorker);
    wed.setListDialog(wld);
    wed.setWorker(workerId);
    wed.setModal(true);
    wed.exec();

}

void WorkerForm::on_deleteButton_clicked()
{
    if (MessageDropper::DropAsk("Delete this worker?", "Are U Sure?")){

        sqlWorker->dropWorker(workerId);
        wld->adjustAmount();
        close();
    }
}
