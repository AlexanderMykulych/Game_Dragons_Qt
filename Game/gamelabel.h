#ifndef GAMELABEL_H
#define GAMELABEL_H

#include <QObject>
#include <QString>
#include <QtGui>
#include <QtCore>
#include <QFont>
#include "propertis.h"


class GameLabel : public QObject
{
    Q_OBJECT
public:
    explicit GameLabel(int x, int y, int width, int font_size, QString text,
                       int flag, QString font_dir, QColor color, QObject *parent = 0);
    inline void set_Text(QString New_Text) {Text = New_Text;}
    void Draw(int flag, QPainter &painter);
    bool setColor(QColor New_Color);
private:
    int X;
    int Y;
    int Width;
    int Height;
    QString Text;
    int Flag;
    QString Font_Dir;
    QFont Font;
    int Font_Size;
    QColor Color;

signals:

public slots:

};

#endif // GAMELABEL_H
