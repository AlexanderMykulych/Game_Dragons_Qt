#include "gameedit.h"

GameEdit::GameEdit(int x, int y, int width, int font_size, QWidget *parent) :
    QLineEdit(parent)
{
    this->setStyleSheet(
                        "color: rgb(0,0,0);"
                        "background-color: rgb(245, 255, 250);"
                        "selection-color: rgb(255, 255, 255);"
                        "selection-background-color: rgb(211, 211, 211);"
                        "border: 2px solid black;"
                        "border-radius: 4px;"
                        );


    int idFont = QFontDatabase::addApplicationFont(":/font_edit_1.ttf");
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    Font.setPointSize(font_size);
    this->setFont(Font);
    this->setGeometry(x, y, width, font_size+20);

    connect(this, SIGNAL(textChanged(QString)), this, SLOT(textChange(QString)));
}

void GameEdit::Draw(QPainter *painter)
{
   // emit QLineEdit::paintEvent();
}

void GameEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
}



