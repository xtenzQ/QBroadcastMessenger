#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include "imanager.h"
#include "client.h"

/*
 * @brief A concrete implementation of the Manager interface
 */
class ConnectionManager : public IManager, QObject
{
    Q_OBJECT

public:
    ConnectionManager();
    /*
    static ConnectionManager &GetInstance() {
        static ConnectionManager instance;
        return instance;
    }*/
    // clients
    QVector<IClient *> clients;

public slots:
    void addClient(IClient *client) override;
    void removeClient(IClient *client) override;
    void notify(IClient *client) override;
    void setTimer();

private slots:
    void datagramListener();
    void checkTime();
    bool lengthValidator(int length, QString string);

private:
    QUdpSocket *udpSocket = nullptr;
    QTimer *ticker;
    const QString P_TYPE = "EVMp";
    const QString P_CONNECT = "CONNECT";
    const QString P_ALIVE = "ALIVE";
    const QString P_SENDMESSAGE = "SENDMSG";
    const QString P_PRIVATEMSG = "PRIVATEMSG";
    const char sep = '_';

    QTimer *timer;
};

#endif // CONNECTIONMANAGER_H
