#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QFile>
#include <propertis.h>
#include <QtCore>
#include <QtGui>
#include <myfont.h>
#include <QTimer>
#include "gamebutton.h"
#include <QDesktopWidget>
#include "gameedit.h"
#include "gamelabel.h"
#include "gamecombobox.h"
#include "server_finder.h"
#include "gameloadanimation.h"
#include "client.h"
#include "mystringlist.h"
#include "messageformat.h"
#include "game_canvas.h"
#include <QInputDialog>

//for debug
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    void set_Name(QString Name) {My_Name = Name;}
    ~Form();

    //Change Display Setting
    int Old_Display_Width;
    int Old_Display_Height;
private:
    Ui::Form *ui;

    void closeEvent(QCloseEvent *event);


    TGameStage GameStage;
    TGamePoint *GamePoint;
    //CONVERSATION
    MessageFormat *Msg_Format;
    //load all
       void LoadAll();

       ////////Client Socket
      GameClient *client;

    QString My_Name;
 //images
    QImage imgMenu;

 //timer
    QTimer *Timer;
    void setProgramSize();

  //Find Server
    Server_Finder *Finder;
    bool Find_Server_if_Find;
    QHostAddress Find_Server_Host_Server;
    GameLoadAnimation *Find_Server_Loader;
    QTimer *Find_Server_Timer;
    void Create_Find_Server();


    //PROGRAM START
 //fonts
    MyFont *Font_Prog_Start;
    int Font_PS_Time;
    int Font_PS_Timer;
    void Draw_Menu_BackGround(QImage &img, QPainter &painter, int opacity);
    void Make_Visible();


  //MENU
    GameButton *Menu_Button_New;
    GameButton *Menu_Button_Exit;
    void CreateMenu();
    void Draw_Menu_Button(GameButton *button, QPainter &painter);
    bool Menu_Button_Mouse_Pressed(int x, int y, GameButton *button);
    bool Menu_Button_Mouse_Release(GameButton *button);

  //New Game
    GameButton *New_Game_Button_Back;
    GameButton *New_Game_Button_NewLobby;
    GameButton *New_Game_Button_ConnectToLobby;
    bool Create_New_Game();
    void Draw_Dark_Glass(int opacity, QPainter &painter);

  //New Lobby
    GameButton *New_Lobby_Button_Create;
    GameButton *New_Lobby_Button_Back;
    GameEdit *New_Lobby_Edit_Create;
    GameLabel *New_Lobby_Label_Create;
    GameComboBox *New_Lobby_Combobox_Player_1;
    GameComboBox *New_Lobby_Combobox_Player_2;
    GameComboBox *New_Lobby_Combobox_Player_3;
    void Create_New_Lobby();
    void ACreate_New_Lobby();
    void Draw_Label(GameLabel *label, int flag, QPainter &painter);

  //Connect To Lobby
    GameButton *Connect_To_Lobby_Button_Connect;
    GameButton *Connect_To_Lobby_Button_Back;
    GameComboBox *Connect_To_Lobby_ComboBox_Connect;
    GameLabel *Connect_To_Lobby_Label_Connect;
    QStringList Connect_To_Lobby_List;
    void Connect_To_Lobby_Refresh();
    void Create_Connect_To_Lobby();
    void ACreate_Connect_To_Lobby();
    void BCreate_Connect_To_Lobby();


  //Lobby
    QString Now_Lobby_Name;
    GameLabel *Lobby_Label_Title;
    GameLabel *Lobby_Label_Clients_Title;
    GameLabel *Lobby_Label_Client_Name[CLIENT_COUNT];
    GameLabel *Lobby_Label_Type_Title;
    GameLabel *Lobby_Label_Client_Player_Type[CLIENT_COUNT];
    void Create_Lobby();
    void Lobby_Set_Inform(QString Name, QString Client_Names,
                          QString Player_1, QString Player_2, QString Player_3);
    void Draw_Lobby(QPainter &painter);
    bool ADMIN;


    //Game canvas
    TGame_Canvas *Game_Canvas;
  //Testing
    void Make_Some_Testing();
    void Draw_Testing(QPainter &painter);
    void Create_Testing();
       /////TEST/////////////

    //debug
    void MessageF(QString Text);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void my_close();

    void time_out();

    //Client
    void MessageCatching(QString Text);
    void Disconnected();

    //Find Server
    void Find_Server_Read_Message(QString Message, QHostAddress adress);
    void Find_Server_Timer_Out();

    //New Lobby
    void New_Lobby_Edit_Text_Change(QString Text);

    //Testing

};

#endif // FORM_H
