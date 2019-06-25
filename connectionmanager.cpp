#include "connectionmanager.h"

ConnectionManager::ConnectionManager(MainWindow *window)
{
    this->window = window;

    udpSocket = new QUdpSocket();
    udpSocket->bind(port, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &ConnectionManager::datagramListener);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ConnectionManager::ping);
    timer->setInterval(responseTime);
    timer->start();
}

/**
 * @brief Add client to clients list
 * @param client IClient entity
 */
void ConnectionManager::addClient(IClient *client) {
    clients.push_back(client);
    refreshChatters();
}

/**
 * @brief Remove client from clients list
 * @param client IClient entity
 */
void ConnectionManager::removeClient(IClient *client) {

    auto iterator = std::find(clients.begin(), clients.end(), client);

    if (iterator != clients.end()) { // client found
        clients.erase(iterator); // remove client
    }

    refreshChatters();
}

void ConnectionManager::sendMessage(QString *) {

}

/**
 * @brief Checks if length of the payload matches the actual payload
 * @param length length of payload in int
 * @param string Payload
 * @return true if equal
 */
bool ConnectionManager::lengthValidator(int length, QString string) {
    return (length == string.length()) ? true : false;
}

/**
 * @brief Listens to incoming datagrams
 */
void ConnectionManager::datagramListener() {
    QByteArray datagram;
    QHostAddress senderIP = QHostAddress();
    quint16 port = 0;
    // Returns true if at least one datagram is waiting to be read
    while (udpSocket->hasPendingDatagrams())
    {
        // sets datagram size
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        // reads datagram
        udpSocket->readDatagram(datagram.data(), datagram.size(), &senderIP, &port);
        // gets pointer to data stored in datagram byte array
        QString data = datagram.constData();

        // parse string to use data further
        // prName - protocol name
        // prCommand - command type
        // prLength - payload length
        // prPayload - payload
        QString prName = data.split(sep)[0];
        QString prCommand = data.split(sep)[1];
        int prLength = data.split(sep)[2].toInt();
        QString prPayload = data.split(sep)[3];

        // Check block
        // Checking protocol name first
        if (prName == P_TYPE)
        {
            // I feel so bad everytime I work with switch in C++ of not being able to compare variables with QString
            if (prCommand == P_CONNECT)
            {
                if (lengthValidator(prLength, prPayload)) {
                    // add client to QHash
                    new Client(this, prPayload, senderIP);
                    window->addMessage(tr("%1 has joined").arg(prPayload), Qt::gray);
                    refreshChatters();
                }
            }
            // if the incoming datagram contains message
            else if (prCommand == P_SENDMESSAGE)
            {
                if (lengthValidator(prLength, prPayload))
                {
                    window->addMessage(tr("<%1> : %2").arg(chattersList.value(senderIP), prPayload), Qt::black);
                }
            }
            // if incoming datagram is a ping
            else if (prCommand == P_ALIVE) {
                if (lengthValidator(prLength, prPayload)) {
                    foreach (IClient *client, clients) {
                        if (client->getIP() == senderIP) {
                            client->resetTimer();
                        }
                    }
                }
                // or add new client to list and show him in chat
                else {
                    new Client(this, prPayload, senderIP);
                    window->addMessage(tr("%1 in chat").arg(prPayload), Qt::gray);
                    refreshChatters();
                }
            }
        }
    }
}

/**
 * @brief ConnectionManager::refreshChatters
 */
void ConnectionManager::refreshChatters() {
    QStringList *list = new QStringList;
    foreach (IClient *client, clients)
    {
        list->append(client->getUsername());
    }
    window->refreshUserList(list);
}

/**
 * @brief ConnectionManager::sendMessage
 * @param msg
 */
void ConnectionManager::sendMessage(QString msg)
{
    if (flag) {
        sayHi();
        flag = false;
    }
    udpSocket->writeDatagram((P_TYPE + sep + P_SENDMESSAGE + sep + QString::number(msg.length()) + sep + msg).toUtf8(), QHostAddress(destinationIP), port); //172.27.24.255 192.168.0.104
}

/**
 * @brief ConnectionManager::sayHi
 */
void ConnectionManager::sayHi()
{
    udpSocket->writeDatagram((P_TYPE + sep + P_CONNECT + sep + QString::number(nickname.length()) + sep + nickname).toUtf8(), QHostAddress(destinationIP), port); //172.27.24.255 192.168.0.104
}

/**
 * @brief ConnectionManager::ping
 */
void ConnectionManager::ping()
{
    udpSocket->writeDatagram((P_TYPE + sep + P_ALIVE + sep + QString::number(nickname.length()) + sep + nickname).toUtf8(), QHostAddress(destinationIP), port);
}

