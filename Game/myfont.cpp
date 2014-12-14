#include "myfont.h"



MyFont::MyFont(QString Name, int Size)
{
    Change(Name, Size);
}

void MyFont::Change(QString Name, int Size)
{
    this->Name = Name;
    this->Size = Size;
    //
    int idFont = QFontDatabase::addApplicationFont(Name);
    Font = QFont(QFontDatabase::applicationFontFamilies(idFont).first());
    Font.setPointSize(Size);
}

void MyFont::Change(QString Name)
{
    Change(Name, this->Size);
}
