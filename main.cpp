#include <QCoreApplication>
#include <QSettings>
#include "httplistener.h"
#include "listdatacontroller.h"
#include "requestmapper.h"
#include "QtSql"
#include "timer.h"

using namespace stefanfrings;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile st(QCoreApplication::applicationDirPath()+"/settings.ini");
    QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";
    QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);

    if (!st.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        settings->setValue("dsnMySQL","serviceteam");
        settings->setValue("hostnameMySQL","localhost");
        settings->setValue("userMySQL","root");
        settings->setValue("passMySQL","101264");
        settings->setValue("dsnSQLServer","soft1");
        settings->setValue("portSQLServer","1433");
        settings->setValue("userSQLServer","sa");
        settings->setValue("passSQLServer","tt123!@#");
        settings->sync();
    }
    st.close();
    settings->beginGroup("db");
    QSqlDatabase db1=QSqlDatabase::addDatabase(settings->value("driverMySQL").toString(),settings->value("dsnMySQL").toString());
    //QSqlDatabase db1=QSqlDatabase::addDatabase("QMYSQL","serviceteam");

    //QSqlDatabase db1=QSqlDatabase::addDatabase("QODBC","serviceteam");
    db1.setDatabaseName(settings->value("dsnMySQL").toString());
    db1.setHostName(settings->value("hostnameMySQL").toString());
    db1.setPort(3306);
    db1.setUserName(settings->value("userMySQL").toString());
    db1.setPassword(settings->value("passMySQL").toString());


    if (!db1.open())
    {
        qDebug()<<"Error on MySQL:"<< db1.lastError().text();
         exit(0);
    }
/*
    QSqlDatabase db2=QSqlDatabase::addDatabase(settings->value("driverSQLServer").toString(),settings->value("dsnSQLServer").toString());

    db2.setDatabaseName(settings->value("dsnSQLServer").toString());
    db2.setHostName(settings->value("hostnameSQLServer").toString());
    db2.setPort(settings->value("portSQLServer").toInt());
    db2.setUserName(settings->value("userSQLServer").toString());
    db2.setPassword(settings->value("passSQLServer").toString());
  */


    //QSqlDatabase db2=QSqlDatabase::addDatabase("QODBC","s1algo");
    //QSqlDatabase db2=QSqlDatabase::addDatabase(settings->value("driverSQLServer").toString(),settings->value("dsnSQLServer").toString());
    //db2.setDatabaseName("DRIVER=FreeTDS;Server=79.129.43.70;Database=tsolakidis;Uid=sa;Port=8728;Pwd=600096;WSID=");
    //db2.setDatabaseName("DRIVER=FreeTDS;Server=192.168.2.248;Database=tsolakidis;Uid=sa;Port=1433;Pwd=600096;WSID=");
    //db2.setDatabaseName("DRIVER=FreeTDS;Server="+settings->value("hostnameSQLServer").toString()+"Database="+settings->value("dsnSQLServer").toString()+";Uid="+settings->value("userSQLServer").toString()+";Port="+settings->value("portSQLServer").toString()+";Pwd="+settings->value("passSQLServer").toString()+";WSID=");
    QSqlDatabase db2=QSqlDatabase::addDatabase("QODBC3",settings->value("dsnSQLServer").toString());

    db2.setDatabaseName(settings->value("dsnSQLServer").toString());

    db2.setUserName(settings->value("userSQLServer").toString());
    db2.setPassword(settings->value("passSQLServer").toString());

    if (!db2.open())
    {
        qDebug()<<"Error on SQL Server:"<< db2.lastError().text();
        //exit(0);
    }
    settings->endGroup();




    //QSettings* listenerSettings=new QSettings("settings.ini",QSettings::IniFormat,&a);
    //qDebug("config file loaded");
    //listenerSettings->beginGroup("listener");
    settings->beginGroup("listener");
    // Start the HTTP server

    Timer* timerdocs=new Timer(10000);
    timerdocs->setLdb(&db1);
    timerdocs->setRdb(&db2);
    timerdocs->setType(Timer::RequestTypes::Docs);

    Timer* timertechs=new Timer(5000);
    timertechs->setLdb(&db1);
    timertechs->setRdb(&db2);
    timertechs->setType(Timer::RequestTypes::Technicians);
    timertechs->start();
    Timer* timertickets=new Timer(10000);
    timertickets->setLdb(&db1);
    timertickets->setRdb(&db2);
    timertickets->setType(Timer::RequestTypes::Tickets);
    timertickets->start();



    HttpListener* httplistener=new HttpListener(settings, new RequestMapper(&a,&db1,&db2), &a);


    return a.exec();
}
