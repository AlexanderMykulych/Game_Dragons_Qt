#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Count = 4;

    connect(ui->action, SIGNAL(triggered()), this, SLOT(on_New_Game_clicked()));
    connect(ui->action_3, SIGNAL(triggered()), this, SLOT(on_Exit_clicked()));
    Fild = new GameFild(4, 100, 100, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Client = new SocketTest(this);
    //Client->writeMyText();
}

void MainWindow::on_New_Game_clicked()
{
    bool ok = false;
    while(!ok)
        Adress = QInputDialog::getText(this, tr("Set Ip:"), tr("ip:"), QLineEdit::Normal, "<ip adress>", &ok);

    Client = new SocketTest(Adress, this);
    connect(Client, SIGNAL(MessageCatch(QString)), this, SLOT(MessageCatch(QString)));
}

void MainWindow::on_Exit_clicked()
{
    close();
}

void MainWindow::MessageCatch(QString Text)
{
    QStringList Message = Text.split("}");
    for(int i = 0; i < Message.size() - 1; i++)
    {
        QStringList msg = Message[i].split("!");
        int Theme = msg[0].toInt();
        QString Data = msg[1];


//        QMessageBox msg1;
//        msg1.setText(QString::number(Theme));
//        msg1.exec();

        switch(Theme)
        {
            case 1:
            {
                GameDraw = GD_DrawText;
                DT_Text = "Wait for client 2!";
                break;
            }
            case 2:
            {
                GameDraw = GD_DrawGame;
                QStringList List = Data.split(",");
                for(int i1=0; i1 < List.size() - 1; i1++)
                {
                    int id1 = i1/Count;
                    int id2 = i1%Count;
                    Matrix[id1][id2] = List[i1].toInt();

                    int X = id1*100 + 100;
                    int Y = id2*100 + 100;



                    if(CZ.size()<=i1)
                    {
                        CrossZero *cz = new CrossZero(X, Y, 100, 100, CZType(Matrix[id1][id2]));

                        CZ.push_back(cz);
                    }
                    else
                    {
                        CZ[i1]->setX(X);
                        CZ[i1]->setY(Y);
                        CZ[i1]->setType(CZType(Matrix[id1][id2]));
                    }
                }
                break;
            }
        }

    }
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush Brush(QColor::fromRgb(255, 255, 0, 255));
    QPen Pen(QColor::fromRgb(255, 0, 0, 255));
    QFont Font;
    Font.setPointSize(50);

    painter.setBrush(Brush);
    painter.setPen(Pen);
    painter.setFont(Font);
    switch(GameDraw)
    {
           case GD_DrawText:
            {
                painter.drawText(QRectF(0,0,this->width(), this->height()), Qt::AlignCenter, DT_Text);
                 break;
            }
           case GD_DrawGame:
            {
                 Fild->Draw(painter);
                 for(int i = 0; i < CZ.size(); i++)
                 {
                     CZ[i]->Draw(painter);
                     exit(0);
                 }
                 break;
            }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    QMessageBox msg;
//    msg.setText(QString::number(event->x()) + " " + QString::number(event->y()));
//    msg.exec();
    if(GameDraw == GD_DrawGame)
    {



        if(event->x()>=100 && event->x()<=100+ Count*100 && event->y() >= 100 && event->y()<=100 + Count*100)
        {
            int X = event->x() - 100;
            int Y = event->y() - 100;

            int i = X/100;
            int j = Y/100;

                QMessageBox msg;
                msg.setText(QString::number(i) + " " + QString::number(j));
                msg.exec();

            Client->writeMyText(QString::number(i) + "!" + QString::number(j)+"}");
        }

    }
}
