#include "crosszero.h"

CrossZero::CrossZero(int X, int Y, int Width, int Height, CZType Type)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Height = Height;
    this->Type = Type;
    Pen.setColor(QColor::fromRgb(255, 0, 0, 255));
    Pen.setWidth(10);
}

void CrossZero::Draw(QPainter &painter)
{
    switch(Type)
    {
        case CZ_None:
        {

            break;
        }
        case CZ_Cross:
        {
            int X11 = this->X;
            int X12 = this->X + this->Width;
            int Y11= this->Y;
            int Y12=this->Height+this->Y;

            int X21 = this->X;
            int X22 = this->X + this->Width;
            int Y21= this->Y + this->Height;
            int Y22=this->Y;

            painter.setPen(Pen);

            painter.drawLine(QPointF(X11, Y11), QPointF(X12, Y12));
            painter.drawLine(QPointF(X21, Y21), QPointF(X22, Y22));
            break;
        }
        case CZ_Zero:
        {

            painter.setPen(Pen);
            painter.drawEllipse(QRectF(this->X, this->Y, this->Width, this->Height));
            break;
        }
    }
}
