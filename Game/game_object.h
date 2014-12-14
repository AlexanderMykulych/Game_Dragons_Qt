#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <QtGui>
#include <QtCore>
#include <QImage>

class Game_Object
{
public:
    Game_Object(QImage *Image, int Image_Number, QRectF RectTarget, qreal Rotate = 0);
    void Draw(QPainter &painter);
    int get_X() {return this->X;}
    int get_Y() {return this->Y;}
    int get_Width() {return this->Width;}
    int get_Height() {return this->Height;}
    int get_ImageId() {return this->Image_Id;}
    void set_X(int X);
    void set_Y(int Y);
    void set_Width(int Width);
    void set_Height(int Height);
    void set_X_Up(int Plus);
    void set_Y_Up(int Plus);
    void set_Width_Up(int Plus);
    void set_Height_Up(int Plus);
    void set_Image_Id(int Image_Id = 0);
    void Next_Image();
    void set_Image_Number(int Image_Number);
    void set_Image(QImage *Image);
    void set_Rotate(qreal Rotate);
    qreal get_Rotate() {return Rotate;}

private:
    int X;
    int Y;
    int Width;
    int Height;

    int Frame_Width;

    int Image_Number;
    int Image_Id;
    QImage *Image;
    QImage Rotate_Image;
    QRectF RectTarget;
    QRectF RectSource;
    qreal Rotate;

    void RT_Update();
};

#endif // GAME_OBJECT_H
