#include "enemy.h"

Enemy::Enemy(int Type, int X, int Y, int Width, int Height, QRectF Rect_Fild, int Speed_X, int Speed_Y, vector<QRectF> Target)
{
    this->Start_X = X;
    this->Start_Y = Y;
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Type = Type;
    this->Rect_Fild = Rect_Fild;
    this->Speed.X = Speed_X;
    this->Speed.Y = Speed_Y;

    this->R_Target = Target;

    this->Fire_Interv = rand() % 200 + 300;
    this->Fire_Interv_Count = this->Fire_Interv;

    //type = 2
    A2 = Rect_Fild.height()/2;

    //type = 3
    A3 = 0;
    A3_Max = Rect_Fild.height()/2;

    //type = 2
    A4 = Rect_Fild.width()/2 - Width;
    //type = random side
    Rand_Change_Time = 4;
    Rand_Change_Iter = 0;

    //type = boss_1
    Target_Id_Change = 0;
    Target_Id_Change_Inter = 10000;
    Target_Id = 0;

    //
}

void Enemy::Process()
{
    this->Fire_Interv_Count++;

    switch(Type)
    {
        case EMT_Down:
        {
            Y += Speed.Y;
            break;
        }

        case EMT_Aside:
        {
            X += Speed.X;
            break;
        }

        case EMT_Down_And_Aside:
        {
            X += Speed.X;
            Y += Speed.Y;
            break;
        }

        case EMT_Sin:
        {
            X += Speed.X;
            Y = Start_Y + A2 - A2*sin(double(X)/double(A2));
            break;
        }

        case EMT_ACos:
        {
            X += Speed.X;

            A3 = X;
            if(A3>A3_Max)
                A3 = A3_Max;

            Y = Start_Y + A3_Max - A3*sin(double(X)/A3_Max);

            break;
        }

        case EMT_CosB:
        {
            Y += Speed.Y;
            X = Start_X + A4 - A4*sin(8*double(Y)/double(A4));
            break;
        }

        case EMT_M_Sin:
        {
            X += Speed.X;
            Y = Start_Y + A2 + A2*sin(double(X)/double(A2));
            break;
        }

        case EMT_M_ACos:
        {
            X += Speed.X;

            A3 = X;
            if(A3>A3_Max)
                A3 = A3_Max;

            Y = Start_Y + A3_Max + A3*sin(double(X)/A3_Max);
            break;
        }

        case EMT_M_CosB:
        {
            Y += Speed.Y;
            X = Start_X + A4 + A4*sin(8*double(Y)/double(A4));
            break;
        }

        case EMT_BOSS_1:
        {
            Target_Id_Change++;
            if(Target_Id_Change % Target_Id_Change_Inter == 0)
            {
                Target_Id = rand() % R_Target.size();
            }

            if(R_Target[Target_Id].x() < X)
                X -= Speed.X;
            else
                if(R_Target[Target_Id].x() > X)
                    X += Speed.X;


            break;
        }

        case EMT_BOSS_2:
        {
            Target_Id_Change++;
            if(Target_Id_Change % Target_Id_Change_Inter == 0)
            {
                Target_Id = rand() % R_Target.size();
            }

            if(R_Target[Target_Id].x() < X)
                X -= Speed.X;
            else
                if(R_Target[Target_Id].x() > X)
                    X += Speed.X;
            else
                    Fire = true;

            break;
        }

        case EMT_BOSS_3:
        {
            Target_Id_Change++;
            if(Target_Id_Change % Target_Id_Change_Inter == 0)
            {
                Target_Id = rand() % R_Target.size();
            }

            if(R_Target[Target_Id].x() <= X && R_Target[Target_Id].x() + R_Target[Target_Id].width() <= X)
                X += Speed.X;
            else
                if(R_Target[Target_Id].x() >= X)
                    X -= Speed.X;
                else
                    X = X + (rand() % 3 - 1)*Speed.X;

            Fire = true;

            break;
        }

    }
    if(X <= Rect_Fild.x() || X + Width >= Rect_Fild.x() + Rect_Fild.width())
        Speed.X = -Speed.X;

    if(Y <= Rect_Fild.y() || Y + Height >= Rect_Fild.y() + Rect_Fild.height())
        Speed.Y = -Speed.Y;

}

Bullet *Enemy::do_Fire()
{
    if((Fire_Interv_Count >= Fire_Interv) || (Fire_Interv_Count >= Fire_Interv/2 && Fire))
    {
        if(rand()%100%2)
        {
            Fire = false;
            Fire_Interv_Count = 0;
            int Width = this->Width / 4;
            int Height = this->Height / 3;
            int X = this->X + this->Width / 2 - Width / 2;
            int Y = this->Y + this->Height;
            int Speed_X = 0;
            int Speed_Y = 3;

            Bullet *bullet = new Bullet(X, Y, Width, Height, Speed_X, Speed_Y, BT_Enemy);
            return bullet;
        }
    }
    return NULL;
}

void Enemy::set_Target(vector<QRectF> Target)
{
    this->R_Target = Target;
}
