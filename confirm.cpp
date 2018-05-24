#include "confirm.h"

Confirm::Confirm(QObject* parent):HttpRequestHandler(parent)
{

}


void Confirm::service(HttpRequest &request, HttpResponse &response,QSqlDatabase* db)
{
    QString requestid=request.getParameter("RQID");
    qDebug()<<"RQID:"<<requestid;
    QString query="UPDATE request set isconfirmed=1 where requestid="+requestid;
    qDebug()<<query;
    QSqlQuery qry(*db);
    qry.exec(query);


}
