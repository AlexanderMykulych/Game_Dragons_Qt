#include "gameloadanimation.h"

GameLoadAnimation::GameLoadAnimation(int x, int y, int width, QString Text, QObject *parent) :
    QObject(parent)
{
    this->X = x;
    this->Y = y;
    this->Width = width;

    this->Text = Text;

    img.load(":/Loading.png");


    Index = 1;
    Image_Count = 8;

    Frame_Width = img.width() / Image_Count;
    this->Height = (this->Width*img.height())/Frame_Width;

    RTarget = QRectF(this->X, this->Y,
                     this->Width, this->Height);

    label = new GameLabel(this->X - this->Width, this->Y + this->Height + 10,
                          3*this->Width,
                          20,
                          this->Text,
                          Qt::AlignCenter,
                          ":/font_simple.ttf",
                          Qt::white,
                          this);
}

void GameLoadAnimation::Draw(QPainter &painter)
{
    QRectF RSource(Frame_Width*Index, 0, Frame_Width, img.height());
    painter.drawImage(RTarget, img, RSource);

    label->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT,
                painter);
    Next_Frame();
}

void GameLoadAnimation::Next_Frame()
{
    Index = (Index + 1) % Image_Count;
}
