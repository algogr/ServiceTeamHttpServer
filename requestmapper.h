#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H
#include "httprequesthandler.h"

using namespace stefanfrings;
#include <QtSql>
class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT

public:
    RequestMapper(QObject* parent=0,QSqlDatabase* ldb=nullptr,QSqlDatabase* rdb=nullptr);
    void service(HttpRequest& request, HttpResponse& response);

private:
    QSqlDatabase *m_ldb,*m_rdb;
};

#endif // REQUESTMAPPER_H
