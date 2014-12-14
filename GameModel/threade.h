#ifndef THREADE_H
#define THREADE_H


#include <QThread>
#include <QTcpSocket>
#include <QMessageBox>
#include <QMutex>

class threade : public QThread
{
    Q_OBJECT
public:
    explicit threade(int ID, int clientNum, QObject *parent = 0);
    //run thread
    void run();
    //we send message to client
    void SendMessage(QString Text);
    //mutex for synchronize thread
    QMutex Mutex;
private:
    //socket to connect whis client
    QTcpSocket *socket;
    //client ID
    int SocketDescriptor;
    //client number in server`s thread
    int clientNum;
    //for debug
    void Message(QString Text);

signals:
    //emit when happend error
    void error(QTcpSocket::SocketError socketError);
    //emit when we catch message from client
    void MessageCatching(int clientNum, QString Text);
    void disconnect(int clientNum);
public slots:
    //when we read message from client
    void readyRead();
    //when server disconnect
    void disconnected();
};

#endif // THREADE_H
