#include "imanager.h"

/**
 * @brief Add client to clients list
 * @param client IClient entity
 */
void IManager::addClient(IClient *client) {
    _clients.push_back(client);
}

/**
 * @brief Remove client from clients list
 * @param client IClient entity
 */
void IManager::removeClient(IClient *client) {
    int count = _clients.size();
    int i;

    for (i = 0; i < count; i++) {
      if(_clients[i] == client)
      break;
    }
    if(i < count)
     _clients.erase(_clients.begin() + i);
}

void IManager::notify(IClient *) {

}
