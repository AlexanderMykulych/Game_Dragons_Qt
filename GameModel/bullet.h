#ifndef BULLET_H
#define BULLET_H

#include <QRectF>
#include "propertis.h"

class Bullet
{
public:
    Bullet(int X, int Y, int Width, int Height, int Speed_X, int Speed_Y, TBulletType Type, int player_id = 0);
    void Process();
    QRectF get_Rect() {return QRectF(X, Y, Width, Height);}
    int get_X() {return X;}
    int get_Y() {return Y;}
    int get_Width() {return Width;}
    int get_Height() {return Height;}
    int get_Speed_X() {return Speed_X;}
    int get_Speed_Y() {return Speed_Y;}
    int get_Type() {return Type;}
    int get_Player_Id() {return Player_Id;}
    void set_Player_Id(int Player_id);

private:
    int X;
    int Y;
    int Width;
    int Height;
    int Speed_X;
    int Speed_Y;
    int Player_Id;

    TBulletType Type;
};

#endif // BULLET_H
