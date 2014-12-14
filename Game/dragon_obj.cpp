#include "dragon_obj.h"

Dragon_Obj::Dragon_Obj(int Type, QString Name, int X, int Y, int Width, int Height, int Side)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Name = Name;
    this->Side = Side;

    this->Type = Type;

    this->Change_Frame_Interval = 9;
    this->Change_Frame_Count = 0;

    //Load All
    LoadAll();
}

void Dragon_Obj::Draw(QPainter &painter)
{
    D_Object->Draw(painter);
    QRectF Rect = QRectF(this->X, this->Y + this->Height, this->Width, 50);
    painter.drawText(Rect, Qt::AlignCenter, Name);
}

void Dragon_Obj::Process()
{
    Change_Frame_Count++;
    if(Change_Frame_Count >= Change_Frame_Interval)
    {
        Change_Frame_Count = 0;
        D_Object->Next_Image();
    }
}

void Dragon_Obj::set_Dragon_Move(TDragon_Move New_DM)
{
    if(New_DM == Dragon_Stage)
        return;

    Dragon_Stage = New_DM;

    switch(Dragon_Stage)
    {
        case DM_Up:
        {
            Image = img_Up;
            break;
        }
        case DM_Left:
        {
            Image = img_L;
            break;
        }
        case DM_Right:
        {
            Image = img_R;
            break;
        }
    }
}

void Dragon_Obj::set_X_Add(int Plus)
{
    D_Object->set_X_Up(Plus);
}

void Dragon_Obj::set_Y_Add(int Plus)
{
    D_Object->set_Y_Up(Plus);
}

void Dragon_Obj::set_X(int X)
{
    D_Object->set_X(X);
}

void Dragon_Obj::set_Y(int Y)
{
    D_Object->set_Y(Y);
}

void Dragon_Obj::set_Width(int Width)
{
    D_Object->set_Width(Width);
}

void Dragon_Obj::set_Height(int Height)
{
    D_Object->set_Height(Height);
}

void Dragon_Obj::set_Type(int Type, int Side)
{
    if(this->Type != Type)
    {
        this->Type = Type;
        if(Type == 1)
        {
            img_Up->load(":/dragon_up.png");
            img_L->load(":/dragonup_left.png");
            img_R->load(":/dragon_up_right.png");
            Image_Number = 10;
        }
        else
        {
            img_Up->load(":/dragon_up_2.png");
            img_L->load(":/dragonup_left_2.png");
            img_R->load(":/dragon_up_right_2.png");
            Image_Number = 4;
        }
    }
    if(this->Side != Side)
    {
        this->Side = Side;
        switch(Side)
        {
            case SM_Left:
            {
                D_Object->set_Image(img_L);
                break;
            }
            case SM_Up:
            {
                D_Object->set_Image(img_Up);
                break;
            }
            case SM_Right:
            {
                D_Object->set_Image(img_R);
                break;
            }
            case SM_Down:
            {
                D_Object->set_Image(img_Up);
                break;
            }
        }
    }
}

void Dragon_Obj::LoadAll()
{
    Dragon_Stage = DM_Up;

    if(Type == 1)
    {
        img_Up = new QImage(":/dragon_up.png");
        img_L = new QImage(":/dragonup_left.png");
        img_R = new QImage(":/dragon_up_right.png");
        Image_Number = 10;
    }
    else
    {
        img_Up = new QImage(":/dragon_up_2.png");
        img_L = new QImage(":/dragonup_left_2.png");
        img_R = new QImage(":/dragon_up_right_2.png");
        Image_Number = 4;
    }


    D_Object = new Game_Object(img_Up,
                               Image_Number,
                               QRectF(this->X, this->Y, this->Width, this->Height));

    switch(Side)
    {
        case SM_Left:
        {
            D_Object->set_Image(img_L);
            break;
        }
        case SM_Up:
        {
            D_Object->set_Image(img_Up);
            break;
        }
        case SM_Right:
        {
            D_Object->set_Image(img_R);
            break;
        }
        case SM_Down:
        {
            D_Object->set_Image(img_Up);
            break;
        }
    }
}
