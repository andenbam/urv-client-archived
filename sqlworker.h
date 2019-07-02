#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QtSql/qsqldatabase.h>
#include <QPair>
#include <QTime>
class SQLWorker
{

public:
    SQLWorker(){}
    QString getDBName();
    bool tryConnectTo(QString& DBPath);
    int tryLogIn(QString un, QString p);
    int getWorkersAmount();

    QVector<QString> getWorkersName();
    QString getWorkerName(int workerId);

    void setWorkerName(int workerId, QString newName);
    void setWorkerPosis(int workerId, int newPosis);

    int getWorkerPosis(int workerId);
    int getPosisfromDesc(QString desc);

    QStringList* getAllPosisDesc();
    QStringList* getWeekTitles();
    QVector<int>    getWorkersPosis();
    QVector<int>    getWorkersIds();
    QString         getPosDesc(int posis);

    void            dropWorker(int workerId);
    void            addWorker(int id, QString name, int posis);
    int             getWorkersMaxId();

    void            setWorkerSchedule(int workerId,
                                      QVector<QPair<QTime, QTime>>* timespan,
                                      QVector<bool>* daysToUpdate);
    void            makeWorkerSchedule(int workerId);
    void            getWorkerSchedule (int workerId,
                                       QVector<QPair<QTime, QTime>>* &timespan,
                                       QVector<bool>* &daysToUpdate);
    float           getWorkerHours(int workerId);
    int             getAbsenceHours();
    int             getTotalVisitsPercentage();

private:
    QSqlDatabase getDB(QString& DBPath);
    QString lastDBPath = "no";
};

#endif // SQLWORKER_H
