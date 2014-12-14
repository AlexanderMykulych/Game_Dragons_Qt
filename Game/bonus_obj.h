#ifndef BONUS_OBJ_H
#define BONUS_OBJ_H

#include <QtCore>
#include <QtGui>
#include "game_object.h"

class Bonus_Obj
{
public:
    Bonus_Obj(int Type, int X, int Y, int Width, int Height);
    void Draw(QPainter &painter);
    void set_X_Add(int Plus);
    void set_Y_Add(int Plus);

private:

    QImage *Image;

    Game_Object *B_Object;

    int X;
    int Y;
    int Width;
    int Height;

    int Type;

    //Load All
    void LoadAll();

};

#endif // BONUS_OBJ_H
