#include "bonus_obj.h"

Bonus_Obj::Bonus_Obj(int Type, int X, int Y, int Width, int Height)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;

    this->Type = Type;

    LoadAll();
}

void Bonus_Obj::Draw(QPainter &painter)
{
    B_Object->Draw(painter);
}

void Bonus_Obj::set_X_Add(int Plus)
{
    B_Object->set_X_Up(Plus);
}

void Bonus_Obj::set_Y_Add(int Plus)
{
    B_Object->set_Y_Up(Plus);
}


void Bonus_Obj::LoadAll()
{
    Image = new QImage(":/Bonus_" + QString::number(Type) + ".png");

    B_Object = new Game_Object(Image, 1, QRectF(this->X,
                                                this->Y,
                                                this->Width,
                                                this->Height));
}
