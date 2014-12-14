#include "bg_sky.h"

BG_Sky::BG_Sky(int X, int Y, int Width, int Height)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;

    Message(QString::number(this->X) + " " + QString::number(this->Y) + " " + QString::number(this->Width) + " " + QString::number(this->Height));

    LoadAll();
}

void BG_Sky::Draw(QPainter &painter)
{
//Sky
    QBrush Old_Brush = painter.brush();
    QBrush Brush_Sky(QColor::fromRgb(100, 149, 237));

    QPen Old_Pen = painter.pen();
    QPen Pen_Sky(Brush_Sky.color());

    painter.setBrush(Brush_Sky);
    painter.setPen(Pen_Sky);

    painter.drawRect(QRect(this->X, this->Y, this->Width, this->Height));

    painter.setBrush(Old_Brush);
    painter.setPen(Old_Pen);

//cloud
    for(int i = 0; i < Cloud.size(); i++)
    {
        Cloud[i]->Draw(painter);
    }
}

void BG_Sky::Process()
{
    Move_Counter++;
    if(Move_Counter>=Move_Interval)
    {
        Move_Counter = 0;
        for(int i = 0; i < Cloud.size(); i+=2)
        {
            Cloud[i]->set_Y_Up(2);
            if(Cloud[i]->get_Y() > this->Height)
            {
                int new_cloud_x = rand() % this->Width;
                int new_cloud_y = rand() % this->Height - this->Height - 50;
                Cloud[i]->set_X(new_cloud_x);
                Cloud[i]->set_Y(new_cloud_y);
            }
        }
        for(int i = 1; i < Cloud.size(); i+=2)
        {
            Cloud[i]->set_Y_Up(1);
            if(Cloud[i]->get_Y() > this->Height)
            {
                int new_cloud_x = rand() % this->Width;
                int new_cloud_y = rand() % this->Height - this->Height - 50;
                Cloud[i]->set_X(new_cloud_x);
                Cloud[i]->set_Y(new_cloud_y);
            }
        }
    }
}

void BG_Sky::LoadAll()
{
    for(int i=0; i < 3; i++)
    {
        img_Cloud[i] = new QImage();
        img_Cloud[i]->load(":/cloud_" + QString::number(i+1)+".png");
    }


    int Cloud_Number = rand() % 3 + 1;
    for(int i = 0; i < Cloud_Number; i++)
    {
        int cloud_id = rand() % 3;
        int cloud_x = rand() % this->Width;
        int cloud_y = rand() % (this->Height) - this->Height;
        int cloud_width = rand() % 570 + 90;
        int cloud_height = cloud_width/(rand() % 4 + 2);
        QRectF cloud_rect = QRectF(cloud_x, cloud_y, cloud_width, cloud_height);

        Game_Object *cloud = new Game_Object(img_Cloud[cloud_id], 1, cloud_rect);
        Cloud.push_back(cloud);
    }
    Move_Interval = 1;
    Move_Counter = 0;
}

void BG_Sky::Message(QString Text)
{
    QFile file("E:\\out.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << Text << '\n';
    file.close();
}
