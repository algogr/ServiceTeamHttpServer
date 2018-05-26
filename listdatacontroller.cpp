#include "listdatacontroller.h"
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
ListDataController::ListDataController(QObject* parent)
{
    list.append("Robert");
       list.append("Lisa");
       list.append("Hannah");
       list.append("Ludwig");
       list.append("Miranda");
       list.append("Francesco");
       list.append("Kim");
       list.append("Jacko");

}

void ListDataController::service(HttpRequest &request, HttpResponse &response,QSqlDatabase* db)
{
    qDebug()<<"UID"<<request.getParameter("UID");
    QString uid=request.getParameter("UID");
    QSqlQuery qry(*db);
    QSqlQuery qry1(*db);
    QString query="select ccctechnician from ccctechnician where username='"+uid+"'";
    qDebug()<<query;
    qry.exec(query);
    qry.next();
    QString techid=qry.value(0).toString();
    qDebug()<<"TECHID:"<<techid;
    query="select distinct districtid from ccctechdistrict where techid="+techid;
    qry.exec(query);
    QString where="(";
   while (qry.next()) {
        where+=qry.value(0).toString()+",";
    }

    where+=")";
    where.replace(",)",")");

    query="select max(requestid) from cccrequest";
    qry.exec(query);
    QVariant maxid;
    if(!qry.next())
        maxid=1;
    else
        maxid=qry.value(0).toInt()+1;

    QString smaxid=maxid.toString();

    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    query="select t.cccergasia title,c.name customername,t.cccreporteddate reporteddate ,t.cccpriority priority,\
                    t.cccdescription description,c.cccperioxi location,t.cccappointment appointmentfrom,o.ccceteria originatorid,\
                    o.name originatorname,tc.username techid,t.ccckatastash status,c.city city,c.cccnomos county,c.address address,\
                    c.phone01 phone1,c.phone02 phone2,c.cccpostalcode postalcode,c.cccdbf loopnumber,\
                    c.longitude longtitude,c.latitude latitude,t.incident incident,t.id mysqlid,t.escalit escalit,\
                    t.cccoteport oteport,t.ccctechnician districtid,t.cccversion version from findoc t,cccsubscriber c,ccceteria o,ccctechnician tc where tc.ccctechnician=t.ccctechnician and o.ccceteria=t.ccceteria and t.cccsubscriber=c.cccsubscriber \
                    and t.ccckatastash=1 and t.cccappointment< (dateadd(dd,7,getdate())) and t.ccctechnician="+techid+" and not exists (select * from cccrequest r where r.ticketid=t.findoc and r.uid="\
                    +techid+" and r.version=t.cccversion and r.isconfirmed=1) UNION select t.cccergasia title,c.name customername,t.cccreporteddate reporteddate ,t.cccpriority priority,\
            t.cccdescription description,c.cccperioxi location,t.cccappointment appointmentfrom,o.ccceteria originatorid,\
            o.name originatorname,tc.username techid,t.ccckatastash status,c.city city,c.cccnomos county,c.address address,\
            c.phone01 phone1,c.phone02 phone2,c.cccpostalcode postalcode,c.cccdbf loopnumber,\
            c.longitude longtitude,c.latitude latitude,t.incident incident,t.id mysqlid,t.escalit escalit,\
            t.cccoteport oteport,t.ccctechnician districtid,t.cccversion version from findoc t,cccsubscriber c,ccceteria o,ccctechnician tc where tc.ccctechnician=t.ccctechnician and o.ccceteria=t.ccceteria and t.cccsubscriber=c.cccsubscriber \
                    and t.ccckatastash=1 and t.cccappointment< (dateadd(dd,7,getdate())) and ((t.ccctechnician is null) or (t.ccctechnician=0)) and exists(select * from ccctechdistrict td where \
                    td.refdate=t.cccappointment and td.techid="+techid+") and not exists (select * from cccrequest r where r.ticketid=t.findoc and r.uid="\
                    +techid+" and r.version=t.cccversion and r.isconfirmed=1)";

    qry.exec(query);
    qDebug()<<query;

    QJsonArray newTickets;
    QVariant recordcount=0;
    if (qry.last())
    {
        recordcount=qry.at()+1;
        qry.first();
        qry.previous();
    }

    int i=0;
    while(qry.next()) {


     QSqlRecord rec = qry.record();
     QJsonObject json;
     for(int j=0; j<rec.count(); ++j) {
        json[rec.fieldName(j)] = qry.value(j).toString();

        }

        QString query1="INSERT INTO cccrequest (uid,ticketid,version,isconfirmed,requestid) VALUES ("+techid+","+\
             qry.value(21).toString()+","+qry.value(25).toString()+",0,"+smaxid+")";
        qry1.exec(query1);
        qDebug()<<query1;
        json["requestid"]=smaxid;
        json["recordcount"]=recordcount.toString();

        newTickets.push_back(QJsonValue(json));

        i++;

}

    response.write(QJsonDocument(newTickets).toJson(),true);
}
