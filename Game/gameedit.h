#ifndef GAMEEDIT_H
#define GAMEEDIT_H

#include <QLineEdit>
#include <QString>
#include <QtCore>
#include <QtGui>

class GameEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit GameEdit(int x, int y, int width, int font_size, QWidget *parent = 0);
    void Draw(QPainter *painter);
private:
    QFont Font;
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // GAMEEDIT_H
