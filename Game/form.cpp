#include "form.h"
#include "ui_form.h"

void Message(QString Text)
{
    QMessageBox msg;
    msg.setText(Text);
    msg.exec();
}



Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    connect(this, SIGNAL(), this, SLOT(my_close()));

    My_Name = "";

    while(My_Name == "")
    {
        My_Name = QInputDialog::getText(this,
                                        "Enter your name pls",
                                        "Name:",
                                        QLineEdit::Normal,
                                        QDir::home().dirName());
    }

    setProgramSize();


    //font change time

    LoadAll();

    GameStage = GS_Find_Server;

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(time_out()));
    Timer->start(10);

}

Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *event)
{
    DEVMODE dm;

    dm.dmSize = sizeof(DEVMODE);

    dm.dmPelsWidth = Old_Display_Width;
    dm.dmPelsHeight = Old_Display_Height;

    dm.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT;;

    ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
}

//void Form::Change_Display_Size(int New_Width, int New_Height)
//{
//    QDesktopWidget *descktop = QApplication::desktop();
//    Old_Display_Width = descktop->width();
//    Old_Display_Width = descktop->height();

//    //change display size
//    {
//        DEVMODE dm;

//        dm.dmSize = sizeof(DEVMODE);

//        dm.dmPelsWidth = 1024;
//        dm.dmPelsHeight = 768;

//        dm.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT;;

//        ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
//    }
//}



void Form::LoadAll()
{
    //create client
    client = new Client(this);
    connect(client, SIGNAL(MessageCatching(QString)), this, SLOT(MessageCatching(QString)));
    connect(client, SIGNAL(Disconnected()), this, SLOT(Disconnected()));

    Msg_Format = new MessageFormat(client);

    imgMenu.load(":/RedDragon.png");


    //load font
    {
        Font_Prog_Start = new MyFont(":/font_fire_2.ttf",FONT_PS_MAX_SIZE);
    }
    //load Menu
    CreateMenu();
    //load new game
    Create_New_Game();
    //load new lobby
    Create_New_Lobby();
    //load connect to lobby
    Create_Connect_To_Lobby();
    //load Testing
    Create_Testing();
    //load Server Find
    Create_Find_Server();
    //load lobby
    Create_Lobby();

}

void Form::setProgramSize()
{
    this->resize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

//    QDesktopWidget *descktop = QApplication::desktop();
//    this->resize(descktop->width(), descktop->height());
   // MessageF(QString::number(descktop->width()));
}

void Form::Create_Find_Server()
{
    Finder = new Server_Finder(CLIENT_PORT, this);

    connect(Finder, SIGNAL(Read_Answer(QString,QHostAddress)),
            this, SLOT(Find_Server_Read_Message(QString,QHostAddress)));

    Find_Server_Loader = new GameLoadAnimation(this->width()/2 - LOADER_WIDTH / 2,
                                               this->height()/2 - LOADER_HEIGHT / 2,
                                               LOADER_WIDTH,
                                               "Find server...",
                                               this);

    Find_Server_if_Find = false;

    Find_Server_Timer = new QTimer(this);
    connect(Find_Server_Timer, SIGNAL(timeout()), this, SLOT(Find_Server_Timer_Out()));
    Find_Server_Timer->start(2000);

}

void Form::Draw_Menu_BackGround(QImage &img, QPainter &painter, int opacity)
{
    //Draw BackGround
    QRectF RTarget(0,0,this->width(), this->height());
    QRectF RSource(0,0,img.width(),img.height());
    painter.drawImage(RTarget, img, RSource);
    Draw_Dark_Glass(opacity, painter);
}

