#include "workerslistdialog.h"
#include "ui_workerslistdialog.h"
#include <QtSql>
#include <QVBoxLayout>
#include <QTableWidget>
#include "workerform.h"
#include "workereditdialog.h"

WorkersListDialog::WorkersListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkersListDialog)
{
    ui->setupUi(this);
}

void clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {

        delete item;
    }
}

void WorkersListDialog::setList(){

    layout = new QVBoxLayout();

    QVector<QString> wList = sqlWorker->getWorkersName();
    QVector<int> wposList = sqlWorker->getWorkersPosis();
    QVector<int> widList = sqlWorker->getWorkersIds();
    ui->wAmountlabel->setText(QString::number(wList.size()));

    for (int i = 0; i < wList.size(); i++){
        WorkerForm *elm = new WorkerForm();
        elm->setSQLWorker(sqlWorker);
        elm->setListDialog(this);
        elm->set(widList[i]);
        layout->addWidget(elm);

    }
    QWidget* scrollWidget = new QWidget();

    scrollWidget->setMinimumWidth(450);
    scrollWidget->setLayout(layout);

    wList.clear();
    wposList.clear();
    widList.clear();

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollWidget);

    this->show();
}

WorkersListDialog::~WorkersListDialog()
{
    delete ui;
}

void WorkersListDialog::adjustAmount(){

    mw->adjustAmount();
    ui->wAmountlabel->setText(QString::number(sqlWorker->getWorkersAmount()));
}

void WorkersListDialog::addNeweyToList(int id){

    WorkerForm *elm = new WorkerForm();
    elm->setSQLWorker(sqlWorker);
    adjustAmount();
    elm->set(id);
    layout->addWidget(elm);
}

void WorkersListDialog::on_addButton_clicked()
{
    WorkerEditDialog wed;
    wed.setSQLWorker(sqlWorker);
    wed.setListDialog(this);
    wed.setMode(false);
    wed.setModal(true);
    wed.exec();
}
