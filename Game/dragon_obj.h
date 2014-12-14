#ifndef DRAGON_OBJ_H
#define DRAGON_OBJ_H

#include "game_object.h"
#include "propertis.h"
#include <QtGui>
#include <QtCore>

class Dragon_Obj
{
public:
    Dragon_Obj(int Type, QString Name, int X, int Y, int Width, int Height, int Side);
    void Draw(QPainter &painter);
    void Process();
    void set_Dragon_Move(TDragon_Move New_DM);
    void set_X_Add(int Plus);
    void set_Y_Add(int Plus);
    void set_X(int X);
    void set_Y(int Y);
    void set_Width(int Width);
    void set_Height(int Height);
    void set_Type(int Type, int Side);
    void set_Name(QString Name){this->Name = Name;}
private:

    TDragon_Move Dragon_Stage;

    QImage *img_Up;
    QImage *img_R;
    QImage *img_L;
    QImage *Image;
    int Image_Number;

    Game_Object *D_Object;
    QString Name;
    int X;
    int Y;
    int Width;
    int Height;
    int Type;
    int Side;

    int Change_Frame_Interval;
    int Change_Frame_Count;

    void LoadAll();



};

#endif // DRAGON_OBJ_H
