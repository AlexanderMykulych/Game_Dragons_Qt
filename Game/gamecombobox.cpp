#include "gamecombobox.h"

GameComboBox::GameComboBox(int x, int y, int width, int font_size, MyStringList Item_List, QWidget *parent) :
    QComboBox(parent)
{
    this->X = x;
    this->Y = y;
    this->Width = width;
    this->Height = font_size+20;
    this->Font_Size = font_size;

    Icon_Lock = QIcon(":/lock_red.ico");
    Icon_Unlock = QIcon(":/unlock_red.ico");


    this->setStyleSheet("color: rgb(0,0,0);"
                        "background-color: rgb(245, 255, 250);"
                        "selection-color: rgb(255, 255, 255);"
                        "selection-background-color: rgb(211, 211, 211);"
                        "border: 2px solid black;"
                        "border-radius: 4px;");

    this->setGeometry(this->X,
                      this->Y,
                      this->Width,
                      this->Height);

    int idFont = QFontDatabase::addApplicationFont(":/font_edit_1.ttf");
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    Font.setPointSize(this->Font_Size);

    this->setFont(Font);
    this->setIconSize(QSize(25, 25));
    this->addItems(Item_List.List);
    for(int i=0; i<Item_List.Lock.size(); i++)
    {
        if(Item_List.Lock[i])
            this->setItemIcon(i, Icon_Lock);
        else
            this->setItemIcon(i, Icon_Unlock);
    }

}

void GameComboBox::paintEvent(QPaintEvent *event)
{
    QComboBox::paintEvent(event);
}
