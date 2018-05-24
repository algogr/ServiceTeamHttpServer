#ifndef CONFIRM_H
#define CONFIRM_H

#include <QObject>
#include "httprequesthandler.h"
#include <QtSql>
using namespace stefanfrings;


class Confirm: public HttpRequestHandler
{
    Q_OBJECT
public:
    explicit Confirm(QObject* parent=nullptr);
    void service(HttpRequest &request,HttpResponse& response,QSqlDatabase* db);
};

#endif // CONFIRM_H
