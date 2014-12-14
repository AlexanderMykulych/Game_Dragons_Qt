#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QMessageBox>
#include "threade.h"

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = 0);
    //1st (Port where we listening
    virtual void StartServer(quint16 Port)=0;
    //2st (We send message to client whis Name: ThreadID, Message: Text)
    virtual void SendMessage(int ThreadID, QString Text)=0;
    virtual void SendMessage(int ThreadID, int Text)=0;
signals:
    //thread emit this signal when we catch message from client
    void MessageCatchings(int clientNum, QString Text);
};

#endif // GAMESERVER_H
