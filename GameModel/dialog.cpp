#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(PORT, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    server = new Server(this);
    server->StartServer(PORT);
    connect(server, SIGNAL(MessageCatchings(int,QString)), this, SLOT(MessageCatching(int,QString)));
    connect(server, SIGNAL(New_Client_Connected(int)), this, SLOT(New_Client_Connected(int)));
    connect(server, SIGNAL(disconnected(int)), this, SLOT(Disconnect(int)));

    Client_Count = 0;

    Msg_Format = new MessageFormat(server);

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(time_out()));
    Timer->start(10);

}

dialog::~dialog()
{
    delete ui;
}

void dialog::Send_Message(quint16 port, QHostAddress host, QString Message)
{
    QByteArray datagram = Message.toLocal8Bit();
    udpSocket->writeDatagram(datagram, host, port);
}

TPlayerType dialog::Translate_Player_Type(QString Text)
{
    if(Text == "<None>")
        return PT_None;
    if(Text == "Bot")
        return PT_Bot;
    if(Text == "Player")
        return PT_Player;
}

QString dialog::Translate_Player_Type(TPlayerType Type)
{
    switch(Type)
    {
        case PT_None:
        {
            return "<None>";
            break;
        }
        case PT_Bot:
        {
            return "Bot";
            break;
        }
        case PT_Player:
        {
            return "Player";
            break;
        }

    }
}



void dialog::Message(QString Text)
{
    QMessageBox msg;
    msg.setText(Text);
    msg.exec();
}

void dialog::Message(int Text)
{
    QMessageBox msg;
    msg.setText(QString::number(Text));
    msg.exec();
}

void dialog::MessageF(QString Text)
{
    QFile file("E:\\out3.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << Text << '\n';
    file.close();

}

void dialog::MessageF(int Text)
{
    MessageF(QString::number(Text));
}

QString dialog::join(char spliter, QString text, ...)
{
    QString *p = &text;
    QString Sum = "";
    int count = 0;
    while(p)
    {
        Sum += (*p) + spliter;
        p++;
        count++;
    }
    return Sum;
}

void dialog::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        QHostAddress Address;
        quint16 Port;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &Address, &Port);

        if(datagram == SERVER_PASSWORD)
        {
            Address_Sender.push_back(Address);
            Port_Sender.push_back(Port);

            Send_Message(Port_Sender[Client_Count], Address_Sender[Client_Count], CLIENT_PASSWORD);

            Client_Count++;
        }
    }
}

