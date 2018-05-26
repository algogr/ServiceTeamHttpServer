#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <QObject>
#include "httprequesthandler.h"
#include <QtSql>
using namespace stefanfrings;

class DataCollection : public HttpRequestHandler
{
    Q_OBJECT
public:
    DataCollection(QObject* parent=nullptr);
    void service(HttpRequest& request, HttpResponse& response,QSqlDatabase* db);
};

#endif // DATACOLLECTION_H
