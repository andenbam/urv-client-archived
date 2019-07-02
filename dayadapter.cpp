#include "dayadapter.h"
#include "ui_dayadapter.h"

DayAdapter::DayAdapter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DayAdapter)
{
    ui->setupUi(this);

}

DayAdapter::~DayAdapter()
{
    delete ui;
}

void DayAdapter::turn(bool toggle){
    ui->day->setChecked(!toggle);
    ui->day->setEnabled(toggle);
    ui->fromEdit->setEnabled(toggle);
    ui->tillEdit->setEnabled(toggle);
}

void DayAdapter::setAdapter(QString day, bool checked, QTime from, QTime till){

    ui->day->setText(day);
    ui->day->setChecked(checked);
    ui->fromEdit->setEnabled(checked);
    ui->tillEdit->setEnabled(checked);
    ui->fromEdit->setTime(from);
    ui->tillEdit->setTime(till);
}

void DayAdapter::getData(bool &checked, QTime &from, QTime &till){
    checked = ui->day->isChecked();
    from = ui->fromEdit->time();
    till = ui->tillEdit->time();

}

void DayAdapter::on_day_toggled(bool checked)
{
    ui->fromEdit->setEnabled(checked);
    ui->tillEdit->setEnabled(checked);
}
