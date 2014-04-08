#include "Server.h"
#include <iostream>

Server::Server(int port, QtWebsocket::Protocol protocol)
{
    server = new QtWebsocket::QWsServer(this, protocol);
    active = false;
    if (! server->listen(QHostAddress::Any, port))
    {
        std::cout << tr("Error: Can't launch server").toStdString() << std::endl;
        std::cout << tr("QWsServer error : %1").arg(server->errorString()).toStdString() << std::endl;
    }
    else
    {
        std::cout << tr("Server is listening on port %1").arg(port).toStdString() << std::endl;
    }
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(processNewConnection()));
}

Server::~Server()
{
}

void Server::processNewConnection()
{
    client = server->nextPendingConnection();

    QObject::connect(client, SIGNAL(frameReceived(QString)), this, SLOT(processMessage(QString)));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    std::cout << tr("Client connected").toStdString() << std::endl;
    connected = true;
    emit state(true);
}




void Server::socketDisconnected()
{
    QtWebsocket::QWsSocket* socket = qobject_cast<QtWebsocket::QWsSocket*>(sender());
    if (socket == 0)
    {
        return;
    }


    socket->deleteLater();

    std::cout << tr("Client disconnected").toStdString() << std::endl;
    connected = false;
    emit state(false);
}

void Server::processPressed()
{
    QString frame;
    frame = "pressed";
    if(connected){
        if (active == false){
            active = true;
            client->write(frame);
        }
    }
}

void Server::processReleased()
{
    QString frame;
    frame = "released";
    if(connected)
    client->write(frame);
    active = false;
}
