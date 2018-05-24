#ifndef ORIGINATORLIST_H
#define ORIGINATORLIST_H

#include <QObject>
#include "httprequesthandler.h"
#include <QList>
#include <QtSql>
using namespace stefanfrings;
class OriginatorList : public HttpRequestHandler
{
    Q_OBJECT
public:
    explicit OriginatorList(QObject *parent = nullptr);
    void service(HttpRequest &request,HttpResponse& response,QSqlDatabase* db);

};

#endif // ORIGINATORLIST_H
