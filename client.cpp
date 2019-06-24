#include "client.h"
#include "connectionmanager.h"

Client::Client(QString *user, QHostAddress *address)
{
    username = user;
    ip = address;
    time = 0;
}

void update() {

}

QString Client::getUsername() {
    return *username;
}
