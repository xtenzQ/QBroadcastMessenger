#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include "imanager.h"
#include "client.h"

class Client;

/*
 * @brief A concrete implementation of the Manager interface
 */
class ConnectionManager : public IManager, QObject
{
    Q_OBJECT

public:
    ConnectionManager(QTextEdit *, QTextEdit *, QListWidget *);
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
    void sendMessage(QString *message) override;
    void setTimer();

private slots:
    void datagramListener();
    void checkTime();
    bool lengthValidator(int length, QString string);
    void displayServiceMessage(QString);
    void displayTextMessage(QString);
    void refreshChatters();
    void ping();

private:
    QUdpSocket *udpSocket = nullptr;
    QTimer *ticker;

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

    QTextEdit *messagesTextEdit;
    QTextEdit *myMessageTextEdit;
    QListWidget *chatters;

    QTimer *timer;
};

#endif // CONNECTIONMANAGER_H
