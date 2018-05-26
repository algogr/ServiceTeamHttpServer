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


    Timer(int timeout);


    QSqlDatabase *db() const;
    void setDb(QSqlDatabase *db);



    void start();
public slots:
    void timeoutdocs();


private:
    int m_timeout;
    QSqlDatabase *m_db;

    //QString m_lServerIp,m_lServerPort,m_serv,m_rServerIp,m_rServerPort;
    //QString m_lUser,m_lPassword,m_rUser,m_rPassword;
};

#endif // TIMER_H
