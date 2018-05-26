#include "docsconfirm.h"
#include <QtNetwork>


DocsConfirm::DocsConfirm(QObject *parent):HttpRequestHandler(parent)
{

}

void DocsConfirm::service(HttpRequest &request, HttpResponse &response,QSqlDatabase* db)
{
    qDebug()<<"AID"<<request.getParameter("jsondata");


    QByteArray reqtojson=request.getParameter("jsondata");;
    QSqlQuery qry(*ldb);
    QSqlQuery qry1(*rdb);


    QJsonDocument json= QJsonDocument::fromJson(reqtojson);

    if(!json.isArray()){
        qDebug()<<"JSON is not an Array.";
        qDebug()<<reqtojson;
        return;
    }

    QJsonArray json_array=json.array();


    QJsonArray recDocs;
    for (int i=0;i<json_array.count();++i)
    {

        QJsonObject obj=json_array.at(i).toObject();
        QVariantMap map=obj.toVariantMap();
        QJsonObject json;
        QString query="UPDATE cccdocconfirm set status="+map["status"].toString()+" where findoc="+map["erpid"].toString();
        qry.exec(query);
        qDebug()<<query;
        query="UPDATE findoc set finstates="+map["status"].toString()+" where findoc="+map["erpid"].toString();
        qry1.exec(query);
        json["erpid"]=map["erpid"].toInt();
        recDocs.push_back(QJsonValue(json));
        i++;

    }


    response.setHeader("Content-Type", "application/json; charset=ISO-8859-1");
    response.write(QJsonDocument(recDocs).toJson(),true);

}
