#include "originatorlist.h"

OriginatorList::OriginatorList(QObject *parent)
{

}

void OriginatorList::service(HttpRequest &request, HttpResponse &response, QSqlDatabase *db)
{
    QSqlQuery qry(*db);




    response.setHeader("Content-Type", "application/json; charset=UTF-8");
    QString query="select ccceteria,name,'' from ccceteria";
    qry.exec(query);


    QJsonArray originators;

    for(int i=0; i<qry.size(); ++i) {
    {
    qry.next();
     QSqlRecord rec = qry.record();
     QJsonObject json;
     for(int j=0; j<rec.count(); ++j) {
        json[rec.fieldName(j)] = qry.value(j).toString();

        }


        originators.push_back(QJsonValue(json));


    }
}

    response.write(QJsonDocument(originators).toJson(),true);

}
