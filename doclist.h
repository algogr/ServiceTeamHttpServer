#ifndef DOCLIST_H
#define DOCLIST_H

#include <QObject>
#include "httprequesthandler.h"
#include <QtSql>
using namespace stefanfrings;

class DocList : public QObject
{
    Q_OBJECT
public:
    explicit DocList(QObject *parent = nullptr);
    void service(HttpRequest &request,HttpResponse& response,QSqlDatabase* db);
};

#endif // DOCLIST_H
