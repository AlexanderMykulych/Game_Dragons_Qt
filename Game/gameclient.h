#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>

class GameClient : public QObject
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
    //1st (connect to server)
    virtual void ConnectToServer(QString hostAddress, quint16 port)=0;
    //2st (Send message to server)
    virtual void Send_Message(QString Text)=0;
    virtual void Send_Message(int Text)=0;
signals:
    //3st (emit when we catch messege from server)
    void MessageCatching(QString Text);
    void Disconnected();
};

#endif // GAMECLIENT_H
