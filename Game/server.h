#ifndef SERVER_H
#define SERVER_H

#include "gameserver.h"

class server : public GameServer
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    //1st (Port where we listening
    void StartServer(qint64 Port);
    //2st (We send message to client whis Name: ThreadID, Message: Text)
    void SendMessage(int ThreadID, QString Text);
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
public slots:
    //3st (When server catch message from client Name: clientNum, Message: Text)
    void MessageCatching(int clientNum, QString Text);
    //when happend error whis server
    void error(QTcpSocket::SocketError);
protected:
    //when new client whant to connect
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
