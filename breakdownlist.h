#ifndef BREAKDOWNLIST_H
#define BREAKDOWNLIST_H

#include <QObject>
#include "httprequesthandler.h"
#include <QList>
#include <QtSql>
using namespace stefanfrings;

class BreakdownList : public HttpRequestHandler
{
    Q_OBJECT
public:
    explicit BreakdownList(QObject *parent = nullptr);
    void service(HttpRequest &request,HttpResponse& response,QSqlDatabase* db);
signals:

public slots:
};

#endif // BREAKDOWNLIST_H
