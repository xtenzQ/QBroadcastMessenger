#ifndef CLIENT_H
#define CLIENT_H

#include "iclient.h"
#include "imanager.h"
#include <QtWidgets>
#include <QtNetwork>
#include "connectionmanager.h"

class ConnectionManager;

/**
 * @brief Concrete client
 */
class Client : public IClient
{
    Q_OBJECT
public:
    Client(ConnectionManager *manager, QString username, QHostAddress address);
    QString getUsername() override { return username; }
    QHostAddress getIP() override { return address; }
    ConnectionManager *manager;
    void resetTimer() override;
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
