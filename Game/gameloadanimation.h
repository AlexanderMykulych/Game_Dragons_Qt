#ifndef GAMELOADANIMATION_H
#define GAMELOADANIMATION_H

#include <QObject>
#include <QImage>
#include <QtGui>
#include <QtCore>
#include "gamelabel.h"
#include "propertis.h"
#include <QMessageBox>

class GameLoadAnimation : public QObject
{
    Q_OBJECT
public:
    explicit GameLoadAnimation(int x, int y, int width, QString Text, QObject *parent = 0);
    void Draw(QPainter &painter);
private:
    int X;
    int Y;
    int Width;
    int Height;
    QImage img;
    int Index;
    int Image_Count;
    int Frame_Width;
    QRectF RTarget;
    QString Text;

    GameLabel *label;

    void Next_Frame();


signals:

public slots:

};

#endif // GAMELOADANIMATION_H
