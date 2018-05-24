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
    QString query="select id from technician where username='"+uid+"'";
    qDebug()<<query;
    qry.exec(query);
    qry.next();
    QString techid=qry.value(0).toString();
    qDebug()<<"TECHID:"<<techid;
    query="select distinct districtid from techdistrict where techid="+techid;
    qry.exec(query);
    QString where="(";
   while (qry.next()) {
        where+=qry.value(0).toString()+",";
    }

    where+=")";
    where.replace(",)",")");

    query="select max(requestid) from request";
    qry.exec(query);
    QVariant maxid;
    if(!qry.next())
        maxid=1;
    else
        maxid=qry.value(0).toInt()+1;

    QString smaxid=maxid.toString();

    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    query="select t.title title,c.name customername,t.reporteddate reporteddate ,t.priority priority,\
                    t.description description,c.location location,t.appointmentfrom appointmentfrom,o.id originatorid,\
                    o.name originatorname,tc.username techid,t.status status,c.city city,c.county county,c.address address,\
                    c.phone1 phone1,c.phone2 phone2,c.postalcode postalcode,c.loopnumber loopnumber,\
                    c.longitude longtitude,c.latitude latitude,t.incident incident,t.id mysqlid,t.escalit escalit,\
                    t.oteport oteport,t.districtid districtid,t.version version from ticket t,customer c,originator o,technician tc where tc.id=t.techid and o.id=t.originatorid and t.cusid=c.id \
                    and t.status=1 and DATE(t.appointmentfrom)< (NOW() + INTERVAL 7 DAY) and t.techid="+techid+" and not exists (select * from request r where r.ticketid=t.id and r.uid="\
                    +techid+" and r.version=t.version and r.isconfirmed=1) UNION select t.title title,c.name customername,t.\
                    reporteddate reporteddate ,t.priority priority,t.description description,c.location location,t.appointmentfrom appointmentfrom,\
                    o.id originatorid,o.name originatorname,tc.username techid,t.status status,c.city city,c.county county,c.address address,\
                    c.phone1 phone1,c.phone2 phone2,c.postalcode postalcode,c.loopnumber loopnumber,\
                    c.longitude longtitude,c.latitude latitude,t.incident incident,t.id mysqlid,t.escalit escalit,\
                    t.oteport oteport,t.districtid districtid,t.version version from ticket t,customer c,originator o,technician tc where tc.id=t.techid and o.id=t.originatorid and t.cusid=c.id \
                    and t.status=1 and DATE(t.appointmentfrom)< (NOW() + INTERVAL 7 DAY) and ((t.techid is null) or (t.techid=0)) and exists(select * from techdistrict td where \
                    td.refdate=date(t.appointmentfrom) and td.techid="+techid+") and not exists (select * from request r where r.ticketid=t.id and r.uid="\
                    +techid+" and r.version=t.version and r.isconfirmed=1)";

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

        QString query1="INSERT INTO request (uid,ticketid,version,isconfirmed,requestid) VALUES ("+techid+","+\
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
