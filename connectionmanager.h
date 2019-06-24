#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include "imanager.h"
#include "client.h"

class MainWindow;

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
    QHash<QHostAddress, IClient *> clients;

public slots:
    void addClient(QHostAddress *ip, QString *nick) override;
    void removeClient(QHostAddress *ip) override;
    void notify(IClient *client) override;
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
    const char sep = '_';

    QTextEdit *messagesTextEdit;
    QTextEdit *myMessageTextEdit;
    QListWidget *chatters;

    QTimer *timer;
};

#endif // CONNECTIONMANAGER_H
