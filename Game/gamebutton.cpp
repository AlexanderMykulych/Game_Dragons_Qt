#include "gamebutton.h"

GameButton::GameButton(int X, int Y, int Width, int FontSize, QString Text, int ID, bool Enable, QObject *parent) :
    QObject(parent)
{
    this->X = X;
    this->Y = Y;
    this->Width = Width;
    this->Text = Text;
    this->ID = ID;
    this->FontSize = FontSize;
    this->Enable = Enable;
    Pressed = false;
    if(ID)
        img.load(":/dragon_button.png");
    else
        img.load(":/button_2.png");
    double prop = (this->Width*100.0) / double(img.width());
    this->Height = (prop*img.height())/200.0;

    int idFont = QFontDatabase::addApplicationFont(":/font_fire_1.ttf");
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());

    RectTarget = QRectF(this->X, this->Y, this->Width, this->Height);
    ChangeFontAndRect();
}

void GameButton::Draw(QPainter &painter)
{
    if(!Enable)
        return;
    painter.drawImage(RectTarget, img, RectSource);
    painter.setFont(Font);
    painter.setPen(Qt::white);
    painter.drawText(RectTarget, Qt::AlignCenter, Text);
}

void GameButton::setPress(bool pressed)
{
    if(!Enable)
        return;
    if(pressed!= Pressed)
    {
        Pressed = pressed;
        ChangeFontAndRect();
    }
}

void GameButton::ChangeFontAndRect()
{
    if(Pressed)
    {
        RectSource = QRectF(0,img.height() / IMAGE_COUNT, img.width(), img.height() / IMAGE_COUNT);
        Font.setPointSize(FontSize-FontSize*15/100);
        Font.setBold(true);
    }
    else
    {
        RectSource = QRectF(0,0,img.width(), img.height() / IMAGE_COUNT);
        Font.setPointSize(FontSize);
        Font.setBold(true);
    }
}
