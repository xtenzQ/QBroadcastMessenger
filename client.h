#ifndef CLIENT_H
#define CLIENT_H

#include "iclient.h"
#include <QtWidgets>
#include <QtNetwork>

class Client : public IClient, QObject
{
    Q_OBJECT
public:
    Client(QString *user, QHostAddress *address);
private:
    QString *username;
    QHostAddress *ip;
    int time;
    QTimer *timer;
private slots:
    void removeMe();
    void resetTimer();
};

#endif // CLIENT_H
