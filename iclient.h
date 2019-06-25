#ifndef ICLIENT_H
#define ICLIENT_H

#include <QtNetwork>
#include <QtWidgets>

/**
 * @brief Interface for the client
 */
class IClient
{

public:
    virtual void message();
    virtual QHostAddress getIP();
    virtual QString getUsername();
    virtual void resetTimer();
};

#endif // ICLIENT_H
