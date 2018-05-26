#include "timer.h"

Timer::Timer(int timeout):QTimer(),m_timeout(timeout)
{
   setInterval(timeout);




}


void Timer::timeoutdocs(){


    QSqlQuery qry(*m_db),qry1(*m_db);

    QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";

    QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);




    QString series=settings->value("docseries").toString();




    QString query="SELECT  f.trndate,f.series,m.whouse,m.whousesec,f.finstates,f.findoc,\
            (select name from whouse w where w.whouse=m.whouse) descrwhouse,\
            (select name from whouse w where w.whouse=m.whousesec) descrwhousesec,f.fincode\
            from findoc f ,mtrdoc m \
            where m.findoc=f.findoc and f.series in ("+series+") and f.finstates=1";


    qry.exec(query);

    while (qry.next())
    {
        QString query=" SELECT * FROM cccdocconfirm where findoc="+qry.value(5).toString()+" and status="+qry.value(4).toString();
        qry1.exec(query);

        if (!qry1.next())
        {
        query="INSERT INTO cccdocconfirm (trndate,series,ax1,ax2,status,findoc,descrax1,descrax2,fincode) VALUES \
        ('"+qry.value(0).toString()+"',"+qry.value(1).toString()+","+qry.value(2).toString()+","+\
         qry.value(3).toString()+","+qry.value(4).toString()+","+qry.value(5).toString()+",'"+\
         qry.value(6).toString()+"','"+qry.value(7).toString()+"','"+qry.value(8).toString()+"')";

        qry1.exec(query);

    }
    }
    delete settings;
    settings=nullptr;


}



Timer::RequestTypes Timer::type() const
{
    return m_type;
}

void Timer::setType(const RequestTypes &type)
{
    m_type = type;
}

void Timer::start()
{

    if (!m_db)
    {
        qDebug()<<"Timer Parameters not set";

        exit(0);
    }
    QTimer::start();

    connect(this,SIGNAL(timeout()),this,SLOT(timeoutdocs()));


    }

}

QSqlDatabase *Timer::db() const
{
    return m_db;
}

void Timer::setDb(QSqlDatabase *db)
{
    m_db = db;
}

