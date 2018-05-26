#ifndef DOCSCONFIRM_H
#define DOCSCONFIRM_H

#include <QObject>
#include "httprequesthandler.h"
#include <QtSql>
using namespace stefanfrings;


class DocsConfirm: public HttpRequestHandler
{
public:

    explicit DocsConfirm(QObject* parent=nullptr);
    void service(HttpRequest &request,HttpResponse& response,QSqlDatabase* db);
};

#endif // DOCSCONFIRM_H
