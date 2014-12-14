#include "game_canvas.h"

TGame_Canvas::TGame_Canvas(int X, int Y, int Width, int Height)
{
    //GP_Timer_Start
    TS_Count = 0;
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Pause = false;
    //Load All
    LoadAll();
}

void TGame_Canvas::Draw(QPainter &painter)
{
    switch(*GamePoint)
    {
        case GP_Timer_Start:
        {

            painter.drawImage(TS_Rect_Target, TS_startImg);

            QFont Old_Font = painter.font();
            QPen Old_Pen = painter.pen();

            painter.setFont(TS_Font);
            painter.setPen(TS_Pen);

            painter.drawText(TS_Rect_Target, QString::number(TS_Count), QTextOption(Qt::AlignCenter));

            painter.setFont(Old_Font);
            painter.setPen(Old_Pen);
            break;
        }
        case GP_Game:
        {
            G_Sky->Draw(painter);

            for(int i = 0; i < G_Dragon.size(); i++)
            {
                G_Dragon[i]->Draw(painter);
            }

            for(int i = 0; i < G_Enemy.size(); i++)
            {
                G_Enemy[i]->Draw(painter);
            }

            for(int i = 0; i < G_Bullet.size(); i++)
            {
                G_Bullet[i]->Draw(painter);
            }

            for(int i = 0; i < G_Explo.size(); i++)
            {
                G_Explo[i]->Draw(painter);
            }

            Inf_box->Draw(painter);

            if(Pause)
            {
                QBrush Brush(QColor::fromRgb(100, 100, 100, 100));
                QPen Pen(Brush,0);


                painter.setBrush(Brush);
                painter.setPen(Pen);
                painter.setFont(this->Font);

                painter.drawRect(this->X, this->Y, this->Width, this->Height);


                painter.drawText(QRectF(this->X, this->Y, this->Width, this->Height),
                                 Qt::AlignCenter,
                                 "PAUSE");

            }

            break;
        }
        case GP_Win:
        {
            QPen Pen(QColor::fromRgb(255, 140, 0, 255));

            painter.drawImage(QRectF(this->X, this->Y, this->Width, this->Height), *Win_Image);


            painter.setFont(this->Font);
            painter.setPen(Pen);

            painter.drawText(QRectF(this->X, this->Y, this->Width, this->Height),
                             Qt::AlignCenter,
                             "You Win!!!");

            break;
        }

    }
}

void TGame_Canvas::Process()
{
    switch(*GamePoint)
    {
        case GP_Game:
        {
            G_Sky->Process();

            for(int i = 0; i < G_Dragon.size(); i++)
            {
                G_Dragon[i]->Process();
            }

            for(int i = 0; i < G_Enemy.size(); i++)
            {
                G_Enemy[i]->Process();
            }

            for(int i = 0; i < G_Bullet.size(); i++)
            {
                G_Bullet[i]->Process();
            }

            for(int i = 0; i < G_Explo.size(); i++)
            {
                if(G_Explo[i]->Process())
                {
                    G_Explo.erase(G_Explo.begin() + i);
                }
            }
            break;
        }
    }
}

void TGame_Canvas::set_GamePoint(TGamePoint *New_GamePoint)
{
    GamePoint = New_GamePoint;
}

void TGame_Canvas::LoadAll()
{
    int idFont = QFontDatabase::addApplicationFont(":/font_fire_1.ttf");
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    Font.setPointSize(100);

//Time Start
    {
        int img_id = rand() % 5 + 1;
        TS_startImg.load(":/start_"+QString::number(img_id)+".jpg");
    }
    {
        int idFont = QFontDatabase::addApplicationFont(":/font_fire_1.ttf");
        TS_Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
        TS_Font.setPointSize(150);
    }
    TS_Rect_Target = QRectF(this->X, this->Y, this->Width, this->Height);
    TS_Pen.setColor(QColor::fromRgb(190, 190, 190));

//Game
    G_Sky = new BG_Sky(this->X, this->Y, this->Width, this->Height);

    vector<QString> inf;
    inf.push_back("Life:");
    inf.push_back("Points:");

    int Height = 70;

    Inf_box = new Info_Box(10, this->Height - Height, 200, Height, inf);

//Win
    Win_Image = new QImage(":/win.jpg");
}

