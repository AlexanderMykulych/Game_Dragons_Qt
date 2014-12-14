#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>
#include <QString>
#include <QMessageBox>
#include "propertis.h"
#include "server.h"
#include <vector>
#include <QTimer>
#include "lobby.h"
#include "TConversation.h"
#include "messageformat.h"
#include <QFile>

using namespace std;

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = 0);
    ~dialog();


private:
    Ui::dialog *ui;


    //////////////SERVER//////////////
    GameServer *server;
    TConversation Conversation;
    MessageFormat *Msg_Format;
    //Find Client
    QUdpSocket *udpSocket;
    void Send_Message(quint16 port, QHostAddress host, QString Message);

    vector<quint16> Port_Sender;
    vector<QHostAddress> Address_Sender;

    int Client_Count;

    int Message_Expected;

    //Lobby
    vector<Lobby> Lobby_List;
    TPlayerType Translate_Player_Type(QString Text);
    QString Translate_Player_Type(TPlayerType Type);

    //Client
    vector<Client*> Client_List;

    //Debug
    void Message(QString Text);
    void Message(int Text);
    void MessageF(QString Text);
    void MessageF(int Text);

    //Help
    QString join(char spliter, QString text, ...);

    //Game
    QTimer *Timer;

private slots:
    void processPendingDatagrams();
    void MessageCatching(int clientNum, QString Text);

    void New_Client_Connected(int clientNum);


    void on_pushButton_clicked();

    void Disconnect(int clientNum);
    //Timer
    void time_out();
};

#endif // DIALOG_H
