#include "sockettest.h"

SocketTest::SocketTest(QString Adress, QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    QObject::connect (socket, SIGNAL(connected()), this, SLOT(connected()));
    QObject:: connect (socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    QObject::connect (socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    QObject::connect (socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
qDebug() <<"connecting..."   ;
socket->connectToHost(Adress,1234);
if (!socket->waitForConnected(1000))
{
    qDebug()<<"Error:"<< socket->errorString();
}
}


void SocketTest::Test()
{
    socket = new QTcpSocket(this);
    QObject::connect (socket, SIGNAL(connected()), this, SLOT(connected()));
    QObject:: connect (socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    QObject::connect (socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    QObject::connect (socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
qDebug() <<"connecting...";
socket->connectToHost("127.0.0.1",1234);
if (!socket->waitForConnected(1000))
{
    qDebug()<<"Error:"<< socket->errorString();
}
}

void SocketTest::writeMyText(QString Text)
{
    socket->write(Text.toLocal8Bit());
}
void SocketTest::connected()
{
qDebug() <<"Connected!"   ;
}
void SocketTest::disconnected()
{
    qDebug() <<"Disconnected!"   ;
}
void SocketTest::bytesWritten (qint64 bytes)
{

}
void SocketTest::ReadyRead ()
{
           QString Text = socket->readAll();
           emit MessageCatch(Text);
}
