#include "bullet_obj.h"

Bullet_Obj::Bullet_Obj(int X, int Y, int Width, int Height, qreal Rotate)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;

    this->Rotate = Rotate;

    Change_Frame_Interval = 10;
    Change_Frame_Count = 0;

    //Load All
    LoadAll();
}

void Bullet_Obj::Draw(QPainter &painter)
{
    B_Object->Draw(painter);
}

void Bullet_Obj::Process()
{
    Change_Frame_Count++;
    if(Change_Frame_Count >= Change_Frame_Interval)
    {
        Change_Frame_Count = 0;
        if(B_Object->get_ImageId() >= Image_Number - 1)
        {
            if(Now_Image + 1 > 2)
                Now_Image = 0;
            else
                Now_Image++;
            B_Object->set_Image(Image[Now_Image]);
        }
        B_Object->Next_Image();
    }
}

void Bullet_Obj::set_X(int X)
{
    B_Object->set_X(X);
}

void Bullet_Obj::set_Y(int Y)
{
    B_Object->set_Y(Y);
}

void Bullet_Obj::set_Width(int Width)
{
    B_Object->set_Width(Width);
}

void Bullet_Obj::set_Height(int Height)
{
    B_Object->set_Height(Height);
}

void Bullet_Obj::set_X_Add(int Plus)
{
    B_Object->set_X_Up(Plus);
}

void Bullet_Obj::set_Y_Add(int Plus)
{
    B_Object->set_Y_Up(Plus);
}

void Bullet_Obj::set_Rotate(qreal Rotate)
{
    this->Rotate = Rotate;
}

void Bullet_Obj::LoadAll()
{
    for(int i = 0; i < 3; i++)
    {
        Image[i] = new QImage(":/Bullet_" + QString::number(i+1) + ".png");
    }
    Image_Number = 3;
    Now_Image = 0;

    B_Object = new Game_Object(Image[Now_Image], Image_Number, QRectF(this->X,
                                                              this->Y,
                                                              this->Width,
                                                              this->Height), Rotate);
}
