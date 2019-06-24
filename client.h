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
    QString *username;
    QHostAddress *ip;
    int time;
    QString getUsername();
private slots:
    void removeMe();
    void resetTimer();

};

#endif // CLIENT_H
