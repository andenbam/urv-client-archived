#include "sqlworker.h"
#include <QSqlQuery>
#include <QVariant>
#include <QFile>
#include <QVector>

QString SQLWorker::getDBName(){

    return lastDBPath;
}

bool SQLWorker::tryConnectTo(QString& DBPath){

    if (DBPath != "") this->lastDBPath = DBPath;

    QSqlDatabase db = QSqlDatabase::database();
    if( db.isValid() ){
        db.setDatabaseName(DBPath);
        if (!QFile::exists(DBPath))
            return false;

        return true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBPath);
    if (!QFile::exists(DBPath))
        return false;
    bool a = db.open();

    db.close();
    if (!a) return a;
    return true;
}

QSqlDatabase SQLWorker::getDB(QString& DBPath){
    QSqlDatabase db = QSqlDatabase::database();
    if( !db.isValid()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(DBPath);
    db.open();
    return db;
}

int SQLWorker::tryLogIn(QString un, QString p){

    int res = 0;

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.prepare("SELECT prior FROM users WHERE username = :un AND password = :pw");
    query.bindValue(":un", un);
    query.bindValue(":pw", p);
    query.exec();
    while(query.next()){
        res = query.value(0).toInt();
    }
    query.clear();
    db.close();

    return res;
}

int SQLWorker::getTotalVisitsPercentage(){

    return 0;
}

int SQLWorker::getWorkersAmount(){
    int n = 0;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT name FROM workers");
    while(query.next()){
        n++;
    }
    query.clear();
    db.close();
    return n;
}

QTime giveMeFckinTime(QString notATimeYet){
    QTime time = *(new QTime(
                       (notATimeYet.at(0).digitValue())*10 + notATimeYet.at(1).digitValue(),
                       (notATimeYet.at(3).digitValue())*10 + notATimeYet.at(4).digitValue(),
                       (notATimeYet.at(6).digitValue())*10 + notATimeYet.at(7).digitValue(),
                       (notATimeYet.at(9).digitValue())*100 + (notATimeYet.at(10).digitValue())*10 + notATimeYet.at(11).digitValue()
                       ));
    return time;

}

void SQLWorker::getWorkerSchedule(int workerId,
                                  QVector<QPair<QTime, QTime> > *&timespan,
                                  QVector<bool> *&daysToUpdate){

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;

    query.exec("SELECT time_from, time_till FROM work_schedule WHERE worker_id = "
               + QString::number(workerId));
    while (query.next()){

        QTime from = giveMeFckinTime(query.value(0).toString());
        QTime till = giveMeFckinTime(query.value(1).toString());

        timespan->push_back(QPair<QTime, QTime>(from, till));
        daysToUpdate->push_back( from < till);
    }
    query.clear();
    db.close();
}


void SQLWorker::makeWorkerSchedule(int workerId){

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    for (int i = 0; i < 6; i++){
        query.exec("INSERT INTO work_schedule VALUES(" + QString::number(workerId) + ", "
                   + QString::number(i+1) + ", '" + QTime(0,0).toString("HH:mm:ss.zzz") + "', '"
                   + QTime(0,0).toString("HH:mm:ss.zzz") + "')");
        query.next();
        query.clear();
    }
    db.close();

}

void SQLWorker::setWorkerSchedule(int workerId,
                                  QVector<QPair<QTime, QTime>> *timespan,
                                  QVector<bool> *daysToUpdate){

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    for (int i = 0; i < 6; i++)
        if (daysToUpdate->at(i)){
        query.exec("UPDATE work_schedule SET time_from = '"
                   + timespan->at(i).first.toString("HH:mm:ss.zzz") + "', time_till = '"
                   +  timespan->at(i).second.toString("HH:mm:ss.zzz")
                   + "' WHERE worker_id = " + QString::number(workerId) + " AND weekday = " + QString::number(i+1));
        query.next();
        query.clear();
        }

    db.close();
}

QString SQLWorker::getWorkerName(int workerId){
    QString name;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT name FROM workers WHERE worker_id = " + QString::number(workerId));
    while(query.next()){
        name = query.value(0).toString();
    }
    query.clear();
    db.close();
    return name;
}

QStringList* SQLWorker::getWeekTitles(){

    QStringList* output = new QStringList;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT day_name FROM weekdays");
    while(query.next()){
        output->push_back(query.value(0).toString());
    }
    query.clear();
    db.close();
    return output;
}

int SQLWorker::getWorkerPosis(int workerId){
    int posis = 0;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT position FROM workers WHERE worker_id = " + QString::number(workerId));
    while(query.next()){
        posis = query.value(0).toInt();
    }
    query.clear();
    db.close();
    return posis;
}

QStringList* SQLWorker::getAllPosisDesc(){

    QStringList* strList = new QStringList;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT description FROM positions");
    while(query.next()){
        strList->push_back( query.value(0).toString());
    }
    query.clear();
    db.close();
    return strList;
}

int SQLWorker::getPosisfromDesc(QString desc){

    int posis = 0;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT position_id FROM positions WHERE description = '" + desc + "'");
    while(query.next()){
        posis = query.value(0).toInt();
    }
    query.clear();
    db.close();
    return posis;
}

QVector<int> SQLWorker::getWorkersIds(){
    QVector<int> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT worker_id FROM workers");
    while(query.next()){
        vector += query.value(0).toInt();
    }
    query.clear();
    db.close();
    return vector;
}

float SQLWorker::getWorkerHours(int workerId){

    return (float) 20.0 * workerId;
}

void SQLWorker::dropWorker(int workerId){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("DELETE FROM workers WHERE worker_id = " + QString::number(workerId) + " ");
    query.next();
    query.clear();

    query.exec("DELETE FROM visits WHERE worker_id = " + QString::number(workerId));
    while (query.next());
    query.clear();

    query.exec("DELETE FROM work_schedule WHERE worker_id = " + QString::number(workerId));
    while (query.next());
    query.clear();
    db.close();
}

int SQLWorker::getWorkersMaxId(){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT MAX(worker_id) FROM workers");
    query.next();
    int n = query.value(0).toInt();
    query.clear();
    db.close();
    return n;
}

void SQLWorker::addWorker(int id, QString name, int posis){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;

    query.exec("INSERT INTO workers \n"
               + QString("VALUES(") + QString::number(id)
               + ", '" + name + "' , "
               + QString::number(posis) + ")");
    query.next();
    query.clear();
    db.close();
}


void SQLWorker::setWorkerName(int workerId, QString newName){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("UPDATE workers SET name = '" + newName + "' WHERE worker_id = " + QString::number(workerId));
    query.next();
    query.clear();
    db.close();
}

void SQLWorker::setWorkerPosis(int workerId, int newPosis){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("UPDATE workers SET position = " + QString::number(newPosis) + " WHERE worker_id = " + QString::number(workerId));
    query.next();
    query.clear();
    db.close();
}

QVector<QString> SQLWorker::getWorkersName(){

    QVector<QString> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT name FROM workers");
    while(query.next()){
        vector += query.value(0).toString();
    }
    query.clear();
    db.close();
    return vector;
}

QString SQLWorker::getPosDesc(int posis){
    QString str;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT description FROM positions WHERE position_id = " + QString::number(posis));
    while(query.next())
        str = query.value(0).toString();
    query.clear();
    db.close();
    return str;
}

QVector<int> SQLWorker::getWorkersPosis(){
    QVector<int> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT position FROM workers");
    while(query.next()){
        vector += query.value(0).toInt();
    }
    query.clear();
    db.close();
    return vector;
}
