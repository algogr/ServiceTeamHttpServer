#include "breakdownlist.h"

BreakdownList::BreakdownList(QObject *parent)
{

}

void BreakdownList::service(HttpRequest &request, HttpResponse &response, QSqlDatabase *db)
{


    QSqlQuery qry(*db);


    response.setHeader("Content-Type", "application/json; charset=UTF-8");
    QString query="select b.code bcode,b.description bdescription,o.erpid oerpid from breakdown b,originator o where b.originatorid=o.id";
    qDebug()<<qry.size()<<query;

    qry.exec(query);


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
