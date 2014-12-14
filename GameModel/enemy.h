#ifndef ENEMY_H
#define ENEMY_H

#include <QRectF>
#include "propertis.h"
#include <cmath>
#include <algorithm>
#include "bullet.h"
#include <vector>

using namespace std;

class Enemy
{
public:
    Enemy(int Type, int X, int Y, int Width, int Height, QRectF Rect_Fild, int Speed_X, int Speed_Y, vector<QRectF> Target);
    void Process();

    Bullet *do_Fire();


    int get_X() {return X;}
    int get_Y() {return Y;}
    int get_Width() {return Width;}
    int get_Height() {return Height;}
    int get_Type() {return Type;}
    QRectF get_Rect() {return QRectF(X, Y, Width, Height);}
    void set_Target(vector<QRectF> Target);

private:
    TPoint Speed;
    int Start_X;
    int Start_Y;
    int X;
    int Y;
    int Width;
    int Height;
    int Type;
    QRectF Rect_Fild;

    //type = sin
    int A2;

    //type = ACos
    int A3;
    int A3_Max;

    //type = CosB
    int A4;
    int A4_Max;
    int A4_Step;

    //type = Random side
    int Rand_Change_Time;
    int Rand_Change_Iter;

    //type = EMT_BOSS_1
    int Target_Id;
    int Target_Id_Change_Inter;
    int Target_Id_Change;


    //target
    vector<QRectF> R_Target;
    bool Fire;
    int Fire_Interv_Count;
    int Fire_Interv;
    bool isMakeChoise;


};

#endif // ENEMY_H
