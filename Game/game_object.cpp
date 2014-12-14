#include "game_object.h"

Game_Object::Game_Object(QImage *Image, int Image_Number, QRectF RectTarget, qreal Rotate)
{
    this->Image = Image;
    this->Image_Number = Image_Number;
    this->Image_Id = 0;
    this->RectTarget = RectTarget;
    this->X = RectTarget.x();
    this->Y = RectTarget.y();
    this->Width = RectTarget.width();
    this->Height = RectTarget.height();

    this->Frame_Width = this->Image->width() / this->Image_Number;

    this->RectSource = QRectF(this->Frame_Width * this->Image_Id,
                              0,
                              this->Frame_Width * (this->Image_Id+1),
                              this->Image->height());

    this->Rotate = Rotate;

    QMatrix matrix_rotate;
    Rotate_Image = this->Image->copy(RectSource.x(), RectSource.y(), RectSource.width(), RectSource.height());
    Rotate_Image = Rotate_Image.transformed(matrix_rotate.rotate(Rotate), Qt::FastTransformation);
}

void Game_Object::Draw(QPainter &painter)
{
    painter.drawImage(RectTarget, Rotate_Image);

    //////////Testing//////////////////////
//    QBrush Old_Brush = painter.brush();
//    QBrush Brush(QColor::fromRgb(100,100,100,0));
//    painter.setBrush(Brush);
//    painter.drawRect(RectTarget);
//    painter.setBrush(Old_Brush);

}

void Game_Object::set_X(int X)
{
    this->X = X;
    RT_Update();
}

void Game_Object::set_Y(int Y)
{
    this->Y = Y;
    RT_Update();
}

void Game_Object::set_Width(int Width)
{
    this->Width = Width;
    RT_Update();
}

void Game_Object::set_Height(int Height)
{
    this->Height = Height;
    RT_Update();
}

void Game_Object::set_X_Up(int Plus)
{
    this->X += Plus;
    RT_Update();
}

void Game_Object::set_Y_Up(int Plus)
{
    this->Y += Plus;
    RT_Update();
}

void Game_Object::set_Width_Up(int Plus)
{
    this->Width += Plus;
    RT_Update();
}

void Game_Object::set_Height_Up(int Plus)
{
    this->Height += Plus;
    RT_Update();
}

void Game_Object::set_Image_Id(int Image_Id)
{
    this->Image_Id = Image_Id;
}

void Game_Object::Next_Image()
{
    this->Image_Id++;
    this->Image_Id %= this->Image_Number;

    this->RectSource = QRectF(this->Frame_Width * this->Image_Id,
                              0,
                              this->Frame_Width,
                              this->Image->height());

    QMatrix matrix_rotate;
    Rotate_Image = Image->copy(RectSource.x(), RectSource.y(), RectSource.width(), RectSource.height());
    Rotate_Image = Rotate_Image.transformed(matrix_rotate.rotate(Rotate), Qt::FastTransformation);
}

void Game_Object::set_Image_Number(int Image_Number)
{
    this->Image_Number = Image_Number;
}

void Game_Object::set_Image(QImage *Image)
{
    this->Image = Image;
}

void Game_Object::set_Rotate(qreal Rotate)
{
    this->Rotate = Rotate;
}


void Game_Object::RT_Update()
{
    RectTarget = QRectF(this->X, this->Y, this->Width, this->Height);
}
