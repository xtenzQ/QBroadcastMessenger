#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "client.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QtNetwork>

class MainWindow;
class Client;

/*
 * @brief A concrete implementation of the Manager interface
 */
class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    ConnectionManager(MainWindow *window);
    // clients
    QVector<Client *> clients;

public slots:
    void addClient(Client *client);
    void removeClient(Client *client);
    void sendMessage(QString *message);
    void sendMessage(QString msg);


private slots:
    void datagramListener();
    bool lengthValidator(int length, QString string);
    void refreshChatters();
    void ping();
    void sayHi();


private:
    MainWindow *window;
    QUdpSocket *udpSocket = nullptr;
    QTimer *ticker;
    const QString nickname = "xtenzQ";

    QHash<QHostAddress, QString> chattersList;
    QHash<QHostAddress, int> timeList;

    const QString P_TYPE = "EVMp";
    const QString P_CONNECT = "CONNECT";
    const QString P_ALIVE = "ALIVE";
    const QString P_SENDMESSAGE = "SENDMSG";
    const QString P_PRIVATEMSG = "PRIVATEMSG";

    // port
    const quint16 port = 14000;
    // response time to ping
    const int responseTime = 2000;

    const char sep = '_';
    bool flag = true;

    const QString destinationIP = "192.168.0.255";
    QTimer *timer;
};

#endif // CONNECTIONMANAGER_H