void Form::Make_Visible()
{
    New_Lobby_Edit_Create->setVisible(GameStage == GS_New_Lobby);
    New_Lobby_Edit_Create->setEnabled(GameStage == GS_New_Lobby);

    Connect_To_Lobby_ComboBox_Connect->setVisible(GameStage == GS_Connect_To_Lobby);
    Connect_To_Lobby_ComboBox_Connect->setEnabled(GameStage == GS_Connect_To_Lobby);

    New_Lobby_Combobox_Player_1->setVisible(GameStage == GS_New_Lobby);
    New_Lobby_Combobox_Player_1->setEnabled(GameStage == GS_New_Lobby);

    New_Lobby_Combobox_Player_2->setVisible(GameStage == GS_New_Lobby);
    New_Lobby_Combobox_Player_2->setEnabled(GameStage == GS_New_Lobby);

    New_Lobby_Combobox_Player_3->setVisible(GameStage == GS_New_Lobby);
    New_Lobby_Combobox_Player_3->setEnabled(GameStage == GS_New_Lobby);

}

void Form::CreateMenu()
{
    Menu_Button_New = new GameButton(100,100,BUTTON_WIDTH,BUTTON_FONT_SIZE,"NewGame", 1, true, this);
    Menu_Button_Exit = new GameButton(100,500,BUTTON_WIDTH,BUTTON_FONT_SIZE,"Exit", 1, true, this);
}

void Form::Draw_Menu_Button(GameButton *button, QPainter &painter)
{
    if(button)
        button->Draw(painter);
}

bool Form::Menu_Button_Mouse_Pressed(int x, int y, GameButton *button)
{
    if(button)
    {
        bool press = button->ifCoordInBut(x,y);
        button->setPress(press);
        return press;
    }
    return 0;
}

bool Form::Menu_Button_Mouse_Release(GameButton *button)
{
    if(button)
        if(button->ifPressed())
            button->setPress(false);
}

bool Form::Create_New_Game()
{
    int koef_shift = 20;
    New_Game_Button_Back = new GameButton(this->width() / 2 - BUTTON_WIDTH / 2,
                                          400,
                                          BUTTON_WIDTH,
                                          BUTTON_FONT_SIZE,
                                          "Back",
                                          0,
                                          true,
                                          this);

    New_Game_Button_NewLobby = new GameButton(this->width() / 2 - BUTTON_WIDTH - koef_shift,
                                             50,
                                             BUTTON_WIDTH,
                                             BUTTON_FONT_SIZE,
                                             "New Lobby",
                                             1,
                                             true,
                                             this);

    New_Game_Button_ConnectToLobby = new GameButton(this->width() / 2 + koef_shift,
                                                   50,
                                                   BUTTON_WIDTH,
                                                   BUTTON_FONT_SIZE,
                                                   "Connect to lobby",
                                                   1,
                                                    true,
                                                    this);
}

void Form::Draw_Dark_Glass(int opacity, QPainter &painter)
{
    QBrush Brush_Old = painter.brush();
    QPen Pen_Old = painter.pen();

    QBrush Brush_New(QColor::fromRgb(0, 0, 0, opacity), Qt::SolidPattern);
    QPen Pen_New(QColor::fromRgb(0, 0, 0, opacity));

    painter.setPen(Pen_New);
    painter.setBrush(Brush_New);
    painter.drawRect(0, 0, this->width(), this->height());

    painter.setPen(Pen_Old);
    painter.setBrush(Brush_Old);
}

