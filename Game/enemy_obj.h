#ifndef ENEMY_OBJ_H
#define ENEMY_OBJ_H

#include "game_object.h"
#include <QtGui>
#include <QtCore>

class Enemy_Obj
{
public:
    Enemy_Obj(int Type, int X, int Y, int Width, int Height);
    void Draw(QPainter &painter);
    void Process();
    void set_X_Add(int Plus);
    void set_Y_Add(int Plus);
    void set_X(int X);
    void set_Y(int Y);
    void set_Width(int Width);
    void set_Height(int Height);
    void set_Type(int Type);

private:

    void LoadAll();

    QImage *Image[4];
    int Image_Number;
    Game_Object *E_Object;

    int X;
    int Y;
    int Width;
    int Height;

    int Type;

    int Change_Frame_Interval;
    int Change_Frame_Count;
};

#endif // ENEMY_OBJ_H
