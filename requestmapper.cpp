#include "requestmapper.h"
#include "requestnewtickets.h"
#include "listdatacontroller.h"
#include "datacollection.h"
#include "confirm.h"
#include "breakdownlist.h"
#include "originatorlist.h"
#include "doclist.h"
#include "docsconfirm.h"





RequestMapper::RequestMapper(QObject* parent,QSqlDatabase* db)
: HttpRequestHandler(parent),m_db(db)
{


}

void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
        QByteArray path=request.getPath();
        qDebug("RequestMapper: path=%s",path.data());


        if (path=="/list") {
            ListDataController().service(request, response,m_db);
        }
        else if (path=="/upload") {
            DataCollection().service(request, response,m_ldb,m_db);
        }

        else if (path=="/confirm") {
            Confirm().service(request, response,m_db);
        }

        else if (path=="/doclist") {
            DocList().service(request, response,m_db);
        }

        else if (path=="/docsconfirm") {
            DocsConfirm().service(request, response,m_db);
        }


        else if (path=="/breakdowns")
        {
            BreakdownList().service(request,response,m_db);

        }

        else if (path=="/originators")
        {

            OriginatorList().service(request,response,m_db);
        }
        else {
            response.setStatus(404,"Not found");
            response.write("The URL is wrong, no such document.",true);
        }

        qDebug("RequestMapper: finished request");

}
