#ifndef CROSSZERO_H
#define CROSSZERO_H

#include <QtGui>
#include <QtCore>

enum CZType  {CZ_None, CZ_Zero, CZ_Cross};

class CrossZero
{
public:
    CrossZero(int X, int Y, int Width, int Height, CZType Type = CZ_None);

    void Draw(QPainter &painter);
    void setX(int X) {this->X = X;}
    void setY(int Y) {this->Y = Y;}
    void setWidth(int Width) {this->Width = Width;}
    void setHeight(int Height) {this->Height = Height;}
    void setType(CZType Type) {this->Type = Type;}

private:
    CZType Type;

    int X;
    int Y;
    int Width;
    int Height;

    QPen Pen;

};

#endif // CROSSZERO_H
