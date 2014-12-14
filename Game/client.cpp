#include "client.h"


Client::Client(QObject *parent):
    GameClient(parent)
{

}

void Client::ConnectToServer(QString hostAddress, quint16 port)
{
    //create client socket
    socket = new QTcpSocket(this);
    //connect signal to slot
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //tell that client connecting

    socket->connectToHost(hostAddress, port);
    if(!socket->waitForConnected(5000))
    {
        Message("Error connecting to server:\nHost Address: "
                + HostAddress +"\nPort: " +QString::number(Port));
    }
}

void Client::Send_Message(QString Text)
{
    socket->write(Text.toLocal8Bit());
}

void Client::Send_Message(int Text)
{
    socket->write(QString::number(Text).toLocal8Bit());
}

void Client::Message(QString text)
{
    QMessageBox msg;
    msg.setText(text);
    msg.exec();
}

void Client::Message(int numb)
{
    QMessageBox msg;
    msg.setText(QString::number(numb));
    msg.exec();
}

void Client::connected()
{
    //When we connected to server

}

void Client::disconnected()
{
    //when we disconnected from server
    emit Disconnected();
}

void Client::bytesWritten(qint64 bytes)
{
    //when we get message from server
}

void Client::readyRead()
{
    //when we read message
    //Message();
    emit MessageCatching(socket->readAll());
}
