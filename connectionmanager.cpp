#include "connectionmanager.h"

ConnectionManager::ConnectionManager(MainWindow *window)
{
    this->window = window;
    udpSocket = new QUdpSocket();
    udpSocket->bind(window->port, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &ConnectionManager::datagramListener);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ConnectionManager::ping);
    timer->setInterval(window->responseTime);
    timer->start();
}

/**
 * @brief Add client to clients list
 * @param client IClient entity
 */
void ConnectionManager::addClient(Client *client) {
    //clients.push_back(client);
    hosts.insert(client->getIP(), client);
    refreshChatters();
}

/**
 * @brief Remove client from clients list
 * @param client IClient entity
 */
void ConnectionManager::removeClient(Client *client) {
    if (hosts.contains(client->getIP())) {
        hosts.remove(client->getIP());
        window->addMessage(tr("%1 left chat").arg(client->getUsername()), Qt::gray);
        refreshChatters();
    }

}

QString ConnectionManager::getNicknameByIP(QHostAddress address) {
    QString nick;
    QHashIterator<QHostAddress, Client *> it(hosts);
    while (it.hasNext()) {
        it.next();
        if (it.key() == address) {
            nick = it.value()->getUsername();
            break;
        }
    }
    return nick;
}

QHostAddress ConnectionManager::getIPbyNickname(QString nickname) {
    QHostAddress ip;
    QHashIterator<QHostAddress, Client *> it(hosts);
    while (it.hasNext()) {
        it.next();
        if (it.value()->getUsername() == nickname) {
            ip = it.key();
            break;
        }
    }
    return ip;
}

/**
 * @brief Checks if length of the payload matches the actual payload
 * @param length length of payload in int
 * @param string Payload
 * @return true if equal
 */
bool ConnectionManager::lengthValidator(int length, QString string) {
    return (length == string.toUtf8().size()) ? true : false;
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
        QHostAddress finalAddress = QHostAddress(senderIP.toIPv4Address());

        // Check block
        // Checking protocol name first
        if (prName == P_TYPE)
        {
            // I feel so bad everytime I work with switch in C++ of not being able to compare variables with QString
            if (prCommand == P_CONNECT)
            {
                if (lengthValidator(prLength, prPayload)) {
                    // add client to QHash
                    new Client(this, prPayload, finalAddress);
                    window->addMessage(tr("%1 has joined").arg(prPayload), Qt::gray);
                    refreshChatters();
                }
            }
            // if the incoming datagram contains message
            else if (prCommand == P_SENDMESSAGE)
            {
                if (lengthValidator(prLength, prPayload))
                {
                    window->addMessage(tr("<%1 | %2> : %3").arg(getNicknameByIP(finalAddress), QTime::currentTime().toString(), prPayload), Qt::black);
                }
            }
            else if (prCommand == P_PRIVATEMSG) {
                if (lengthValidator(prLength, prPayload))
                {
                    window->addMessage(tr("<From %1 | %2> : %3").arg(getNicknameByIP(finalAddress), QTime::currentTime().toString(), prPayload), Qt::blue);
                }
            }
            // if incoming datagram is a ping
            else if (prCommand == P_ALIVE) {
                if (lengthValidator(prLength, prPayload)) {
                    for (int i = 0; i < hosts.size(); i++) {
                        if (hosts.contains(finalAddress)) {
                            hosts[finalAddress]->resetTimer();
                        }
                        else {
                            new Client(this, prPayload, finalAddress);
                            window->addMessage(tr("%1 in chat").arg(prPayload), Qt::gray);
                            refreshChatters();
                        }
                    }
                }
                // or add new client to list and show him in chat


            }
        }
    }
}

/**
 * @brief ConnectionManager::refreshChatters
 */
void ConnectionManager::refreshChatters() {
    QStringList *list = new QStringList;
    QHashIterator<QHostAddress, Client *> it(hosts);
    while (it.hasNext()) {
        it.next();
        list->append(hosts[it.key()]->getUsername());
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
    udpSocket->writeDatagram((P_TYPE + sep + P_SENDMESSAGE + sep + QString::number(msg.toUtf8().size()) + sep + msg).toUtf8(), QHostAddress(window->destinationIP), window->port); //172.27.24.255 192.168.0.104
}

/**
 * @brief ConnectionManager::sendPrivateMessage
 * @param msg
 */
void ConnectionManager::sendPrivateMessage(QString msg, QHostAddress address)
{
    udpSocket->writeDatagram((P_TYPE + sep + P_PRIVATEMSG + sep + QString::number(msg.toUtf8().size()) + sep + msg).toUtf8(), QHostAddress(address), window->port); //172.27.24.255 192.168.0.104
}

/**
 * @brief ConnectionManager::sayHi
 */
void ConnectionManager::sayHi()
{
    udpSocket->writeDatagram((P_TYPE + sep + P_CONNECT + sep + QString::number(window->nickname.toUtf8().size()) + sep + window->nickname).toUtf8(), QHostAddress(window->destinationIP), window->port); //172.27.24.255 192.168.0.104
}

/**
 * @brief ConnectionManager::ping
 */
void ConnectionManager::ping()
{
    udpSocket->writeDatagram((P_TYPE + sep + P_ALIVE + sep + QString::number(window->nickname.toUtf8().size()) + sep + window->nickname).toUtf8(), QHostAddress(window->destinationIP), window->port);
}

void ConnectionManager::checkRet(bool ret,const MIPErrorBase &obj)
{
    if (!ret)
    {
       std::cerr << obj.getErrorString() << std::endl;
        exit(-1);
    }
}

void ConnectionManager::call()
{
#ifdef WIN32
    WSADATA dat;
    WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
#ifdef MIPCONFIG_SUPPORT_PORTAUDIO
    std::string errStr;

    if (!MIPPAInputOutput::initializePortAudio(errStr))
    {
        std::cerr << "Can't initialize PortAudio: " << errStr << std::endl;
        return -1;
    }
#endif // MIPCONFIG_SUPPORT_PORTAUDIO
    MIPAudioSessionParams Aparams;
    bool ret;

    int audioPort = 14002;

    Aparams.setPortbase(audioPort);
    Aparams.setSpeexIncomingPayloadType(97);
    Aparams.setOpusIncomingPayloadType(98);

    ret = audioSess.init(&Aparams);
    checkRet(ret, audioSess);

    QHashIterator<QHostAddress, Client *> it(hosts);
    while (it.hasNext()) {
        it.next();
        ret = audioSess.addDestination(RTPIPv4Address(it.key().toIPv4Address(), audioPort));
    }
}

void ConnectionManager::hangup() {
    audioSess.destroy();
#ifdef MIPCONFIG_SUPPORT_PORTAUDIO
    MIPPAInputOutput::terminatePortAudio();
#endif // MIPCONFIG_SUPPORT_PORTAUDIO
#ifdef WIN32
    WSACleanup();
#endif // WIN32
}

