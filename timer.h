#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QJsonDocument>
#include <QtSql>


class Timer : public QTimer
{
    Q_OBJECT


public:
    enum RequestTypes
          {
             Docs,
             Technicians,
             Tickets
          };

    Timer(int timeout);

    QSqlDatabase *ldb() const;
    void setLdb(QSqlDatabase *ldb);

    QSqlDatabase *rdb() const;
    void setRdb(QSqlDatabase *rdb);

    RequestTypes type() const;
    void setType(const RequestTypes &type);

    void start();
public slots:
    void timeoutdocs();
    void timeouttechnicians();
    void timeouttickets();

private:
    int m_timeout;
    QSqlDatabase *m_ldb,*m_rdb;
    RequestTypes m_type;
    //QString m_lServerIp,m_lServerPort,m_serv,m_rServerIp,m_rServerPort;
    //QString m_lUser,m_lPassword,m_rUser,m_rPassword;
};

#endif // TIMER_H
