#include "bullet.h"

Bullet::Bullet(int X, int Y, int Width, int Height, int Speed_X, int Speed_Y, TBulletType Type, int player_id)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Speed_X = Speed_X;
    this->Speed_Y = Speed_Y;
    this->Type = Type;
    this->Player_Id = player_id;
}

void Bullet::Process()
{
    X += Speed_X;
    Y += Speed_Y;
}

void Bullet::set_Player_Id(int Player_id)
{
    this->Player_Id = Player_id;
}
