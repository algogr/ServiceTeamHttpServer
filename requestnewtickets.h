#ifndef REQUESTNEWTICKETS_H
#define REQUESTNEWTICKETS_H

#include <QObject>
#include "httprequesthandler.h"
using namespace stefanfrings;

class RequestNewTickets : public HttpRequestHandler
{
    Q_OBJECT
public:
    RequestNewTickets(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // REQUESTNEWTICKETS_H
