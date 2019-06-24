#include "client.h"
#include "connectionmanager.h"

Client::Client(QString *user, QHostAddress *address)
{
    username = user;
    ip = address;

    ConnectionManager::GetInstance().addClient(this);
    // set timer to remove itself on expire
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ConnectionManager::GetInstance().removeClient(this)));
    timer->setInterval(20000);
    timer->start();
}

void update() {

}