void Form::Create_New_Lobby()
{
    New_Lobby_Button_Create = new GameButton(this->width()/2 - BUTTON_WIDTH/2,
                                             400,
                                             BUTTON_WIDTH,
                                             BUTTON_FONT_SIZE,
                                             "Create new lobby",
                                             0,
                                             false,
                                             this);

    New_Lobby_Button_Back = new GameButton(this->width()/2 - BUTTON_WIDTH/2,
                                             600,
                                             BUTTON_WIDTH,
                                             BUTTON_FONT_SIZE,
                                             "Back",
                                             0,
                                             true,
                                             this);


    New_Lobby_Edit_Create = new GameEdit(this->width()/2 - NEW_LOBBY_EDIT_WIDTH/2,
                                         50,
                                         NEW_LOBBY_EDIT_WIDTH,
                                         NEW_LOBBY_EDIT_FONT_SIZE,
                                         this);
    connect(New_Lobby_Edit_Create, SIGNAL(textChanged(QString)),
            this, SLOT(New_Lobby_Edit_Text_Change(QString)));


    New_Lobby_Label_Create = new GameLabel(this->width()/2 - NEW_LOBBY_EDIT_WIDTH/2,
                                           10,
                                           NEW_LOBBY_EDIT_WIDTH,
                                           NEW_LOBBY_EDIT_FONT_SIZE,
                                           "Write the lobby name:",
                                           Qt::AlignCenter,
                                           ":/font_simple.ttf",
                                           Qt::white,
                                           this);


    {
        MyStringList list;
        list.push(false, "<None>");
        list.push(false, "Bot");
        list.push(false, "Player");

        int top1 = 100;
        int top2 = top1 + 50;
        int top3 = top2 + 50;

        New_Lobby_Combobox_Player_1 = new GameComboBox(this->width() / 2 - NEW_LOBBY_EDIT_WIDTH / 2,
                                                       top1,
                                                       NEW_LOBBY_EDIT_WIDTH,
                                                       NEW_LOBBY_EDIT_FONT_SIZE,
                                                       list,
                                                       this);

        New_Lobby_Combobox_Player_2 = new GameComboBox(this->width() / 2 - NEW_LOBBY_EDIT_WIDTH / 2,
                                                       top2,
                                                       NEW_LOBBY_EDIT_WIDTH,
                                                       NEW_LOBBY_EDIT_FONT_SIZE,
                                                       list,
                                                       this);

        New_Lobby_Combobox_Player_3 = new GameComboBox(this->width() / 2 - NEW_LOBBY_EDIT_WIDTH / 2,
                                                       top3,
                                                       NEW_LOBBY_EDIT_WIDTH,
                                                       NEW_LOBBY_EDIT_FONT_SIZE,
                                                       list,
                                                       this);
    }

}

void Form::ACreate_New_Lobby()
{
       Msg_Format->Clean();
       Now_Lobby_Name = New_Lobby_Edit_Create->text();
       Msg_Format->Send_Message(TM_CREATE_NEW_LOBBY_NAME, New_Lobby_Edit_Create->text());
}

void Form::Draw_Label(GameLabel *label, int flag, QPainter &painter)
{
    label->Draw(flag, painter);
}

void Form::Connect_To_Lobby_Refresh()
{
    Connect_To_Lobby_ComboBox_Connect->clear();
    Connect_To_Lobby_ComboBox_Connect->addItems(Connect_To_Lobby_List);
}

void Form::Create_Connect_To_Lobby()
{
    Connect_To_Lobby_Button_Connect = new GameButton(this->width()/2 - BUTTON_WIDTH/2,
                                                     300,
                                                     BUTTON_WIDTH,
                                                     BUTTON_FONT_SIZE,
                                                     "Connect",
                                                     0,
                                                     true,
                                                     this);

    Connect_To_Lobby_Button_Back = new GameButton(this->width()/2 - BUTTON_WIDTH/2,
                                                     600,
                                                     BUTTON_WIDTH,
                                                     BUTTON_FONT_SIZE,
                                                     "Back",
                                                     0,
                                                     true,
                                                     this);
    /////////////Delete this list later
    {
        MyStringList list;
        Connect_To_Lobby_ComboBox_Connect = new GameComboBox(this->width()/2 - CONNECT_TO_LOBBY_COMBOBOX_WIDTH/2,
                                                         100,
                                                         CONNECT_TO_LOBBY_COMBOBOX_WIDTH,
                                                         CONNECT_TO_LOBBY_COMBOBOX_FONT_SIZE,
                                                         list,
                                                         this);

        Connect_To_Lobby_Label_Connect = new GameLabel(this->width()/2 - CONNECT_TO_LOBBY_COMBOBOX_WIDTH/2,
                                                       50,
                                                       CONNECT_TO_LOBBY_COMBOBOX_WIDTH,
                                                       CONNECT_TO_LOBBY_COMBOBOX_FONT_SIZE,
                                                       "Choose lobby:",
                                                       Qt::AlignCenter,
                                                       ":/font_simple.ttf",
                                                       Qt::white,
                                                       this);
    }
}

