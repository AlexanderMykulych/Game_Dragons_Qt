#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include "sockettest.h"
#include "crosszero.h"
#include "gamefild.h"
#include <QtCore>
#include <QtGui>
#include <vector>

enum TGameDraw {GD_None, GD_DrawText, GD_DrawGame};

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_New_Game_clicked();
    void on_Exit_clicked();
    void MessageCatch(QString Text);

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    SocketTest *Client;

    GameFild *Fild;
    vector<CrossZero*> CZ;

    QString Adress;

    TGameDraw GameDraw;

    //GD_Text
    QString DT_Text;

    //GD_Game
    int Matrix[10][10];


    int Count;
};

#endif // MAINWINDOW_H
