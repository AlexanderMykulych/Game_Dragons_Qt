#include "lobby.h"

Lobby::Lobby()
{
    Player_Number = 0;
    set_Game_Stage(GS_None);
    EnemyIsAlive = false;
    //
    LoadAll();
}

void Lobby::Add_Client(Client *New_Client)
{
    Client_Name.push_back(New_Client->Name);
    GameClient.push_back(New_Client);
}



void Lobby::MessageL(QString Text)
{
    QFile file("E:\\out3.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << Text << '\n';
    file.close();
}

vector<TTheme_Data> Lobby::Process()
{
    vector<TTheme_Data> v_Buf_TD;

    TTheme_Data buf_TD;
    buf_TD.ID = -1;
    buf_TD.Theme = -1;
    buf_TD.Data = "";

    switch(Game_Stage)
    {
        case GS_Timer_To_Start:
        {
            buf_TD.ID = -2;
            buf_TD.Theme = TM_ANSWER_TIMER_START;
            buf_TD.Data = QString::number(TS_Counter);
            if(TS_Counter>=0)
                TS_Counter -= ++TS_Timer_Counter%TS_Timer_Change_Lim == 0;
            else
            {
                buf_TD.Theme = TM_ANSWER_START;
                buf_TD.Data = QString::number(TM_NONE);
                Game_Stage = GS_Player_Config;
            }
            v_Buf_TD.push_back(buf_TD);
            break;
        }
        case GS_Player_Config:
        {
            for(int i = 0; i < GameClient.size();i++)
            {
                GameClient[i]->set_Width(DRAGON_WIDTH);
                GameClient[i]->set_Height(DRAGON_HEIGHT);

                int sector_width = CLIENT_SCREEN_WIDTH/GameClient.size();
                int X = sector_width*i + (sector_width - DRAGON_WIDTH) / 2;
                int Y = CLIENT_SCREEN_HEIGHT - DRAGON_HEIGHT;

                GameClient[i]->set_X(X);
                GameClient[i]->set_Y(Y);
            }


            buf_TD.ID = -2;
            buf_TD.Theme = TM_ANSWER_PLAYER_CONFIG;


            Composer Message('*');

            Message.Add(GameClient.size());

            for(int i = 0; i < GameClient.size(); i++)
            {
                Composer Player('#');
                Player.Add(GameClient[i]->Name);
                Player.Add(GameClient[i]->get_X());
                Player.Add(GameClient[i]->get_Y());
                Player.Add(GameClient[i]->get_Width());
                Player.Add(GameClient[i]->get_Height());

                Message.Add(Player.get_Composite());
            }

            buf_TD.Data = Message.get_Composite();

            Game_Stage = GS_Start;

            v_Buf_TD.push_back(buf_TD);
            break;
        }

        case GS_Start:
        {



        ////EnemY   is Fire
            for(int i = 0; i < G_Enemy.size(); i++)
            {
                Bullet *bullet = G_Enemy[i]->do_Fire();
                if(bullet)
                    G_Bullet.push_back(bullet);
            }


        ///Collision

            for(int i = 0; i < G_Bullet.size(); i++)
            {
                if(!(G_Bullet[i]->get_X()>= 0 && G_Bullet[i]->get_X() + G_Bullet[i]->get_Width() <= CLIENT_SCREEN_WIDTH
                     && G_Bullet[i]->get_Y()>= 0 && G_Bullet[i]->get_Y() + G_Bullet[i]->get_Height() <= CLIENT_SCREEN_HEIGHT))
                {
                    G_Bullet.erase(G_Bullet.begin() + i);
                }
            }

        /// Bullet with enemy
            for(int i = 0; i < G_Bullet.size(); i++)
            {
                if(G_Bullet[i]->get_Type() == BT_Dragon)
                {
                    for(int j = 0; j < G_Enemy.size(); j++)
                    {
                        if(ifCollision(G_Bullet[i]->get_Rect(), G_Enemy[j]->get_Rect()))
                        {
                            //MessageL("Enemy = " + QString::number(j) + " Bullet = " + QString::number(i));
                            buf_TD.ID = -2;
                            buf_TD.Theme = TM_ANSWER_EXPL_POS;

                            Composer Msg('*');
                            Msg.Add(G_Enemy[j]->get_X());
                            Msg.Add(G_Enemy[j]->get_Y());

                            buf_TD.Data = Msg.get_Composite();

                            GameClient[G_Bullet[i]->get_Player_Id()]->EnemyIsDead();

                            DeleteEnemy(G_Enemy, j);
                            DeleteBullet(G_Bullet, i);

                            v_Buf_TD.push_back(buf_TD);
                        }
                    }
                }
            }

        /////BULET with DRAGON
            for(int i = 0; i < G_Bullet.size(); i++)
            {
                if(G_Bullet[i]->get_Type() == BT_Enemy)
                {
                    for(int j = 0; j < GameClient.size(); j++)
                    {
                        if(ifCollision(G_Bullet[i]->get_Rect(), GameClient[j]->get_Rect()))
                        {
                            //MessageL("Enemy = " + QString::number(j) + " Bullet = " + QString::number(i));
                            buf_TD.ID = -2;
                            buf_TD.Theme = TM_ANSWER_EXPL_POS;

                            Composer Msg('*');
                            Msg.Add(GameClient[j]->get_X());
                            Msg.Add(GameClient[j]->get_Y());

                            buf_TD.Data = Msg.get_Composite();

                            GameClient[j]->BulletIsHit();

                            DeleteBullet(G_Bullet, i);

                            v_Buf_TD.push_back(buf_TD);

                        }
                    }
                }
            }


        /////BULET PROCESS
            for(int i = 0; i < G_Bullet.size(); i++)
            {
                G_Bullet[i]->Process();
            }
        ////CLIENT PROCESS
            for(int i = 0; i < GameClient.size(); i++)
            {
                GameClient[i]->Process();
            }

        ////get client message

            TClient_Message cl_msg = get_Client_Message();

            int client_id = 0;

            for(int i = 0; i < GameClient.size(); i++)
            {
                if(GameClient[i]->clientNum == cl_msg.ID)
                {
                    client_id = i;
                    break;
                }
            }

            switch(cl_msg.Theme)
            {

                case TM_KEY_PRESSED:
                {

                    int Key = cl_msg.Data.toInt();
                    switch(Key)
                    {
                        case GGK_Up:
                        {
                            GameClient[client_id]->set_Up();
                            break;
                        }

                        case GGK_Down:
                        {
                            GameClient[client_id]->set_Down();
                            break;
                        }

                        case GGK_Left:
                        {
                            GameClient[client_id]->set_Left();
                            break;
                        }

                        case GGK_Right:
                        {
                            GameClient[client_id]->set_Right();
                            break;
                        }

                        case GGK_Pause:
                        {
                            Game_Stage = GS_Pause;

                            buf_TD.Theme = TM_ANSWER_PAUSE_ON;
                            buf_TD.ID = -2;

                            v_Buf_TD.push_back(buf_TD);
                            break;
                        }

                        case GGK_Fire:
                        {
                            if(GameClient[client_id]->get_Side() == SM_Up || GameClient[client_id]->get_Side() == SM_Down)
                            {
                                Bullet *bullet = GameClient[client_id]->Fire();
                                if(bullet)
                                {
                                    bullet->set_Player_Id(client_id);
                                    G_Bullet.push_back(bullet);
                                }
                            }
                            break;
                        }
                    }

                    break;
                }

            }

        /////Information About enemy and players
        ///
        /// about ENEMY
            {
                vector<QRectF> Target_For_Enemy;
                for(int i = 0; i < GameClient.size(); i++)
                {
                    QRectF R(GameClient[i]->get_X(), GameClient[i]->get_Y(),
                             GameClient[i]->get_Width(), GameClient[i]->get_Height());

                    Target_For_Enemy.push_back(R);
                }

                if(!EnemyIsAlive)
                {
                    for(int i = 0; i < LevelInf[Now_Level-1].Inf.size(); i++)
                    {
                        Create_Enemy(LevelInf[Now_Level - 1].Inf[i], Target_For_Enemy);
                    }
                    EnemyIsAlive = true;
                    buf_TD.Theme = TM_ANSWER_ENEMY_START_POS;
                }
                else
                    buf_TD.Theme = TM_ANSWER_ENEMY_POS;
                buf_TD.ID = -2;

                Composer Message('*');
                int Count = G_Enemy.size();
                Message.Add(Count);

                for(int i = 0; i < Count; i++)
                {

                    G_Enemy[i]->set_Target(Target_For_Enemy);
                    G_Enemy[i]->Process();

                    Composer buf('#');
                    buf.Add(G_Enemy[i]->get_X());
                    buf.Add(G_Enemy[i]->get_Y());
                    buf.Add(G_Enemy[i]->get_Width());
                    buf.Add(G_Enemy[i]->get_Height());
                    buf.Add(G_Enemy[i]->get_Type());
                    Message.Add(buf.get_Composite());
                }

                buf_TD.Data = Message.get_Composite();
                v_Buf_TD.push_back(buf_TD);
            }
        //////about Player
            {
                buf_TD.ID = -2;
                buf_TD.Theme = TM_ANSWER_PLAYER_CONFIG;

                Composer Message('*');

                Message.Add(GameClient.size());

                for(int i = 0; i < GameClient.size(); i++)
                {
                    Composer Player('#');
                    Player.Add(GameClient[i]->Name);
                    Player.Add(GameClient[i]->get_X());
                    Player.Add(GameClient[i]->get_Y());
                    Player.Add(GameClient[i]->get_Width());
                    Player.Add(GameClient[i]->get_Height());
                    Player.Add(GameClient[i]->get_Side( ));

                    Message.Add(Player.get_Composite());
                }

                buf_TD.Data = Message.get_Composite();

                v_Buf_TD.push_back(buf_TD);
            }
        ////about bullets
            buf_TD.ID = -2;
            buf_TD.Theme = TM_ANSWER_BULLET_POS;

            Composer Message('*');
            Message.Add(G_Bullet.size());

            for(int i = 0; i < G_Bullet.size(); i++)
            {
                Composer bullet('#');
                bullet.Add(G_Bullet[i]->get_X());
                bullet.Add(G_Bullet[i]->get_Y());
                bullet.Add(G_Bullet[i]->get_Width());
                bullet.Add(G_Bullet[i]->get_Height());
                bullet.Add(G_Bullet[i]->get_Type());

                Message.Add(bullet.get_Composite());

            }

            buf_TD.Data = Message.get_Composite();

            v_Buf_TD.push_back(buf_TD);


            if(G_Enemy.size() == 0)
            {

                if(Now_Level + 1 < LevelInf.size())
                {
                    Now_Level++;
                    EnemyIsAlive = false;
                }
                else
                {
                    buf_TD.Theme = TM_ANSWER_WIN;
                    buf_TD.ID = -2;

                    v_Buf_TD.push_back(buf_TD);

                    Game_Stage = GS_Win;
                }
            }

            ////Dragon Information

            for(int i = 0; i < GameClient.size(); i++)
            {
                buf_TD.ID = GameClient[i]->clientNum;
                buf_TD.Theme = TM_ANSWER_DRAGON_INF;

                Composer Message('*');
                Message.Add(GameClient[i]->get_Life());
                Message.Add(GameClient[i]->get_Points());

                buf_TD.Data = Message.get_Composite();

                v_Buf_TD.push_back(buf_TD);
            }


            break;
        }
        case GS_Pause:
        {
            TClient_Message cl_msg = get_Client_Message();

            int client_id = 0;

            for(int i = 0; i < GameClient.size(); i++)
            {
                if(GameClient[i]->clientNum == cl_msg.ID)
                {
                    client_id = i;
                    break;
                }
            }

            switch(cl_msg.Theme)
            {

                case TM_KEY_PRESSED:
                {

                    int Key = cl_msg.Data.toInt();
                    switch(Key)
                    {
                        case GGK_Pause:
                        {
                            Game_Stage = GS_Start;

                            buf_TD.Theme = TM_ANSWER_PAUSE_OFF;
                            buf_TD.ID = -2;

                            v_Buf_TD.push_back(buf_TD);
                            break;
                        }
                    }

                    break;
                }

            }

            break;
        }
    }
    return v_Buf_TD;
}

void Lobby::set_Game_Stage(TGameStage New_Game_Stage)
{
    Game_Stage = New_Game_Stage;
}

void Lobby::Add_Client_Message(int ID, int Theme, QString Data)
{
    TClient_Message buf;
    buf.Theme = Theme;
    buf.Data = Data;
    buf.ID = ID;

    Client_Message.push(buf);
}

void Lobby::LoadAll()
{
    //GS_Timer_Start
    TS_Timer_Change_Lim = 100;
    TS_Timer_Counter = 0;
    TS_Counter = 4;
    //
    LevelInf = Read_Level(":/level.txt");
    Now_Level = 1;
    Max_Level = LevelInf.size();
}

vector<TLevelInf> Lobby::Read_Level(QString Dir)
{
    vector<TLevelInf> Buf;

    QFile file(Dir);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream input(&file);

    while(!input.atEnd())
    {
        int number;
        input >> number;

        TLevelInf lbuf;

        for(int i = 0; i < number; i++)
        {
            TBlockInf buf;

            input >> buf.Pos.X >> buf.Pos.Y;
            input >> buf.Type;
            input >> buf.Size.X >> buf.Size.Y;
            input >> buf.Rect.X >> buf.Rect.Y;
            input >> buf.Speed.X >> buf.Speed.Y;

            lbuf.Inf.push_back(buf);
        }

        Buf.push_back(lbuf);
    }

    file.close();

    return Buf;
}

void Lobby::Create_Enemy(TBlockInf BI, vector<QRectF> Target)
{
    int Start_X = BI.Pos.X;
    int Start_Y = BI.Pos.Y;
    int Width = BI.Rect.X / BI.Size.X;
    int Height = BI.Rect.Y / BI.Size.Y;
    int Speed_X = BI.Speed.X;
    int Speed_Y = BI.Speed.Y;


    for(int i = 0; i < BI.Size.X; i++)
    {
        for(int j = 0; j < BI.Size.Y; j++)
        {
            int X = Start_X + Width*i;
            int Y = Start_Y + Height*j;

//            MessageL("i = " + QString::number(i) + " X = " + QString::number(X) + " Y = " + QString::number(Y));
//            MessageL("Width = " + QString::number(Width) + " Height = " + QString::number(Height));

            Enemy *enm = new Enemy(BI.Type,
                                   X,
                                   Y,
                                   ENEMY_WIDTH, ENEMY_HEIGHT,
                                   QRectF(X, Y, Width, Height),
                                   Speed_X,
                                   Speed_Y,
                                   Target);

            G_Enemy.push_back(enm);
        }
    }
}

void Lobby::DeleteEnemy(vector<Enemy *> &v, int id)
{
    if(v.size() < id + 1)
        return;
    v.erase(v.begin() + id);
}

void Lobby::DeleteBullet(vector<Bullet *> &v, int id)
{
    if(v.size() < id + 1)
        return;
    v.erase(v.begin() + id);
}



TClient_Message Lobby::get_Client_Message()
{
    TClient_Message buf;
    buf.Theme = -1;
    buf.Data = "";

    if(Client_Message.empty())
        return buf;

    buf = Client_Message.front();
    Client_Message.pop();
}

bool Lobby::ifCollision(QRectF Rect1, QRectF Rect2)
{
    return (ifPointInRect(Rect1.x(), Rect1.y(), Rect2) ||
            ifPointInRect(Rect1.x() + Rect1.width(), Rect1.y(), Rect2) ||
            ifPointInRect(Rect1.x(), Rect1.y() + Rect1.height(), Rect2) ||
            ifPointInRect(Rect1.x() + Rect1.width(), Rect1.y() + Rect1.height(), Rect2));
}

bool Lobby::ifPointInRect(int X, int Y, QRectF Rect)
{
    return (X>=Rect.x() && X<=Rect.x() + Rect.width() && Y>=Rect.y() && Y<=Rect.y()+Rect.height());
}

void Lobby::Delete_Client(int clientNum)
{
    if(GameClient.size()>0)
    {
        for(int i=0; i<GameClient.size(); i++)
        {
            if(GameClient[i]->clientNum == clientNum)
            {
                for(int j=0; j<Client_Name.size(); j++)
                {
                    if(Client_Name[j] == GameClient[j]->Name);
                        Client_Name.erase(Client_Name.begin() + j);
                }
                if(Admin_ID == GameClient[i]->clientNum)
                    for(int j=0; j<GameClient.size(); j++)
                        if(i != j)
                        {
                            Admin_ID = j;
                            break;
                        }
                GameClient.erase(GameClient.begin() + i);
            }
        }
    }
}

//void Lobby::MessageL(QString Text)
//{
//    QMessageBox msg;
//    msg.setText(Text);
//    msg.exec();
//}

