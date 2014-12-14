#include "threade.h"

threade::threade(int ID, int clientNum, QObject *parent) :
    QThread(parent)
{
    SocketDescriptor = ID;
    this->clientNum = clientNum;
}

void threade::run()
{
    socket = new QTcpSocket(this);
    if(!socket->setSocketDescriptor(SocketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    exec();
}

void threade::SendMessage(QString Text)
{
    Mutex.lock();
    socket->write(Text.toLocal8Bit());
    Mutex.unlock();
}

void threade::Message(QString Text)
{
    QMessageBox msg;
    msg.setText(Text);
    msg.exec();
}

void threade::readyRead()
{
    QByteArray Data;
    Data = socket->readAll();
    emit MessageCatching(clientNum, Data);
}

void threade::disconnected()
{
    emit disconnect(clientNum);
    socket->deleteLater();

    exit(0);
}
