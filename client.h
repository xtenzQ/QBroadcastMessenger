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

    QString getUsername() override { return username; }
    QHostAddress getIP() override { return address; }
    void resetTimer() override;
private slots:
    ConnectionManager *manager;
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