void Form::ACreate_Connect_To_Lobby()
{
    Msg_Format->Send_Message(TM_LOBBY_LIST, QString::number(TM_NONE));
}

void Form::BCreate_Connect_To_Lobby()
{
   Msg_Format->Send_Message(TM_CONNECT_TO_LOBBY, Connect_To_Lobby_ComboBox_Connect->currentText());
}

void Form::Create_Lobby()
{
    Lobby_Label_Title = new GameLabel(0,
                                        0,
                                        this->width(),
                                        45,
                                        "",
                                        Qt::AlignCenter,
                                        ":/font_simple.ttf",
                                        Qt::white,
                                        this);

    int top = 150;
    Lobby_Label_Clients_Title = new GameLabel(20,
                                              top-40,
                                              this->width()/5,
                                              20,
                                              "Player:",
                                              Qt::AlignLeft,
                                              ":/font_simple.ttf",
                                              Qt::white,
                                              this);
    int top_step = 25;
    for(int i=0; i<CLIENT_COUNT; i++, top += top_step)
    {
        Lobby_Label_Client_Name[i] = new GameLabel(20,
                                            top,
                                            this->width()/5,
                                            20,
                                            "",
                                            Qt::AlignCenter,
                                            ":/font_simple.ttf",
                                            Qt::white,
                                            this);
    }

    top = 150;
    Lobby_Label_Type_Title = new GameLabel(this->width()/2 + 20,
                                              top-40,
                                              this->width()/2 - 20,
                                              20,
                                              "Player type:",
                                              Qt::AlignLeft,
                                              ":/font_simple.ttf",
                                              Qt::white,
                                              this);

    for(int i=0; i<CLIENT_COUNT; i++, top += top_step)
    {
        Lobby_Label_Client_Player_Type[i] = new GameLabel(this->width()/2 + 20,
                                                            top,
                                                            this->width()/2 - 20,
                                                            20,
                                                            "",
                                                            Qt::AlignCenter,
                                                            ":/font_simple.ttf",
                                                            Qt::white,
                                                            this);
    }
}

void Form::Lobby_Set_Inform(QString Name, QString Client_Names, QString Player_1, QString Player_2, QString Player_3)
{
    Lobby_Label_Title->set_Text(Name);

    {
        QStringList Client_Names_List = Client_Names.split("@");
        for(int i=0; i<Client_Names_List.size(); i++)
        {
            if(Lobby_Label_Client_Name[i])
            {
                Lobby_Label_Client_Name[i]->set_Text(Client_Names_List[i]);
                if(Client_Names_List[i] == this->My_Name)
                {
                    Lobby_Label_Client_Name[i]->setColor(Qt::red);
                }
            }
        }
    }

    Lobby_Label_Client_Player_Type[0]->set_Text(Player_1);
    Lobby_Label_Client_Player_Type[1]->set_Text(Player_2);
    Lobby_Label_Client_Player_Type[2]->set_Text(Player_3);
}

void Form::Draw_Lobby(QPainter &painter)
{
    Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);
    Lobby_Label_Title->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT, painter);
    Lobby_Label_Clients_Title->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT, painter);
    for(int i=0; i < CLIENT_COUNT; i++)
    {
        Lobby_Label_Client_Name[i]->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT, painter);
    }
    Lobby_Label_Type_Title->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT, painter);
    for(int i=0; i < 3; i++)
    {
        Lobby_Label_Client_Player_Type[i]->Draw(LABEL_FLAG_DRAW_BOUNDING_NOT, painter);
    }
}

void Form::Make_Some_Testing()
{

}


void Form::Draw_Testing(QPainter &painter)
{

}

void Form::Create_Testing()
{

}

