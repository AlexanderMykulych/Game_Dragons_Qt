#ifndef SERVER_H
#define SERVER_H

#include "gameserver.h"

class Server : public GameServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    //1st (Port where we listening
    void StartServer(quint16 Port);
    //2st (We send message to client whis Name: ThreadID, Message: Text)
    void SendMessage(int ThreadID, QString Text);
    void SendMessage(int ThreadID, int Text);
private:
    //for debug
    void Message(QString Text);
    //clients
    threade *Threade[100];
    //count of client
    int ThreadeCount;
signals:
    //thread emit this signal when we catch message from client
    void MessageCatchings(int clientNum, QString Text);

    void New_Client_Connected(int clientNum);

    void disconnected(int clientNum);
public slots:
    //3st (When server catch message from client Name: clientNum, Message: Text)
    void MessageCatching(int clientNum, QString Text);
    //when happend error whis server
    void error(QTcpSocket::SocketError);
    void disconnect(int clientNum);
protected:
    //when new client whant to connect
    void incomingConnection(int socketDescriptor);

};

#endif // SERVER_H
