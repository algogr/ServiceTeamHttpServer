#include "timer.h"

Timer::Timer(int timeout):QTimer(),m_timeout(timeout)
{
   setInterval(timeout);




}


void Timer::timeoutdocs(){

    QSqlQuery qry1(*m_ldb);

    QSqlQuery qry2(*m_rdb);

    QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";

    QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);




    QString series=settings->value("docseries").toString();




    QString query="SELECT  f.trndate,f.series,m.whouse,m.whousesec,f.finstates,f.findoc,\
            (select name from whouse w where w.whouse=m.whouse) descrwhouse,\
            (select name from whouse w where w.whouse=m.whousesec) descrwhousesec,f.fincode\
            from findoc f ,mtrdoc m \
            where m.findoc=f.findoc and f.series in ("+series+") and f.finstates=1";


    qry2.exec(query);

    while (qry2.next())
    {
        QString query=" SELECT * FROM docconfirm where erpid="+qry2.value(5).toString()+" and status="+qry2.value(4).toString();
        qry1.exec(query);

        if (!qry1.next())
        {
        query="INSERT INTO docconfirm (trndate,series,ax1,ax2,status,erpid,descrax1,descrax2,fincode) VALUES \
        ('"+qry2.value(0).toString()+"',"+qry2.value(1).toString()+","+qry2.value(2).toString()+","+\
         qry2.value(3).toString()+","+qry2.value(4).toString()+","+qry2.value(5).toString()+",'"+\
         qry2.value(6).toString()+"','"+qry2.value(7).toString()+"','"+qry2.value(8).toString()+"')";

        qry1.exec(query);

    }
    }
    delete settings;
    settings=nullptr;


}

void Timer::timeouttechnicians()
{

    QSqlQuery qry1(*m_ldb);

    QSqlQuery qry2(*m_rdb);




    QString query="SELECT  ccctexnikos,name,mail,mail10,mail20,code from ccctexnikos";
    qry2.exec(query);


    while (qry2.next())
    {


        if (qry2.value(5).toInt()<1000)
        {
            QString query=" SELECT * FROM technician where erpid="+qry2.value(0).toString();

            qry1.exec(query);

        }
        else
        {
            QString query=" SELECT * FROM district where erpid="+qry2.value(0).toString();

            qry1.exec(query);


        }

        if (!qry1.next())
        {

        if (qry2.value(5).toInt()<1000)
        {
        query="INSERT INTO technician (erpid,name,email,email2,email3,username,password,active) VALUES \
        ("+qry2.value(0).toString()+",'"+qry2.value(1).toString()+"','"+qry2.value(2).toString()+"','"+\
         qry2.value(3).toString()+"','"+qry2.value(4).toString()+"','"+qry2.value(5).toString()+"','',1)";

        qry1.exec(query);

    }
        else
        {
            query="INSERT INTO district (erpid,description) VALUES \
            ("+qry2.value(0).toString()+",'"+qry2.value(1).toString()+"')";

            qry1.exec(query);


        }
        }
        else
        {




            if (qry2.value(5).toInt()<1000)
            {
            query="UPDATE technician set name='"+qry2.value(1).toString()+"' where erpid="+qry2.value(0).toString();
            qry1.exec(query);

            query="UPDATE technician set email='"+qry2.value(2).toString()+"' where erpid="+qry2.value(0).toString();
            qry1.exec(query);

            query="UPDATE technician set email2='"+qry2.value(3).toString()+"' where erpid="+qry2.value(0).toString();
            qry1.exec(query);

            query="UPDATE technician set email3='"+qry2.value(4).toString()+"' where erpid="+qry2.value(0).toString();
            qry1.exec(query);

            }
            else
            {
                query="UPDATE district set description='"+qry2.value(1).toString()+"' where erpid="+qry2.value(0).toString();

                qry1.exec(query);


        }


        }

    }

}

void Timer::timeouttickets()
{
    QSqlQuery qry1(*m_ldb);

    QSqlQuery qry2(*m_rdb);

    QString query="SELECT  ccctexnikos,fincode from findoc where ccckatastash=1 and trndate >='2018/4/23'";

    bool isdistrict=false;
    qry2.exec(query);
    while (qry2.next())
    {
        query="SELECT * from ticket where version=0 and incident='"+qry2.value(1).toString()+"' UNION SELECT * from ticket where version <> 0 and incident='"+qry2.value(1).toString()+"' and techid<>(select id from technician where erpid="+qry2.value(0).toString()+")";
        qDebug()<<query;
        qry1.exec(query);
        if (qry1.next())
        {
        QString query=" SELECT id FROM technician where erpid="+qry2.value(0).toString();

        qry1.exec(query);

        if (!qry1.next())
        {
            QString query=" SELECT id FROM district where erpid="+qry2.value(0).toString();
            qry1.exec(query);

            isdistrict=true;
         }

        query="UPDATE ticket set status=1 where incident='"+qry2.value(1).toString()+"'";

        qry1.exec(query);
        if (isdistrict)
        {
            query="UPDATE ticket set districtid=(select id from district where erpid="\
                    +qry2.value(0).toString()+") where incident='"+qry2.value(1).toString()+"'";


            qry1.exec(query);
        }
        else
        {
            query="UPDATE ticket set techid=(select id from technician where erpid="\
                    +qry2.value(0).toString()+") where incident='"+qry2.value(1).toString()+"'";


            qry1.exec(query);
        }
        query="UPDATE ticket set version=1 where incident='"+qry2.value(1).toString()+"'";


        qry1.exec(query);
    }
    }

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

    if (!m_ldb || !m_rdb || !m_type)
    {
        qDebug()<<"Timer Parameters not set";

        exit(0);
    }
    QTimer::start();

    switch (m_type) {
    case Docs:
        connect(this,SIGNAL(timeout()),this,SLOT(timeoutdocs()));

        break;
    case Technicians:
        connect(this,SIGNAL(timeout()),this,SLOT(timeouttechnicians()));

        break;
    case Tickets:
        connect(this,SIGNAL(timeout()),this,SLOT(timeouttickets()));

        break;

    default:

        break;
    }

}

QSqlDatabase *Timer::rdb() const
{
    return m_rdb;
}

void Timer::setRdb(QSqlDatabase *rdb)
{
    m_rdb = rdb;
}

QSqlDatabase *Timer::ldb() const
{
    return m_ldb;
}

void Timer::setLdb(QSqlDatabase *ldb)
{
    m_ldb = ldb;
}
