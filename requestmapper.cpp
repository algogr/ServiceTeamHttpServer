#include "requestmapper.h"
#include "requestnewtickets.h"
#include "listdatacontroller.h"
#include "datacollection.h"
#include "confirm.h"
#include "breakdownlist.h"
#include "originatorlist.h"
#include "doclist.h"
#include "docsconfirm.h"





RequestMapper::RequestMapper(QObject* parent,QSqlDatabase* ldb,QSqlDatabase* rdb)
: HttpRequestHandler(parent),m_ldb(ldb),m_rdb(rdb)
{


}

void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
        QByteArray path=request.getPath();
        qDebug("RequestMapper: path=%s",path.data());


        if (path=="/list") {
            ListDataController().service(request, response,m_ldb);
        }
        else if (path=="/upload") {
            DataCollection().service(request, response,m_ldb,m_rdb);
        }

        else if (path=="/confirm") {
            Confirm().service(request, response,m_ldb);
        }

        else if (path=="/doclist") {
            DocList().service(request, response,m_ldb);
        }

        else if (path=="/docsconfirm") {
            DocsConfirm().service(request, response,m_ldb,m_rdb);
        }


        else if (path=="/breakdowns")
        {
            BreakdownList().service(request,response,m_ldb);

        }

        else if (path=="/originators")
        {

            OriginatorList().service(request,response,m_ldb);
        }
        else {
            response.setStatus(404,"Not found");
            response.write("The URL is wrong, no such document.",true);
        }

        qDebug("RequestMapper: finished request");

}
