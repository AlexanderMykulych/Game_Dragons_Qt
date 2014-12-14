#ifndef LOBBY_H
#define LOBBY_H

#include <QString>
#include "propertis.h"
#include "client.h"
#include <vector>
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "composer.h"
#include <enemy.h>
#include <queue>
#include "bullet.h"


using namespace std;


class Lobby
{
public:
    Lobby();
    QString Name;

    int Bot_Number;

    TPlayerType Player_Type_1;
    TPlayerType Player_Type_2;
    TPlayerType Player_Type_3;
    int Player_Number;
    QStringList Client_Name;
    vector<Client*> GameClient;

    void Add_Client(Client *New_Client);
    void set_Admin_ID(int New_Admin_ID) {Admin_ID = New_Admin_ID;}
    inline int get_Admin_ID() {return Admin_ID;}
    void Delete_Client(int clientNum);


    //work with game
    vector<TTheme_Data> Process();
    void set_Game_Stage(TGameStage New_Game_Stage);
    //
    void Add_Client_Message(int ID, int Theme, QString Data);
private:
    void MessageL(QString Text);

    void LoadAll();

    TGameStage Game_Stage;
    int Admin_ID;
    //GS_TIME_START
    int TS_Counter;
    int TS_Timer_Counter;
    int TS_Timer_Change_Lim;

    //Read level inform
    vector<TLevelInf> Read_Level(QString Dir);
    vector<TLevelInf> LevelInf;
    int Now_Level;
    int Max_Level;
    //Enemy
    vector<Enemy*> G_Enemy;
    void Create_Enemy(TBlockInf BI, vector<QRectF> Target);


    //
    bool EnemyIsAlive;

    //Bullet
    vector<Bullet*> G_Bullet;


    //delete from vector
    void DeleteEnemy(vector<Enemy*> &v, int id);
    void DeleteBullet(vector<Bullet *> &v, int id);

//Queue
    queue<TClient_Message> Client_Message;
    TClient_Message get_Client_Message();


    bool ifCollision(QRectF Rect1, QRectF Rect2);
    bool ifPointInRect(int X, int Y, QRectF Rect);

};

#endif // LOBBY_H
