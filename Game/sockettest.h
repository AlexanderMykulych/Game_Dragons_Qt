#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QString>

class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QString Adress, QObject *parent = 0);
    void Test();
    void writeMyText(QString Text);
signals:
    void MessageCatch(QString Text);
public slots:
    void connected();
    void disconnected();
    void bytesWritten (qint64 bytes);
    void ReadyRead ();


private:
    QTcpSocket *socket;

};

#endif // SOCKETTEST_H
