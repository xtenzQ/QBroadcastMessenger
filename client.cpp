#include "client.h"
#include "connectionmanager.h"

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
    this->manager->refreshChatters();

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

void Client::update() {

}

/**
 * @brief Removes client from list
 */
void Client::removeMe() {
    manager->removeClient(this);
    manager->refreshChatters();
}

void Client::display() {

}
