#ifndef IMANAGER_H
#define IMANAGER_H
#include <QtWidgets>
#include <QtNetwork>
#include "iclient.h"

/**
 * @brief Interface for the Manager
 */
class IManager : public QObject {
Q_OBJECT

public:

    /**
     * Register new client
     * @brief addClient client object to be registered
     */
    virtual void addClient(IClient *) = 0;

    /**
     * Remove existing client
     * @brief removeClient client object to be unregistered
     */
    virtual void removeClient (IClient *) = 0;

    /**
     * @brief notify
     */
    virtual void sendMessage(QString *) = 0;

};

#endif // IMANAGER_H
