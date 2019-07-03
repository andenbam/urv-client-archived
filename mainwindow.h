#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    bool isConnected();
    void setConnected(bool value);
    void quit();
    void connectTo();
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void adjustAmount();
    ~MainWindow();

private slots:
    void on_workersListButton_clicked();

    void on_seeMoreButton_clicked();

private:
    bool connected = false;
    SQLWorker* sqlWorker = nullptr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
