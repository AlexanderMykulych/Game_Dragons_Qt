#ifndef GAME_CANVAS_H
#define GAME_CANVAS_H

#include <QtCore>
#include <QtGui>
#include "propertis.h"
#include <QMessageBox>
#include <QFont>
#include "bg_sky.h"
#include "dragon_obj.h"
#include "enemy_obj.h"
#include "explosion.h"
#include "bonus_obj.h"
#include "bullet_obj.h"
#include <vector>
#include "info_box.h"

using namespace std;

class TGame_Canvas
{
public:
    TGame_Canvas(int X, int Y, int Width, int Height);
    void Draw(QPainter &painter);
    void Process();
    void set_GamePoint(TGamePoint *New_GamePoint);

    //Load All
    void LoadAll();
    //GP_Timer_Start

    void set_TS_Count(int New_TS_Count) {TS_Count = New_TS_Count;}

    //Add Dragon
    void AddDragon(vector<DragonPos> &dragon_pos);

    //Enemy Pos
    void set_Enemy_Pos(vector<EnemyPos> &enemy_pos);

    //bullet Pos
    void set_Bullet_Pos(vector<BulletPos> &bullet_pos);

    //explos pos
    void Add_Explo_Pos(int Type, int X, int Y);

    //pause
    void set_Pause(bool Pause);


    //set inf
    void set_Inform(TDragonInf Inf);
    //debug
    void Message(QString Text = "1234");

    void Win();
private:
    //Options
    int X;
    int Y;
    int Width;
    int Height;
    QFont Font;

    TGamePoint *GamePoint;
    //GP_Timer_Start
    QPen TS_Pen;
    QRectF TS_Rect_Target;
    QFont TS_Font;
    QImage TS_startImg;
    int TS_Count;

    //GP_Game
    BG_Sky *G_Sky;
    vector<Dragon_Obj*> G_Dragon;
    vector<Enemy_Obj*> G_Enemy;
    vector<Bullet_Obj*> G_Bullet;
    vector<Explosion*> G_Explo;
    Info_Box *Inf_box;
    bool Pause;

    //GP_Win
    QImage *Win_Image;
};

#endif // GAME_CANVAS_H
