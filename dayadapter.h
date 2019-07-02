#ifndef DAYADAPTER_H
#define DAYADAPTER_H

#include <QWidget>

namespace Ui {
class DayAdapter;
}

class DayAdapter : public QWidget
{
    Q_OBJECT

public:
    explicit DayAdapter(QWidget *parent = 0);
    void setAdapter(QString day, bool checked, QTime from, QTime till);
    void getData(bool &checked, QTime &from, QTime &till);
    void turn(bool toggle);
    ~DayAdapter();

private slots:
    void on_day_toggled(bool checked);

private:
    Ui::DayAdapter *ui;
};

#endif // DAYADAPTER_H
