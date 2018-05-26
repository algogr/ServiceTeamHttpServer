#include "doclist.h"

DocList::DocList(QObject *parent) : QObject(parent)
{

}

void DocList::service(HttpRequest &request, HttpResponse &response, QSqlDatabase *db)
{
    QSqlQuery qry(*db);
    qDebug()<<"AID"<<request.getParameter("AID");
    QString aid=request.getParameter("AID");


    response.setHeader("Content-Type", "application/json; charset=UTF-8");
    QString query="select trndate,ax1,ax2,descrax1,descrax2,status,findoc,series,fincode from \
    cccdocconfirm where ax2="+aid+" and status=1";


    qry.exec(query);
    qDebug()<<qry.size()<<query;


    QJsonArray breakdowns;

    for(int i=0; i<qry.size(); ++i) {
    {
    qry.next();
     QSqlRecord rec = qry.record();
     QJsonObject json;
     for(int j=0; j<rec.count(); ++j) {
        json[rec.fieldName(j)] = qry.value(j).toString();

        }


        breakdowns.push_back(QJsonValue(json));


    }
}

    response.write(QJsonDocument(breakdowns).toJson(),true);


}
