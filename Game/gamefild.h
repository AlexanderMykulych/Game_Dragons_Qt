#ifndef GAMEFILD_H
#define GAMEFILD_H

#include <QtCore>
#include <QtGui>

class GameFild
{
public:
    GameFild(int Count, int Width, int X, int Y);

    void Draw(QPainter &painter);

private:

    int X;
    int Y;
    int Rect_Width;
    int Count;

    QBrush Brush;
    QPen Pen;

};

#endif // GAMEFILD_H