void dialog::MessageCatching(int clientNum, QString Text)
{
    QStringList Buf_Text = Text.split("}");
    for(int Id_Msg = 0; Id_Msg < Buf_Text.size()-1; Id_Msg++)
    {
        //Message(Text);
        QStringList list = Buf_Text[Id_Msg].split("!");
        int Theme = list[0].toInt();
        QString Data = list[1];

        //MessageF("Client: " + QString::number(clientNum) + " " + Client_List[clientNum]->Name + " Theme: " + QString::number(Theme) + " Data: " + Data);

        switch(Theme)
        {
            case TM_MY_NAME:
            {
                for(int i=0; i < Client_Count; i++)
                {
                    if(Data == Client_List[i]->Name)
                    {
                        Data = "/" + Data;
                    }
                }

                Client_List[clientNum]->Name = Data;
                Msg_Format->Send_Message(clientNum, TM_ANSWER_MY_NAME, Client_List[clientNum]->Name);
                break;
            }

            case TM_CREATE_NEW_LOBBY_NAME:
            {
                bool flag = true;
                for(int i=0; i<Lobby_List.size(); i++)
                {
                    flag = Lobby_List[i].Name != Data;
                }
                if(flag)
                {
                    Lobby lobby;
                    lobby.Name = Data;
                    lobby.Player_Number = 0;
                    lobby.Bot_Number = 0;
                    Lobby_List.push_back(lobby);
                    Client_List[clientNum]->Lobby_ID = Lobby_List.size()-1;
                   // Message("New lobby size: " + QString::number(Client_List[clientNum]->Lobby_ID) + " Client: " + QString::number(clientNum));
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_NAME, QString::number(TM_ADMIN));
                }
                else
                {
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_NAME, QString::number(TM_ERROR));
                }
                break;
            }
            case TM_CREATE_NEW_LOBBY_PL1:
            {
           // MessageF("PL_1 " + Data);
                bool flag = false;
                Lobby_List[Lobby_List.size()-1].Player_Type_1 = Translate_Player_Type(Data);
                if(Lobby_List[Lobby_List.size()-1].Player_Type_1 == PT_Player)
                    Lobby_List[Lobby_List.size()-1].Player_Number++;
                else
                    if(Lobby_List[Lobby_List.size()-1].Player_Type_1 == PT_Bot)
                          Lobby_List[Lobby_List.size()-1].Bot_Number++;

                flag = true;
                if(flag)
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL1, QString::number(TM_SUCCESES));
                else
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL1, QString::number(TM_ERROR));
                break;
            }
            case TM_CREATE_NEW_LOBBY_PL2:
            {
           // MessageF("PL_2 " + Data);
                bool flag = false;
                Lobby_List[Lobby_List.size()-1].Player_Type_2 = Translate_Player_Type(Data);
                if(Lobby_List[Lobby_List.size()-1].Player_Type_2 == PT_Player)
                    Lobby_List[Lobby_List.size()-1].Player_Number++;
                else
                    if(Lobby_List[Lobby_List.size()-1].Player_Type_2 == PT_Bot)
                          Lobby_List[Lobby_List.size()-1].Bot_Number++;
                flag = true;
                if(flag)
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL2, QString::number(TM_SUCCESES));
                else
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL2, QString::number(TM_ERROR));

                break;
            }
            case TM_CREATE_NEW_LOBBY_PL3:
            {
               // MessageF("PL_3 " + Data);
                bool flag = false;
                Lobby_List[Lobby_List.size()-1].Player_Type_3 = Translate_Player_Type(Data);
                if(Lobby_List[Lobby_List.size()-1].Player_Type_3 == PT_Player)
                    Lobby_List[Lobby_List.size()-1].Player_Number++;
                else
                    if(Lobby_List[Lobby_List.size()-1].Player_Type_3 == PT_Bot)
                          Lobby_List[Lobby_List.size()-1].Bot_Number++;
                flag = true;
                if(flag)
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL3, QString::number(TM_SUCCESES));
                else
                    Msg_Format->Send_Message(clientNum, TM_ANSWER_CREATE_NEW_LOBBY_PL3, QString::number(TM_ERROR));

                break;
            }
            case TM_LOBBY_LIST:
            {
                QString Buff = "";
                if(Lobby_List.size()>0)
                {
                    for(int i=0; i<Lobby_List.size()-1; i++)
                    {
                        Buff += Lobby_List[i].Name+"*";
                    }
                    Buff += Lobby_List[Lobby_List.size()-1].Name;
                }
                Msg_Format->Send_Message(clientNum, TM_ANSWER_LOBBY_LIST, Buff);
                break;
            }
            case TM_CONNECT_TO_LOBBY:
            {
                QStringList list = Data.split(";");
                Data = list[0];
                bool ADMIN = false;
                if(list.size()>1)
                    ADMIN = list[1] == QString::number(TM_ADMIN);

                int index = -1;
                for(int i = 0; i < Lobby_List.size(); i++)
                {
                    if(Lobby_List[i].Name == Data)
                    {
                        index = i;
                        if(Lobby_List[i].GameClient.size() - Lobby_List[i].Player_Number > 0)
                        {
                            Lobby_List[i].Add_Client(Client_List[clientNum]);
                            if(ADMIN)
                                Lobby_List[i].set_Admin_ID(clientNum);
                            Client_List[clientNum]->Lobby_ID = i;
                            Msg_Format->Send_Message(clientNum, TM_ANSWER_CONNECT_TO_LOBBY, Data);
                        }
                        else
                        {
                            Msg_Format->Send_Message(clientNum, TM_ANSWER_CONNECT_TO_LOBBY, QString::number(TM_ERROR));
                        }

                        break;
                    }
                }



                //Msg_Format->Send_Message(clientNum, TM_ANSWER_CONNECT_TO_LOBBY, QString::number(TM_ERROR));


                break;
            }
            case TM_LOBBY_INFORM:
            {
                int Lobby_ID = -1;
                for(int i=0; i < Lobby_List.size(); i++)
                {
                    if(Lobby_List[i].Name == Data)
                    {
                        Lobby_ID = i;
                        break;
                    }
                }

                if(Lobby_ID >= 0)
                {
                    QString Clients_Name = "";
                    for(int i=0; i < Lobby_List[Lobby_ID].Client_Name.size(); i++)
                    {
                        Clients_Name += Lobby_List[Lobby_ID].Client_Name[i]+"@";
                    }

                    QString Player_1 = Translate_Player_Type(Lobby_List[Lobby_ID].Player_Type_1);
                    QString Player_2 = Translate_Player_Type(Lobby_List[Lobby_ID].Player_Type_2);
                    QString Player_3 = Translate_Player_Type(Lobby_List[Lobby_ID].Player_Type_3);

                    QString New_Data = Lobby_List[Lobby_ID].Name+","+Clients_Name+","+Player_1+","+Player_2+","+Player_3;

                    for(int i = 0; i < Lobby_List[Lobby_ID].GameClient.size(); i++)
                    {
                        Msg_Format->Send_Message(Lobby_List[Lobby_ID].GameClient[i]->clientNum, TM_ANSWER_LOBBY_INFORM, New_Data);
                    }

    //                Message(Lobby_List[Lobby_ID].GameClient.size());
    //                Message(Lobby_List[Lobby_ID].Player_Number);

                    if(Lobby_List[Lobby_ID].GameClient.size() == Lobby_List[Lobby_ID].Player_Number)
                    {
                       // Message(Lobby_List[Lobby_ID].Player_Number);
                        for(int i = 0; i < Lobby_List[Lobby_ID].GameClient.size(); i++)
                        {
                            Msg_Format->Send_Message(Lobby_List[Lobby_ID].GameClient[i]->clientNum,
                                                     TM_ANSWER_START_GAME, QString::number(TM_NONE));
                        }
                        Lobby_List[Lobby_ID].set_Game_Stage(GS_Timer_To_Start);
                    }

                    //Msg_Format->Send_Message(clientNum, TM_ANSWER_LOBBY_INFORM, New_Data);
                }

                break;
            }

            case TM_KEY_PRESSED:
            {
                int Lobby_Id = Client_List[clientNum]->Lobby_ID;

                TClient_Message buf;
                buf.Theme = Theme;
                buf.Data = Data;
                buf.ID = clientNum;

                Lobby_List[Lobby_Id].Add_Client_Message(buf.ID, buf.Theme, buf.Data);
                break;
            }

        }
    }
}

