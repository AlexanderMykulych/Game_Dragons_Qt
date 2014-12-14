#include "client.h"

Client::Client(int clientNum, QObject *parent) :
    QObject(parent)
{
    this->clientNum = clientNum;
    this->Name = "";
    Enable = true;
    Lobby_ID = -1;
    Side = SM_Up;

    Speed_Up = 20;

    Fild = QRectF(0, 0, CLIENT_SCREEN_WIDTH, CLIENT_SCREEN_HEIGHT);

    Fire_Interv = 20;
    Fire_Interv_Count = Fire_Interv;

    Life = DRAGON_LIFE;
    Points = 0;

    Move_Count_Inter = 2;
    Move_Count = Move_Count_Inter;

}

void Client::Delete()
{
    Enable = false;
}

void Client::Process()
{
    //Fire
    Fire_Interv_Count++;
    Move_Count++;
}

void Client::set_X(int X)
{
    this->X = X;
}

void Client::set_Y(int Y)
{
    this->Y = Y;
}

void Client::set_Width(int Width)
{
    this->Width = Width;
}

void Client::set_Height(int Height)
{
    this->Height = Height;
}

void Client::set_SpeedUp(int SpeedUp)
{
    this->Speed_Up = SpeedUp;
}

void Client::set_Up()
{
    if(Move_Count >= Move_Count_Inter)
    {
        Move_Count = 0;
        if(Y - Speed_Up >= Fild.y() && Y + Height - Speed_Up <= Fild.y() + Fild.height())
        {
            Y -= Speed_Up;
        }
        Side = SM_Up;
    }
}

void Client::set_Down()
{
    if(Move_Count >= Move_Count_Inter)
    {
        Move_Count = 0;
        if(Y + Speed_Up >= Fild.y() && Y + Height + Speed_Up <= Fild.y() + Fild.height())
        {
            Y += Speed_Up;
        }
        Side = SM_Down;
    }
}

void Client::set_Left()
{
    if(Move_Count >= Move_Count_Inter)
    {
        Move_Count = 0;
        if(X - Speed_Up >= Fild.x() && X + Width - Speed_Up <= Fild.x() + Fild.width())
        {
            X -= Speed_Up;
        }
        Side = SM_Left;
    }
}

void Client::set_Right()
{
    if(Move_Count >= Move_Count_Inter)
    {
        Move_Count = 0;
        if(X + Speed_Up >= Fild.x() && X + Width + Speed_Up <= Fild.x() + Fild.width())
        {
            X += Speed_Up;
        }
        Side = SM_Right;
    }
}

void Client::set_Side(int Side)
{
    this->Side = Side;
}

Bullet *Client::Fire()
{
    if(Fire_Interv_Count >= Fire_Interv)
    {
        Fire_Interv_Count = 0;
        int Width = this->Width / 4;
        int Height = this->Height / 3;
        int X = this->X + this->Width / 2 - Width / 2;
        int Y = this->Y;
        int Speed_X = 0;
        int Speed_Y = -5;

        Bullet *bullet = new Bullet(X, Y, Width, Height, Speed_X, Speed_Y, BT_Dragon);
        return bullet;
    }
    return NULL;
}

void Client::BulletIsHit()
{
    if(Life > 0)
        Life--;
}

void Client::EnemyIsDead()
{
    Points++;
}


