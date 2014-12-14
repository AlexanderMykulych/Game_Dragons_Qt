#include "info_box.h"

Info_Box::Info_Box(int X, int Y, int Width, int Height, vector<QString> Inf)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Inf = Inf;

    int idFont = QFontDatabase::addApplicationFont(":/font_fire_1.ttf");
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    Font.setPointSize(25);
}

void Info_Box::Draw(QPainter &painter)
{
    int Block_Height = this->Height / Inf.size();

    QFont Old_Font = painter.font();
    QPen Old_Pen = painter.pen();

    QPen Pen(QColor::fromRgb(255, 0, 0, 255));

    painter.setFont(this->Font);
    painter.setPen(Pen);

    for(int i = 0; i < Inf.size(); i++)
    {
        int bl_Y = this->Y + Block_Height*i;

        painter.drawText(QRectF(this->X,
                                 bl_Y,
                                 this->Width,
                                 Block_Height),
                          Qt::AlignLeft,
                          this->Inf[i]);


    }
    painter.setFont(Old_Font);
    painter.setPen(Old_Pen);

   // painter.drawRect(QRectF(X, Y, Width, Height));
}

void Info_Box::set_Inf(vector<QString> inf)
{
    Inf = inf;
}
