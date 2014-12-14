#ifndef MYFONT_H
#define MYFONT_H
#include <QString>
#include <QFont>
#include <QFontDatabase>
#include <QtCore>
#include <QtGui>

class MyFont
{
public:
    MyFont(QString Name, int Size);
    void Change(QString Name, int Size);
    void Change(QString Name);
    inline void SetSize(int NewSize) {Size = NewSize; Font.setPointSize(NewSize);}
    inline void SetSize(double NewSize) {Size = NewSize; Font.setPointSizeF(NewSize);}
    inline int GetSize() {return Size;}
    QFont Font;
private:
    QString Name;
    double Size;
};

#endif // MYFONT_H
