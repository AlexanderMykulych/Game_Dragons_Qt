#include "enemy_obj.h"

Enemy_Obj::Enemy_Obj(int Type, int X, int Y, int Width, int Height)
{

    if(Type > 4)
        this->Type = 4;
    else
        this->Type = Type;

    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;

    Change_Frame_Interval = 17;
    Change_Frame_Count = 0;

    //Load All
    LoadAll();
}

void Enemy_Obj::Draw(QPainter &painter)
{
    E_Object->Draw(painter);
}

void Enemy_Obj::Process()
{
    Change_Frame_Count++;
    if(Change_Frame_Count >= Change_Frame_Interval)
    {
        Change_Frame_Count = 0;
        E_Object->Next_Image();
    }
}

void Enemy_Obj::set_X_Add(int Plus)
{
    E_Object->set_X_Up(Plus);
}

void Enemy_Obj::set_Y_Add(int Plus)
{

    E_Object->set_Y_Up(Plus);
}

void Enemy_Obj::set_X(int X)
{
    E_Object->set_X(X);
}

void Enemy_Obj::set_Y(int Y)
{
    E_Object->set_Y(Y);
}

void Enemy_Obj::set_Width(int Width)
{
    E_Object->set_Width(Width);
}

void Enemy_Obj::set_Height(int Height)
{
    E_Object->set_Height(Height);
}

void Enemy_Obj::set_Type(int Type)
{
    if(this->Type != Type)
    {
        this->Type = 4;
        if(Type > 4)
            this->Type = 4;
        E_Object->set_Image(Image[this->Type - 1]);
    }
}

void Enemy_Obj::LoadAll()
{
    for(int i = 0; i < 4; i++)
        Image[i] = new QImage(":/enemy_" + QString::number(i+1) + ".png");

    Image_Number = 3;

    E_Object = new Game_Object(Image[Type - 1], Image_Number, QRectF(this->X,
                                                           this->Y,
                                                           this->Width,
                                                           this->Height));
}