void Form::MessageF(QString Text)
{
    QFile file("E:\\out2.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << Text << '\n';
    file.close();
}


void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    Make_Visible();

    switch(GameStage)
    {
        case GS_Find_Server:
        {
            Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);

            Find_Server_Loader->Draw(painter);

            break;
        }
        case GS_ProgramStart:
        {
            Draw_Menu_BackGround(imgMenu, painter, 0);
            //Draw Title
            {
                QFont OldFont = painter.font();
                painter.setFont(Font_Prog_Start->Font);

                painter.setPen(Qt::white);
                QFont f(Font_Prog_Start->Font);
                f.setPointSize(FONT_PS_MAX_SIZE);
                QFontMetrics fm(f);
                int width = fm.width(FONT_PS_TEXT);
                QRectF RTarget(this->width()/2 - width/2,
                               this->height()/2 - 30,width,600);
                painter.drawText(RTarget,Qt::AlignCenter,  FONT_PS_TEXT);
                painter.setFont(OldFont);
            }

        //
        break;
        }
        case GS_Menu:
        {
            Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);
            Draw_Menu_Button(Menu_Button_New, painter);
            Draw_Menu_Button(Menu_Button_Exit, painter);

            QFont Font = painter.font();
            QPen Pen(QColor::fromRgb(205, 0, 0, 255));

            Font.setPointSize(100);

            painter.setFont(Font);
            painter.setPen(Pen);

            painter.drawText(QRectF(this->width() / 2, 0, this->width()/2, this->height()),
                             Qt::AlignCenter | Qt::TextWordWrap, GAME_NAME);
        //
        break;
        }
        case GS_New_Game:
        {
            Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);
            Draw_Menu_Button(New_Game_Button_Back, painter);
            Draw_Menu_Button(New_Game_Button_NewLobby, painter);
            Draw_Menu_Button(New_Game_Button_ConnectToLobby, painter);
            break;
        }
        case GS_New_Lobby:
        {
            Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);
            Draw_Label(New_Lobby_Label_Create,
                       LABEL_FLAG_DRAW_BOUNDING_NOT,
                       painter);
            Draw_Menu_Button(New_Lobby_Button_Create, painter);
            Draw_Menu_Button(New_Lobby_Button_Back, painter);

            break;
        }
        case GS_Connect_To_Lobby:
        {
            Draw_Menu_BackGround(imgMenu, painter, BACKGROUND_OPACITY);
            Draw_Menu_Button(Connect_To_Lobby_Button_Connect, painter);
            Draw_Menu_Button(Connect_To_Lobby_Button_Back, painter);
            Draw_Label(Connect_To_Lobby_Label_Connect,LABEL_FLAG_DRAW_BOUNDING_NOT, painter);

        break;
        }
        case GS_Lobby:
        {
            Draw_Lobby(painter);
            break;
        }

        case GS_Game:
        {
            if(Game_Canvas)
            {
                Game_Canvas->Draw(painter);
            }
            break;
        }

        case GS_Testing:
        {
            Draw_Testing(painter);
            break;
        }
    }
}

void Form::keyPressEvent(QKeyEvent *event)
{
    switch(GameStage)
    {
        case GS_ProgramStart:
        {
           switch(event->key())
           {
               case Qt::Key_Return:
               {
                   GameStage = GS_Menu;
                   break;
               }

               case Qt::Key_Escape:
               {
                   GameStage = GS_Exit;
                   break;
               }

               default:
                   QDialog::keyPressEvent(event);
               break;
           }
        break;
        }

        case GS_Menu:
        {
            switch(event->key())
            {

                case Qt::Key_Escape:
                {
                    GameStage = GS_Exit;
                    break;
                }

                default:
                    QDialog::keyPressEvent(event);
                break;
            }
        break;
        }
        case GS_New_Lobby:
        {

            break;
        }

        case GS_Game:
        {
            switch(event->key())
            {
                case GK_Up:
                {
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Up));
                    break;
                }
                case GK_Down:
                {
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Down));
                    break;
                }
                case GK_Left:
                {
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Left));
                    break;
                }
                case GK_Right:
                {
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Right));
                    break;
                }
                case GK_Pause:
                {
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Pause));
                    break;
                }
                case GK_Fire:
                {
                    //Message("asd");
                    Msg_Format->Send_Message(TM_KEY_PRESSED, QString::number(GGK_Fire));
                    break;
                }
            }
            break;
        }


        case GS_Testing:
        {
            if(event->key() == Qt::Key_Escape)
                Make_Some_Testing();

            break;
        }

    }
    this->update();
}

