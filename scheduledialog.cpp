#include "scheduledialog.h"
#include "ui_scheduledialog.h"
#include "dayadapter.h"
#include <QVBoxLayout>
#include <QPair>
#include <QTime>

ScheduleDialog::ScheduleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);
}

void ScheduleDialog::setEditDialog(WorkerEditDialog *wed){

        this->wed = wed;
        days = *(new QVector<DayAdapter*>);
        QVBoxLayout* l = new QVBoxLayout();
        QStringList* list = sqlWorker->getWeekTitles();

        for (int i=0; i<list->size(); i++){

            days.push_back(new DayAdapter());

            if (!wed->getMode())
                days[i]->setAdapter(list->at(i), i == 5 ? false : true,QTime(8,30),QTime(19,0));
            else
                days[i]->setAdapter(list->at(i),
                                    wed->daysToUpdate->at(i),
                                    wed->timespan->at(i).first,
                                    wed->timespan->at(i).second);
            l->addWidget(days[i]);
        }

        QWidget *widget = new QWidget();
        widget->setLayout(l);
        ui->daysScrollArea->setWidget(widget);
        this->show();
}


ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}

void ScheduleDialog::on_buttonBox_accepted()
{
    wed->timespan->clear();
    wed->daysToUpdate->clear();

    for (int i = 0; i < 6; i++){
        bool turned;
        QTime from;
        QTime till;
        if (ui->everydayCheckBox->isChecked())
        {
            turned = true;
            from = ui->fromEdit->time();
            till = ui->tillEdit->time();
        }
        else
            days.at(i)->getData(turned,from,till);

        wed->timespan->push_back(QPair<QTime,QTime>(from,till));
        wed->daysToUpdate->push_back(turned);
    }

    wed->setUpdateSchedule();
}

void ScheduleDialog::on_everydayCheckBox_stateChanged(int a)
{
    ui->fromEdit->setEnabled(a);
    ui->tillEdit->setEnabled(a);
    for (int i = 0; i<days.size(); i++){
        days.at(i)->turn(!a);
    }
}


