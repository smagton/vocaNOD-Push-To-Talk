#ifndef SERVER_H
#define SERVER_H

#include <QtCore>
#include <QtNetwork>


#include "QWsServer.h"
#include "QWsSocket.h"

class Server : public QObject
{
    Q_OBJECT

public:
    Server(int port = 80, QtWebsocket::Protocol protocol = QtWebsocket::Tcp);
    ~Server();

    signals:
    void state(bool);

public slots:
    void processNewConnection();
    void socketDisconnected();
    void processPressed();
    void processReleased(); //TODO peut etre enlever cela des slots pour que ce soit plus propre

private:
    bool connected;
    QtWebsocket::QWsServer* server;
    QtWebsocket::QWsSocket* client;
    bool active;
};

#endif // SERVER_H
