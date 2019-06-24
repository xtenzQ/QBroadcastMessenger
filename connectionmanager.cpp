#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(14000, QUdpSocket::ShareAddress);
}

/**
 * @brief Add client to clients list
 * @param client IClient entity
 */
void ConnectionManager::addClient(IClient *client) {
    clients.push_back(client);
}

/**
 * @brief Remove client from clients list
 * @param client IClient entity
 */
void ConnectionManager::removeClient(IClient *client) {
    int count = clients.size();
    int i;

    for (i = 0; i < count; i++) {
      if(clients[i] == client)
      break;
    }
    if(i < count)
     clients.erase(clients.begin() + i);
}

void ConnectionManager::notify(IClient *) {

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
                    new Client(&prPayload, &senderIP);
                }
                if (data.split(sep)[2].toInt() == data.split(sep)[3].length())
                {
                    //addMessage(tr("%1 присоединился").arg(data.split("_")[3]), true);
                    //refreshListWidget();
                }
            }
            else if (data.split("_")[1] == P_SENDMESSAGE)
            {
                if (data.split("_")[2].toInt() == data.split("_")[3].length())
                {
                    //textEditMessages->append(tr("%1 : %2").arg(userList.value(senderIP.toString().split("::ffff:")[1]), data.split("_")[3]));
                    //addMessage(tr("%1 : %2").arg(userList.value(senderIP.toString().split("::ffff:")[1]), data.split("_")[3]), false);
                }
            }
            else if (data.split("_")[1] == P_PRIVATEMSG)
            {
                //...
            }
            else if (data.split("_")[1] == P_ALIVE)
            {
                if (data.split("_")[2].toInt() == data.split("_")[3].length())
                {
                    /*if (userList.contains(senderIP.toString().split("::ffff:")[1]))
                    {
                        if (timeList.value(senderIP.toString().split("::ffff:")[1]) > 0) {
                            int newTime = timeList.value(senderIP.toString().split("::ffff:")[1]) - 1;
                            timeList[senderIP.toString().split("::ffff:")[1]] = newTime;
                        }
                    }
                    else
                    {
                        userList.insert(senderIP.toString().split("::ffff:")[1], data.split("_")[3]);
                        timeList.insert(senderIP.toString().split("::ffff:")[1], 0);
                        addMessage(tr("%1 в чате").arg(data.split("_")[3]), true);
                        refreshListWidget();
                    }*/
                }
            }
        }
        //textEditMessages->append(data);
    }
}
