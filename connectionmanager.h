#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QtWidgets>
#include <QtNetwork>
#include <mipconfig.h>
#include "mipavcodecencoder.h"
#include <mipaudiosession.h>
#include <mippainputoutput.h>
#include <iostream>
#include <jrtplib3/rtpipv4address.h>

using namespace jrtplib;

#include "client.h"
#include "mainwindow.h"

class MainWindow;
class Client;

/*
 * @brief A concrete implementation of the Manager interface
 */
class ConnectionManager : public QObject, MIPAudioSession
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
    void sendPrivateMessage(QString msg);
    void call();
    void hangup();

protected:
    void onInputThreadExit(bool err, const std::string &compName, const std::string &errStr)
    {
        if (err)
        {
            qDebug() << "Input chain thread exited due to an error";
            qDebug() << "Component: " << QString::fromStdString(compName);
            qDebug() << "Error: " << QString::fromStdString(errStr);
        }
    }
    void onOutputThreadExit(bool err, const std::string &compName, const std::string &errStr)
    {
        if (err)
        {
            qDebug() << "Output chain thread exited due to an error";
            qDebug() << "Component: " << QString::fromStdString(compName);
            qDebug() << "Error: " << QString::fromStdString(errStr);
        }
    }

private slots:
    void datagramListener();
    bool lengthValidator(int length, QString string);
    void refreshChatters();
    void ping();
    void sayHi();
    void checkRet(bool ret, MIPErrorBase *obj);
    QString getNicknameByIP(QHostAddress address);

private:
    MainWindow *window;
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
    bool flag = true;  
    QTimer *timer;
    MIPAudioSession *audioSess;
};

#endif // CONNECTIONMANAGER_H