void Form::mousePressEvent(QMouseEvent *event)
{
    switch(GameStage)
    {
        case GS_ProgramStart:
        {
            break;
        }
        case GS_Menu:
        {
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), Menu_Button_New))
            {
                GameStage = GS_New_Game;
            }
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), Menu_Button_Exit))
            {
                GameStage = GS_Exit;
            }
            break;
        }
        case GS_New_Game:
        {
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), New_Game_Button_Back))
            {
                GameStage = GS_Menu;
            }
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), New_Game_Button_NewLobby))
            {
                GameStage = GS_New_Lobby;
            }
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), New_Game_Button_ConnectToLobby))
            {
                ACreate_Connect_To_Lobby();
            }
            break;
        }
        case GS_New_Lobby:
        {
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), New_Lobby_Button_Create))
            {
                ACreate_New_Lobby();
            }
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), New_Lobby_Button_Back))
            {
                GameStage = GS_New_Game;
            }


        break;
        }
        case GS_Connect_To_Lobby:
        {
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), Connect_To_Lobby_Button_Connect))
            {
                BCreate_Connect_To_Lobby();
            }
            if(Menu_Button_Mouse_Pressed(event->x(), event->y(), Connect_To_Lobby_Button_Back))
            {
                GameStage = GS_New_Game;
            }
            break;
        }
    }
    this->update();
}

void Form::mouseReleaseEvent(QMouseEvent *event)
{
    switch(GameStage)
    {
        case GS_ProgramStart:
        {

            break;
        }
        case GS_Menu:
        {
            Menu_Button_Mouse_Release(Menu_Button_New);
            Menu_Button_Mouse_Release(Menu_Button_Exit);
            break;
        }
        case GS_New_Game:
        {
            Menu_Button_Mouse_Release(New_Game_Button_Back);
            Menu_Button_Mouse_Release(New_Game_Button_NewLobby);
            Menu_Button_Mouse_Release(New_Game_Button_ConnectToLobby);
            break;
        }
        case GS_New_Lobby:
        {
            Menu_Button_Mouse_Release(New_Lobby_Button_Back);
            Menu_Button_Mouse_Release(New_Lobby_Button_Create);
            break;
        }
        case GS_Connect_To_Lobby:
        {
            Menu_Button_Mouse_Release(Connect_To_Lobby_Button_Connect);
            Menu_Button_Mouse_Release(Connect_To_Lobby_Button_Back);
            break;
        }
    }
    this->update();
}

void Form::my_close()
{

}


void Form::time_out()
{

    switch(GameStage)
    {
        case GS_ProgramStart:
        {
            Font_PS_Time++;
            double c = 0.1*FONT_PS_MAX_SIZE;
            double B = (FONT_PS_MAX_SIZE/2.0 - c);
            double A = (FONT_PS_MAX_SIZE/2.0 + c);
            Font_Prog_Start->SetSize(A + sin(Font_PS_Time/7.0)*B);
            break;
        }
        case GS_Game:
        {
            Game_Canvas->Process();
            break;
        }
        case GS_Exit:
        {
            close();
        }
    }
    this->update();
}

