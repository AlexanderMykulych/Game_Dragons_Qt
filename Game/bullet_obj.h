#ifndef BULLET_OBJ_H
#define BULLET_OBJ_H

#include <QtCore>
#include <QtGui>
#include "game_object.h"

class Bullet_Obj
{
public:
    Bullet_Obj(int X, int Y, int Width, int Height,qreal Rotate = -90);
    void Draw(QPainter &painter);
    void Process();
    void set_X(int X);
    void set_Y(int Y);
    void set_Width(int Width);
    void set_Height(int Height);
    void set_X_Add(int Plus);
    void set_Y_Add(int Plus);
    void set_Rotate(qreal Rotate);

private:

    QImage *Image[3];
    int Image_Number;
    int Now_Image;
    Game_Object *B_Object;

    int X;
    int Y;
    int Width;
    int Height;
    qreal Rotate;


    int Change_Frame_Interval;
    int Change_Frame_Count;

    void LoadAll();
};

#endif // BULLET_OBJ_H
