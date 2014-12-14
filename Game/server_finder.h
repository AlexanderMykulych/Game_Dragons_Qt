#ifndef SERVER_FINDER_H
#define SERVER_FINDER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include "propertis.h"

class Server_Finder : public QObject
{
    Q_OBJECT
public:
    explicit Server_Finder(quint16 Port,
                           QObject *parent = 0);
    bool Send_Request(QString Message_To_Server);
private:
    QUdpSocket *socket_finder;
    quint16 Port;
signals:
    void Read_Answer(QString Message_From_Server, QHostAddress Address);
public slots:
    void read();
};

#endif // SERVER_FINDER_H
