#include "explosion.h"

Explosion::Explosion(int Type, int X, int Y, int Width, int Height)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Type = Type;
    if(Type > 4)
        this->Type = 4;

    Change_Frame_Interval = 5;
    Change_Frame_Count = 0;

    //Load All
    LoadAll();
}

void Explosion::Draw(QPainter &painter)
{
    E_Object->Draw(painter);
}

bool Explosion::Process()
{
    bool flag = false;
    Change_Frame_Count++;
    if(Change_Frame_Count >= Change_Frame_Interval)
    {
        if(E_Object->get_ImageId() >= Image_Number - 1)
            flag = true;
        Change_Frame_Count = 0;
        E_Object->Next_Image();
    }
    return flag;
}

void Explosion::set_X_Add(int Plus)
{
    E_Object->set_X_Up(Plus);
}

void Explosion::set_Y_Add(int Plus)
{
    E_Object->set_Y_Up(Plus);
}

void Explosion::LoadAll()
{
    if(!Type)
    {
        Image = new QImage(":/Explosion.png");
    }
    else
    {
        Image = new QImage(":/appear_" + QString::number(Type) + ".png");
    }

    Image_Number = 20;

    E_Object = new Game_Object(Image, Image_Number, QRectF(this->X,
                                                           this->Y,
                                                           this->Width,
                                                           this->Height));
}
