#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "game_object.h"
#include <QtGui>
#include <QtCore>

class Explosion
{
public:
    Explosion(int Type, int X, int Y, int Width, int Height);
    void Draw(QPainter &painter);
    bool Process();
    void set_X_Add(int Plus);
    void set_Y_Add(int Plus);

private:

    QImage *Image;
    int Image_Number;
    Game_Object *E_Object;

    int X;
    int Y;
    int Width;
    int Height;

    int Type;

    int Change_Frame_Interval;
    int Change_Frame_Count;

    //Load All
    void LoadAll();

};

#endif // EXPLOSION_H
