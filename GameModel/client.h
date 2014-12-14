#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include "propertis.h"
#include "bullet.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(int clientNum, QObject *parent = 0);
    int clientNum;
    QString Name;
    int Lobby_ID;
    void Delete();
    bool Enable;
    void Process();

    void set_X(int X);
    void set_Y(int Y);
    void set_Width(int Width);
    void set_Height(int Height);
    void set_SpeedUp(int SpeedUp);
    int get_X() {return X;}
    int get_Y() {return Y;}
    int get_Width() {return Width;}
    int get_Height() {return Height;}
    int get_Side() {return Side;}
    int get_Life() {return Life;}
    int get_Points() {return Points;}
    void set_Up();
    void set_Down();
    void set_Left();
    void set_Right();
    void set_Side(int Side);
    void setFild(QRectF Fild) {this->Fild = Fild;}
    QRectF get_Rect() {return QRectF(X, Y, Width, Height);}


    Bullet* Fire();

    void BulletIsHit();
    void EnemyIsDead();
private:
    int X;
    int Y;
    int Width;
    int Height;
    int Speed_Up;
    int Side;

    QRectF Fild;

    int Fire_Interv;
    int Fire_Interv_Count;

    //Life
    int Life;
    //Points
    int Points;

    int Move_Count;
    int Move_Count_Inter;
signals:

public slots:

};

#endif // CLIENT_H
