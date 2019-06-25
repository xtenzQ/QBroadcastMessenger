#ifndef ICLIENT_H
#define ICLIENT_H

#include <QtNetwork>
#include <QtWidgets>

/**
 * @brief Interface for the client
 */
class IClient : public QObject
{
Q_OBJECT
public:
    //virtual void message();
    virtual QHostAddress getIP() = 0;
    virtual QString getUsername() = 0;
    virtual void resetTimer() = 0;
};

#endif // ICLIENT_H
