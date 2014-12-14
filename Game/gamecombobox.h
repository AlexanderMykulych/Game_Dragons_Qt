#ifndef GAMECOMBOBOX_H
#define GAMECOMBOBOX_H

#include <QComboBox>
#include <QFont>
#include <QtCore>
#include <QtGui>
#include <QIcon>
#include "mystringlist.h"
#include <QStringList>
#include <QString>

class GameComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit GameComboBox(int x, int y, int width, int font_size, MyStringList Item_List, QWidget *parent = 0);

private:
    int X;
    int Y;
    int Width;
    int Height;
    int Font_Size;
    QFont Font;
    QIcon Icon_Lock;
    QIcon Icon_Unlock;
    MyStringList Item_List;

    void paintEvent(QPaintEvent *event);
signals:

public slots:

};

#endif // GAMECOMBOBOX_H
