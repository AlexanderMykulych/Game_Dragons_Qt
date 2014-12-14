#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QObject>
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

const int IMAGE_COUNT = 2;

class GameButton : public QObject
{
    Q_OBJECT
public:
    explicit GameButton(int X, int Y, int Width,int FontSize,
                        QString Text, int ID, bool Enable, QObject *parent);
    void Draw(QPainter &painter);
    inline int getX() {return X;}
    inline int getY() {return Y;}
    inline int getWidth() {return Width;}
    inline int getHeight() {return Height;}
    inline bool ifCoordInBut(int x, int y) {return (x>=X && y>=Y && x<=X+Width && y<=Y+Height);}
    inline bool ifPressed() {return Pressed;}
    void setPress(bool pressed);
    inline void setEnabled(bool enable) {Enable = enable;}
protected:
    int X;
    int Y;
    int Width;
    int Height;
    int FontSize;
    QString Text;
    int ID;
    bool Pressed;
    QImage img;
    QFont Font;
    QRectF RectTarget;
    QRectF RectSource;
    bool Enable;
    void ChangeFontAndRect();
signals:

public slots:

};

#endif // GAMEBUTTON_H