void dialog::New_Client_Connected(int clientNum)
{
    Client *client = new Client(clientNum, this);
    Client_List.push_back(client);
}

void dialog::on_pushButton_clicked()
{
    Message(Lobby_List.size());
}

void dialog::Disconnect(int clientNum)
{

    if(Client_List[clientNum]->Lobby_ID >= 0)
    {
        Lobby_List[Client_List[clientNum]->Lobby_ID].Delete_Client(clientNum);
    }
    Client_List[clientNum]->Delete();
}

void dialog::time_out()
{
    for(int i = 0; i < Lobby_List.size(); i++)
    {
        vector<TTheme_Data> theme_data = Lobby_List[i].Process();
       // MessageF(QString::number(theme_data.Theme) + " " + QString::number(theme_data.ID) + " " + theme_data.Data);

        for(int i2 = 0; i2 < theme_data.size(); i2++)
        {
//            MessageF(QString::number(theme_data[i2].ID) + " " + QString::number(theme_data[i2].Theme)
//                     + " " + theme_data[i2].Data);
            switch(theme_data[i2].ID)
            {
                case -2:
                {
                    for(int j = 0; j < Lobby_List[i].GameClient.size(); j++)
                    {
                        theme_data[i2].ID = Lobby_List[i].GameClient[j]->clientNum;
                        Msg_Format->Send_Message(theme_data[i2]);
                    }
                    break;
                }

                case -1:
                {
                    break;
                }

                default:
                {
                    if(theme_data[i2].Theme != -1)
                    {
                        Msg_Format->Send_Message(theme_data[i2]);
                    }
                    break;
                }
            }
        }


    }
}
