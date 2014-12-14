#include "gamefild.h"

GameFild::GameFild(int Count, int Width, int X, int Y)
{
    this->Count = Count;
    this->Rect_Width = Width;
    this->X = X;
    this->Y = Y;

    Brush.setColor(QColor::fromRgb(255,255,255,255));
    Brush.setStyle(Qt::SolidPattern);
    Pen.setColor(QColor::fromRgb(0,0,0,255));
    Pen.setWidth(5);
}

void GameFild::Draw(QPainter &painter)
{
    painter.setBrush(Brush);
    painter.setPen(QPen(Brush, 1));

    painter.drawRect(QRectF(X, Y, Count*Rect_Width, Count*Rect_Width));

    painter.setPen(Pen);

    int Y1 = this->Y;
    int Y2 = this->Y + Count*Rect_Width;

    for(int i=1; i < Count; i++)
    {
        int X1 = this->X + Rect_Width*i;

        painter.drawLine(QPointF(X1, Y1),  QPointF(X1, Y2));
    }

     int X1 = this->X;
     int X2 = this->X + Count*Rect_Width;
    for(int i=1; i < Count; i++)
    {

        int Y1 = this->Y + Rect_Width*i;

        painter.drawLine(QPointF(X1, Y1),  QPointF(X2, Y1));
    }

}
