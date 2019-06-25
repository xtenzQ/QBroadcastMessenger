#ifndef CLIENT_H
#define CLIENT_H

#include "iclient.h"

#include <QtWidgets>
#include <QtNetwork>

class ConnectionManager;

/**
 * @brief Concrete client
 */
class Client : public IClient, QObject
{
    Q_OBJECT
public:
    Client(ConnectionManager *manager, QString username, QHostAddress address);
    // username
    QString username;
    // IPv4 address
    QHostAddress address;
    // timer deletion
    int time;
private slots:
    ConnectionManager *manager;
    void removeMe();
    void resetTimer();
private:
    QTimer *timer;
};

#endif // CLIENT_H
