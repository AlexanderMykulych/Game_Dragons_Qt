#include "server.h"

server::server(QObject *parent) :
    GameServer(parent)
{
    ThreadeCount = 0;
}

void server::StartServer(qint64 Port)
{
    if(!listen(QHostAddress::Any, Port))
    {
        Message("Couldn start to server");
    }
}

void server::SendMessage(int ThreadID, QString Text)
{
    Threade[ThreadID]->SendMessage(Text);
}

void server::Message(QString Text)
{
    QMessageBox msg;
    msg.setText(Text);
    msg.exec();
}

void server::MessageCatching(int clientNum, QString Text)
{
    emit MessageCatchings(clientNum,Text);
}



void server::error(QAbstractSocket::SocketError)
{
    Message("Error connection");
}



void server::incomingConnection(int socketDescriptor)
{
  //  Message(QString::number(ThreadeCount));
    Threade[ThreadeCount] = new threade(socketDescriptor, ThreadeCount);
    connect(Threade[ThreadeCount], SIGNAL(finished()), Threade[ThreadeCount], SLOT(deleteLater()));
    connect(Threade[ThreadeCount], SIGNAL(MessageCatching(int,QString)),
            this, SLOT(MessageCatching(int,QString)));
    connect(Threade[ThreadeCount], SIGNAL(error(QTcpSocket::SocketError)),
            this, SLOT(error(QTcpSocket::SocketError)));
    ThreadeCount++;
    Threade[ThreadeCount-1]->run();
}
