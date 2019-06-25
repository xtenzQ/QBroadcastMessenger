#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QtNetwork>
#include "connectionmanager.h"

class ConnectionManager;

/**
 * @brief Concrete client
 */
class Client : public QObject
{
    Q_OBJECT
public:
    Client(ConnectionManager *manager, QString username, QHostAddress address);
    QString getUsername() { return username; }
    QHostAddress getIP() { return address; }
    ConnectionManager *manager;
    void resetTimer();
private slots:
    void removeMe();
private:
    // username
    QString username;
    // IPv4 address
    QHostAddress address;
    //
    QTimer *timer;
};

#endif // CLIENT_H
