#include "server_finder.h"


Server_Finder::Server_Finder(quint16 Port,
                             QObject *parent) :
    QObject(parent)
{
    socket_finder = new QUdpSocket(this);

    socket_finder->bind(Port);

    connect(socket_finder, SIGNAL(readyRead()), this, SLOT(read()));
}

bool Server_Finder::Send_Request(QString Message_To_Server)
{
    QByteArray datagram = Message_To_Server.toLocal8Bit();
    socket_finder->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, SERVER_PORT);
}


void Server_Finder::read()
{
    while(socket_finder->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket_finder->pendingDatagramSize());
        QHostAddress host;
        socket_finder->readDatagram(datagram.data(), datagram.size(),
                                    &host);
        emit Read_Answer(datagram, host);
    }
}
