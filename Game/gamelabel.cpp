#include "gamelabel.h"

GameLabel::GameLabel(int x, int y, int width, int font_size,
                     QString text, int flag, QString font_dir, QColor color, QObject *parent) :
    QObject(parent)
{
    this->X = x;
    this->Y = y;
    this->Width = width;
    this->Height = font_size + 10;
    this->Text = text;
    this->Flag = flag;
    this->Font_Dir = font_dir;
    this->Color = color;
    this->Font_Size = font_size;
    int idFont = QFontDatabase::addApplicationFont(font_dir);
    this->Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    this->Font.setPointSize(this->Font_Size);
}

void GameLabel::Draw(int flag, QPainter &painter)
{
    switch(flag)
    {
        case LABEL_FLAG_DRAW_BOUNDING:
        {
            QPen Pen_Old = painter.pen();
            QPen Pen(Qt::white);
            painter.setPen(Pen);
            painter.drawRect(this->X,
                             this->Y,
                             this->Width,
                             this->Height);
            painter.setPen(Pen_Old);
            break;
        }
    }

    QPen Pen_Old = painter.pen();
    QPen Pen(Color);
    painter.setPen(Pen);

    QRectF R1(X, Y, Width, Height);
    QFont Font_Old = painter.font();

    painter.setFont(Font);
    painter.drawText(R1, Flag, Text);
    painter.setFont(Font_Old);

    painter.setPen(Pen_Old);
}

bool GameLabel::setColor(QColor New_Color)
{
    Color = New_Color;
}