void Form::MessageCatching(QString Text)
{
       // MessageF("All message = " + Text);
        QStringList Buf_Text = Text.split("}");
        for(int i = 0; i < Buf_Text.size()-1; i++)
        {

        QStringList list = Buf_Text[i].split("!");
        int Theme = list[0].toInt();
        QString Data = list[1];

        MessageF("Theme: " + QString::number(Theme) + " Data: " + Data);

        switch(Theme)
        {
            case TM_ANSWER_CREATE_NEW_LOBBY_NAME:
            {
                if(Data == QString::number(TM_ADMIN))
                {
                    ADMIN = true;
                    Msg_Format->Send_Message(TM_CREATE_NEW_LOBBY_PL1, New_Lobby_Combobox_Player_1->currentText());
                }
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_lobby_name");
                }

                break;
            }
            case TM_ANSWER_CREATE_NEW_LOBBY_PL1:
            {
                if(Data == QString::number(TM_SUCCESES))
                {
                    Msg_Format->Send_Message(TM_CREATE_NEW_LOBBY_PL2, New_Lobby_Combobox_Player_2->currentText());
                }
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_PL1");
                }
                break;
            }
            case TM_ANSWER_CREATE_NEW_LOBBY_PL2:
            {
                if(Data == QString::number(TM_SUCCESES))
                {
                    Msg_Format->Send_Message(TM_CREATE_NEW_LOBBY_PL3, New_Lobby_Combobox_Player_3->currentText());
                }
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_PL2");
                }
                break;
            }
            case TM_ANSWER_CREATE_NEW_LOBBY_PL3:
            {
                if(Data == QString::number(TM_SUCCESES))
                {
                    Message("Succeses!!!");
                   // GameStage = GS_Lobby;
                    if(ADMIN)
                        Now_Lobby_Name = Now_Lobby_Name + ";" + QString::number(TM_ADMIN);
                    Msg_Format->Send_Message(TM_CONNECT_TO_LOBBY, Now_Lobby_Name);
                }
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_PL3");
                }
                break;
            }
            case TM_ANSWER_LOBBY_LIST:
            {
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_lobby_list");
                }
                else
                {
                    if(Data != "")
                    {
                        Connect_To_Lobby_List = Data.split("*");
                        Connect_To_Lobby_Refresh();
                        GameStage = GS_Connect_To_Lobby;
                    }
                    else
                    {
                        Message("Lobby list is empty");
                    }
                }
                break;
            }
            case TM_ANSWER_CONNECT_TO_LOBBY:
            {
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_connect_to_lobby");
                }
                else
                {

                    Msg_Format->Send_Message(TM_LOBBY_INFORM, Data);
                }
                break;
            }
            case TM_ANSWER_LOBBY_INFORM:
            {

                QStringList Data_Buff = Data.split(",");
                QString Lobby_Title = Data_Buff[0];
                QString Lobby_Client_Names = Data_Buff[1];

                QString Lobby_Player_1 = Data_Buff[2];
                QString Lobby_Player_2 = Data_Buff[3];
                QString Lobby_Player_3 = Data_Buff[4];

                Lobby_Set_Inform(Lobby_Title,
                                 Lobby_Client_Names,
                                 Lobby_Player_1,
                                 Lobby_Player_2,
                                 Lobby_Player_3);

                GameStage = GS_Lobby;
                break;
            }
            case TM_ANSWER_MY_NAME:
            {
                if(Data == QString::number(TM_ERROR))
                {
                    Message("Error_name");
                }
                else
                {
                    My_Name = Data;
                }
                break;
            }
            case TM_ANSWER_START_GAME:
            {
                TGame_Canvas *game_canvas = new TGame_Canvas(0,0,this->width(), this->height());
                TGamePoint *game_point = new TGamePoint;
                GamePoint = game_point;
                game_canvas->set_GamePoint(GamePoint);
                Game_Canvas = game_canvas;
                GameStage = GS_Game;
                //Message("asdf");
                break;
            }

            case TM_ANSWER_TIMER_START:
            {
                *GamePoint = GP_Timer_Start;
                Game_Canvas->set_TS_Count(Data.toInt());
                break;
            }

            case TM_ANSWER_START:
            {
                *GamePoint = GP_Game;
                break;
            }

            case TM_ANSWER_PLAYER_CONFIG:
            {
                QStringList DataList = Data.split("*");

                vector<DragonPos> v_dragon_pos;

                int Count = DataList[0].toInt();

                for(int i = 0; i < Count; i++)
                {
                    QStringList Player = DataList[i+1].split("#");

                    DragonPos dragon;

                    dragon.Name = Player[0];
                    dragon.X = Player[1].toInt();
                    dragon.Y = Player[2].toInt();
                    dragon.Width = Player[3].toInt();
                    dragon.Height = Player[4].toInt();
                    dragon.Side = Player[5].toInt();

                    //MessageF("X = " + Player[1] + " Y = " + Player[2] + " Side = " + Player[5]);

                    if(dragon.Name == this->My_Name)
                        dragon.Type = 2;
                    else
                        dragon.Type = 1;

                    v_dragon_pos.push_back(dragon);
                }
                Game_Canvas->AddDragon(v_dragon_pos);
                break;
            }

            case TM_ANSWER_ENEMY_POS:
            case TM_ANSWER_ENEMY_START_POS:
            {
                QStringList DataList = Data.split("*");

                int Count = DataList[0].toInt();
                vector<EnemyPos> v_enemy_pos;

                for(int i = 0; i < Count; i++)
                {
                    QStringList Enemy = DataList[i+1].split("#");
                    EnemyPos enemy_pos;
                    enemy_pos.X = Enemy[0].toInt();
                    enemy_pos.Y = Enemy[1].toInt();
                    enemy_pos.Width = Enemy[2].toInt();
                    enemy_pos.Height = Enemy[3].toInt();
                    enemy_pos.Type = Enemy[4].toInt();

                    if(Theme == TM_ANSWER_ENEMY_START_POS)
                        Game_Canvas->Add_Explo_Pos(enemy_pos.Type, enemy_pos.X, enemy_pos.Y);

                    v_enemy_pos.push_back(enemy_pos);
                }


                Game_Canvas->set_Enemy_Pos(v_enemy_pos);
                break;
            }

            case TM_ANSWER_BULLET_POS:
            {
                QStringList DataList = Data.split("*");

                int Count = DataList[0].toInt();
                vector<BulletPos> v_bullet_pos;

                for(int i = 0; i < Count; i++)
                {
                    QStringList bullet = DataList[i+1].split("#");
                    BulletPos bullet_pos;
                    bullet_pos.X = bullet[0].toInt();
                    bullet_pos.Y = bullet[1].toInt();
                    bullet_pos.Width = bullet[2].toInt();
                    bullet_pos.Height = bullet[3].toInt();
                    bullet_pos.Type = bullet[4].toInt();

                    v_bullet_pos.push_back(bullet_pos);
                }

                Game_Canvas->set_Bullet_Pos(v_bullet_pos);
                break;
            }

            case TM_ANSWER_EXPL_POS:
            {

                QStringList DataList = Data.split("*");

               // MessageF("Eplosion:  X = " + DataList[0] + " Y = " + DataList[1]);

                int X = DataList[0].toInt();
                int Y = DataList[1].toInt();

                Game_Canvas->Add_Explo_Pos(0, X, Y);
                break;
            }

            case TM_ANSWER_DRAGON_INF:
            {
                QStringList DataList = Data.split("*");

                int Life = DataList[0].toInt();
                int Points = DataList[1].toInt();

                TDragonInf di;
                di.Life = Life;
                di.Points = Points;

                Game_Canvas->set_Inform(di);

                break;
            }

            case TM_ANSWER_PAUSE_ON:
            {
                Game_Canvas->set_Pause(true);

                break;
            }

            case TM_ANSWER_PAUSE_OFF:
            {
                Game_Canvas->set_Pause(false);

                break;
            }

            case TM_ANSWER_WIN:
            {
                Game_Canvas->Win();

                break;
            }

        }
    }
}

void Form::Disconnected()
{
    GameStage = GS_Exit;
}

void Form::Find_Server_Read_Message(QString Message, QHostAddress adress)
{
    if(Message == CLIENT_PASSWORD)
    {
        Find_Server_Host_Server = adress;
        Find_Server_Timer->stop();
        Find_Server_if_Find = true;

        //Connect to server
        client->ConnectToServer(Find_Server_Host_Server.toString(), SERVER_PORT);
        Msg_Format->Send_Message(TM_MY_NAME, My_Name);

        GameStage = GS_ProgramStart;
    }
}

void Form::Find_Server_Timer_Out()
{
    switch(GameStage)
    {
        case GS_Find_Server:
        {
            Finder->Send_Request(SERVER_PASSWORD);
            break;
        }
    }
}

void Form::New_Lobby_Edit_Text_Change(QString Text)
{
    New_Lobby_Button_Create->setEnabled(Text != "");
}




