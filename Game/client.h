#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include "gameclient.h"

class Client : public GameClient
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
//    1st (connect to server)
    void ConnectToServer(QString hostAddress, quint16 port);
    //2st (Send message to server)
    void Send_Message(QString Text);
    void Send_Message(int Text);

private:
    //for debug
    void Message(QString text);
    void Message(int numb);
    //server inform fild
    QString HostAddress;
    qint64 Port;
    //client socket
    QTcpSocket *socket;
signals:
    //3st (emit when we catch messege from server)
    void MessageCatching(QString Text);
    void Disconnected();
public slots:
    //when we connected
    void connected();
    //when we disconnected
    void disconnected();
    //when we written to server
    void bytesWritten(qint64 bytes);
    //when we read message from server
    void readyRead();

};

#endif // CLIENT_H
