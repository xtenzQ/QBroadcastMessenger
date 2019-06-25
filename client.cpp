#include "client.h"

/**
 * @brief Concrete client
 * @param manager reference to mmanager
 * @param username client's username
 * @param address IP address
 */
Client::Client(ConnectionManager *manager, QString username, QHostAddress address)
{
    // sets fields
    this->username = username;
    this->address = address;
    this->manager = manager;

    // add client to list
    this->manager->addClient(this);

    // timer to remove
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(removeMe()));
    timer->setInterval(20000);
    timer->start();
}

/**
 * @brief Resets timer
 */
void Client::resetTimer() {
    timer->stop();
    timer->start();
}

/**
 * @brief Removes client from list
 */
void Client::removeMe() {
    manager->removeClient(this);
}