void TGame_Canvas::AddDragon(vector<DragonPos> &dragon_pos)
{    
    for(int i = 0; i < dragon_pos.size(); i++)
    {
        //Message(QString::number(G_Dragon.size()));
        if(G_Dragon.size() >= i + 1)
        {
            G_Dragon[i]->set_Name(dragon_pos[i].Name);
            G_Dragon[i]->set_X(dragon_pos[i].X);
            G_Dragon[i]->set_Y(dragon_pos[i].Y);
            G_Dragon[i]->set_Width(dragon_pos[i].Width);
            G_Dragon[i]->set_Height(dragon_pos[i].Height);
            G_Dragon[i]->set_Type(dragon_pos[i].Type, dragon_pos[i].Side);
        }
        else
        {
            //Message();
            Dragon_Obj *dragon = new Dragon_Obj(dragon_pos[i].Type, dragon_pos[i].Name,
                                             dragon_pos[i].X, dragon_pos[i].Y,
                                             dragon_pos[i].Width, dragon_pos[i].Height, dragon_pos[i].Side);
            G_Dragon.push_back(dragon);
        }
    }
    for(int i = 0; i < int(G_Dragon.size() - dragon_pos.size())>0; i++)
        G_Dragon.pop_back();
}

void TGame_Canvas::set_Enemy_Pos(vector<EnemyPos> &enemy_pos)
{
    for(int i = 0; i < enemy_pos.size(); i++)
    {
        if(G_Enemy.size() >= i + 1)
        {
            G_Enemy[i]->set_X(enemy_pos[i].X);
            G_Enemy[i]->set_Y(enemy_pos[i].Y);
            G_Enemy[i]->set_Width(enemy_pos[i].Width);
            G_Enemy[i]->set_Height(enemy_pos[i].Height);
            G_Enemy[i]->set_Type(enemy_pos[i].Type);
        }
        else
        {
            Enemy_Obj *enemy = new Enemy_Obj(enemy_pos[i].Type,
                                             enemy_pos[i].X, enemy_pos[i].Y,
                                             enemy_pos[i].Width, enemy_pos[i].Height);
            G_Enemy.push_back(enemy);
        }
    }

    for(int i = 0; i < int(G_Enemy.size() - enemy_pos.size())>0; i++)
        G_Enemy.pop_back();
}

void TGame_Canvas::set_Bullet_Pos(vector<BulletPos> &bullet_pos)
{
    //Message("bullet_pos = " + QString::number(bullet_pos.size()));
    for(int i = 0; i < bullet_pos.size(); i++)
    {
        if(G_Bullet.size() >= i + 1)
        {
            G_Bullet[i]->set_X(bullet_pos[i].X);
            G_Bullet[i]->set_Y(bullet_pos[i].Y);
            G_Bullet[i]->set_Width(bullet_pos[i].Width);
            G_Bullet[i]->set_Height(bullet_pos[i].Height);

            qreal rotate;
            if(bullet_pos[i].Type)
            {
                rotate = 90;
            }
            else
            {
                rotate = -90;
            }

            G_Bullet[i]->set_Rotate(rotate);
        }
        else
        {
            qreal rotate;
            if(bullet_pos[i].Type)
            {
                rotate = 90;
            }
            else
            {
                rotate = -90;
            }

            Bullet_Obj *enemy = new Bullet_Obj(bullet_pos[i].X, bullet_pos[i].Y,
                                             bullet_pos[i].Width, bullet_pos[i].Height, rotate);
            G_Bullet.push_back(enemy);
        }
    }
    for(int i = 0; i < int(G_Bullet.size() - bullet_pos.size())>0; i++)
        G_Bullet.pop_back();
}

void TGame_Canvas::Add_Explo_Pos(int Type, int X, int Y)
{
    Explosion *buf = new Explosion(Type, X, Y, 100, 100);
    G_Explo.push_back(buf);
}

void TGame_Canvas::set_Pause(bool Pause)
{
    this->Pause = Pause;
}

void TGame_Canvas::set_Inform(TDragonInf Inf)
{
    vector<QString> inf;
    inf.push_back("Life: " + QString::number(Inf.Life));
    inf.push_back("Points: " + QString::number(Inf.Points));

    Inf_box->set_Inf(inf);
}


void TGame_Canvas::Message(QString Text)
{
//    QMessageBox msg;
//    msg.setText(Text);
//    msg.exec();
    QFile file("E:\\out2.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << Text << '\n';
    file.close();
}

void TGame_Canvas::Win()
{
    *GamePoint = GP_Win;
}
