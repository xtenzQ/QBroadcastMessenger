#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QTextEdit *messageLineEdit, QTextEdit *messageTextEdit, QListWidget *chatListTextEdit)
{
    myMessageTextEdit = messageLineEdit;
    messagesTextEdit = messageTextEdit;
    chatters = chatListTextEdit;

    udpSocket = new QUdpSocket();
    udpSocket->bind(port, QUdpSocket::ShareAddress);

    timer = new QTimer(this);
    timer->setInterval(responseTime);
    timer->start();

    connect(udpSocket, &QUdpSocket::readyRead, this, &ConnectionManager::datagramListener);
    connect(timer, &QTimer::timeout, this, &ConnectionManager::ping);
}

/**
 * @brief Add client to clients list
 * @param client IClient entity
 */
void ConnectionManager::addClient(IClient *client) {
    clients.push_back(client);
    refreshChatters();
    /*chattersList.insert(*ip, *nick);
    timeList.insert(*ip, 0);
    refreshChatters();*/
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
    /*chattersList.remove(*ip);
    timeList.remove(*ip);
    refreshChatters();*/
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
                    displayServiceMessage(tr("%1 has joined").arg(prPayload));
                }
            }
            // if the incoming datagram contains message
            else if (prCommand == P_SENDMESSAGE)
            {
                if (lengthValidator(prLength, prPayload))
                {
                    displayTextMessage(tr("%1 : %2").arg(chattersList.value(senderIP), prPayload));
                }
            }
            // if incoming datagram is a ping
            else if (prCommand == P_ALIVE)
            {
                if (lengthValidator(prLength, prPayload))
                {
                    // check if ping incoming from existing client
                    if (chattersList.contains(senderIP))
                    {
                        if (timeList.value(senderIP) > 0) {
                            timeList[senderIP] = timeList.value(senderIP) - 1;
                        }
                    }
                    // or add new client to list and show him in chat
                    else
                    {
                        addClient(&senderIP, &prPayload);
                        displayServiceMessage(tr("%1 in chat").arg(prPayload));
                    }
                }
            }
        }
    }
}

/**
 * @brief Check pings to reset timers
 */
void ConnectionManager::ping()
{
    // Not the best decision actually but I failed to implement subject-observer pattern
    // (not idea how to avoid circular dependency) :(
    // maybe, someday...
    foreach (int time, timeList.values())
    {
        QHostAddress address = timeList.key(time);
        if (time > 2)
        {
            displayServiceMessage(tr("%1 left chat").arg(chattersList.value(address)));
            removeClient(&address);
        }
        else
        {
            timeList[address] = time++;
        }
    }
}

/**
 * @brief Displays gray-colored message
 * @param msg message
 */
void ConnectionManager::displayServiceMessage(QString msg) {
    messagesTextEdit->setTextColor(QColor(Qt::gray));
    messagesTextEdit->append(msg);
}

/**
 * @brief Displays default message
 * @param msg
 */
void ConnectionManager::displayTextMessage(QString msg) {
    messagesTextEdit->setTextColor(QColor(Qt::black));
    messagesTextEdit->append(msg);
}

/**
 * @brief ConnectionManager::refreshChatters
 */
void ConnectionManager::refreshChatters() {
    chatters->clear();
    foreach (QString item, chattersList)
    {
        chatters->addItem(item);
    }
}

bool ConnectionManager::isEmpty()
{
    if ((lineEditName->text().isEmpty() && lineEditName->isEnabled() == true) || (lineEditMessage->text().isEmpty() && lineEditMessage->isEnabled() == true)) {
        return true;
    }
    return false;
}

void ConnectionManager::clearMessage()
{
    lineEditMessage->clear();
}

void Sender::sendMessage()
{
    if (!isEmpty())
    {
        if (firstTime == true) {
            sendGreeting();
            firstTime = false;
            lineEditName->setEnabled(firstTime);
            lineEditMessage->setEnabled(!firstTime);
            buttonSend->setText("Отправить");
            timer->start();
        }
        else {
            QString message = lineEditMessage->text();
            QString len = QString::number(message.length());
            QByteArray datagram = (P_SENDMESSAGE + len + P_DIVIDER + message).toUtf8();
            udpSocket->writeDatagram(datagram, QHostAddress("10.24.34.181"), 14000); //172.27.24.255 192.168.0.104
            clearMessage();
        }
    }
}


void ConnectionManager::sendGreeting()
{
    QString name = lineEditName->text();
    QString len = QString::number(name.length());
    QByteArray datagram = (P_CONNECT + len + P_DIVIDER + name).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress("10.24.34.181"), 14000);
}

void ConnectionManager::sendAlive()
{
    QString name = lineEditName->text();
    QString len = QString::number(name.length());
    QByteArray datagram = (P_ALIVE + len + P_DIVIDER + name).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress("10.24.34.181"), 14000);
}

