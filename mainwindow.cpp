#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workerslistdialog.h"
#include "logindialog.h"
#include "messagedropper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::quit(){

    QCoreApplication::quit();
}

void MainWindow::connectTo(){

    LoginDialog lDialog;
    lDialog.setSQLWorker(sqlWorker);
    lDialog.setMW(this);
    lDialog.setModal(true);
    lDialog.exec();
}

bool MainWindow::isConnected(){
    return connected;
}

void MainWindow::adjustAmount(){

    ui->amountlabel->setText(QString::number(sqlWorker->getWorkersAmount()));
}

void MainWindow::setConnected(bool value){
    connected = value;
    if (value) {
        ui->dbnamelabel->setText(sqlWorker->getDBName());
        ui->amountlabel->setText(QString::number(sqlWorker->getWorkersIds().size()));
    }
}

void MainWindow::on_workersListButton_clicked()
{
    WorkersListDialog wld;
    wld.setModal(true);
    wld.setSQLWorker(sqlWorker);
    wld.setMainWindow(this);
    wld.setList();
    wld.exec();
    wld.show();
}

void MainWindow::on_seeMoreButton_clicked()
{
    MessageDropper::DropThis("Not Ready Yet...", "This Area is Under Construction.\n Sorry, it's unavailable :(");
}
