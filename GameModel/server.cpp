#include "server.h"

Server::Server(QObject *parent) :
    GameServer(parent)
{
    ThreadeCount = 0;
}

void Server::StartServer(quint16 Port)
{
    if(!listen(QHostAddress::Any, Port))
    {
        Message("Couldn start to server");
    }
}

void Server::SendMessage(int ThreadID, QString Text)
{
    Threade[ThreadID]->SendMessage(Text);
}

void Server::SendMessage(int ThreadID, int Text)
{
    Threade[ThreadID]->SendMessage(QString::number(Text));
}

void Server::Message(QString Text)
{
    QMessageBox msg;
    msg.setText(Text);
    msg.exec();
}

void Server::MessageCatching(int clientNum, QString Text)
{
    emit MessageCatchings(clientNum,Text);
}



void Server::error(QAbstractSocket::SocketError)
{
    Message("Error connection");
}



void Server::incomingConnection(int socketDescriptor)
{
    //Message(QString::number(ThreadeCount) + " client is connected to me!!!");
    Threade[ThreadeCount] = new threade(socketDescriptor, ThreadeCount, this);
    connect(Threade[ThreadeCount], SIGNAL(finished()), Threade[ThreadeCount], SLOT(deleteLater()));
    connect(Threade[ThreadeCount], SIGNAL(MessageCatching(int,QString)),
            this, SLOT(MessageCatching(int,QString)));
    connect(Threade[ThreadeCount], SIGNAL(error(QTcpSocket::SocketError)),
            this, SLOT(error(QTcpSocket::SocketError)));
    connect(Threade[ThreadeCount], SIGNAL(disconnect(int)), this, SLOT(disconnect(int)));

    emit New_Client_Connected(ThreadeCount);

    ThreadeCount++;
    Threade[ThreadeCount-1]->run();
}

void Server::disconnect(int clientNum)
{
   // Message(QString::number(clientNum) + " is disconnected!!!");
    emit disconnected(clientNum);
}
