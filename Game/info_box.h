#ifndef INFO_BOX_H
#define INFO_BOX_H

#include <QtGui>
#include <QtCore>
#include <vector>

using namespace std;

class Info_Box
{
public:
    Info_Box(int X, int Y, int Width, int Height, vector<QString> Inf);
    void Draw(QPainter &painter);
    void set_Inf(vector<QString> inf);
private:
    vector<QString> Inf;
    int X;
    int Y;
    int Width;
    int Height;
    QFont Font;
};

#endif // INFO_BOX_H
