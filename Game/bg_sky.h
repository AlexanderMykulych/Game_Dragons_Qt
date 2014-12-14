#ifndef BG_SKY_H
#define BG_SKY_H

#include "game_object.h"
#include <vector>
#include <QRectF>
#include <QMessageBox>

using namespace std;

class BG_Sky
{
public:
    BG_Sky(int X, int Y, int Width, int Height);
    void Draw(QPainter &painter);
    void Process();
private:
    int X;
    int Y;
    int Width;
    int Height;
    void LoadAll();
    vector<Game_Object*> Cloud;
    QImage *img_Cloud[3];
    //cloud move
    int Move_Interval;
    int Move_Counter;


    //debug
    void Message(QString Text = "Some Text");
};

#endif // BG_SKY_H
