#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H
#include "httprequesthandler.h"

using namespace stefanfrings;
#include <QtSql>
class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT

public:
    RequestMapper(QObject* parent=0,QSqlDatabase* db=nullptr);
    void service(HttpRequest& request, HttpResponse& response);

private:
    QSqlDatabase *m_db;
};

#endif // REQUESTMAPPER_H
