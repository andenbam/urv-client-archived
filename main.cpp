#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include "sqlworker.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setOrganizationName("BlackSofa");
    a.setOrganizationDomain("www.google.ru");
    a.setApplicationName("urv-client");
    a.setApplicationDisplayName("URV Client with SQLite");
    a.setApplicationVersion("1.0.0.0");

    MainWindow *mw = new MainWindow();
    mw->setSQLWorker(new SQLWorker());
    mw->connectTo();
    if (!mw->isHidden())
        return a.exec();
    else return 0;
}
