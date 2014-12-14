#ifndef PROPERTIS_H
#define PROPERTIS_H

#include <QString>
#include <QFont>


const QString GAME_NAME = "Survival: dragon";

struct TDragonInf
{
    int Life;
    int Points;
};

struct EnemyPos
{
    int X;
    int Y;
    int Width;
    int Height;
    int Type;
};

struct BulletPos
{
    int X;
    int Y;
    int Width;
    int Height;
    int Type;
};

struct DragonPos
{
    int X;
    int Y;
    int Width;
    int Height;
    int Type;
    int Side;
    QString Name;
};

//Sound dir
const QString SOUND_CLICK = "";
const QString SOUND_FIRE = "";
const QString SOUND_EXPL = "";
const QString SOUND_BACKGROUND = "";


//side to move dragon
const int SM_Left = 1;
const int SM_Up = 2;
const int SM_Right = 3;
const int SM_Down = 4;


const int CLIENT_SCREEN_WIDTH = 1366;
const int CLIENT_SCREEN_HEIGHT = 768;


const int CLIENT_COUNT = 3;
//(GSC = Game Server Client)
//Host and Port
const QString GSC_LOCAL_HOST = "127.0.0.1";
const qint64 GSC_PORT = 1234;
const int FONT_PS_MAX_SIZE = 50;
const QString FONT_PS_TEXT = "Press Enter";
const int BUTTON_WIDTH = 400;
const int BUTTON_FONT_SIZE = 20;
const int BACKGROUND_OPACITY = 170;
const int NEW_LOBBY_EDIT_WIDTH = 700;
const int NEW_LOBBY_EDIT_FONT_SIZE = 25;
const int CONNECT_TO_LOBBY_COMBOBOX_WIDTH = 700;
const int CONNECT_TO_LOBBY_COMBOBOX_FONT_SIZE = 25;


const int LABEL_FLAG_DRAW_BOUNDING = 1;
const int LABEL_FLAG_DRAW_BOUNDING_NOT = 0;

//Server client
const quint16 SERVER_PORT = 1234;
const quint16 CLIENT_PORT = 1235;
const QString SERVER_PASSWORD = "1111";
const QString CLIENT_PASSWORD = "9999";

//Find Server
const int LOADER_WIDTH = 100;
const int LOADER_HEIGHT = 100;
//Game
enum TGameStage {GS_Find_Server,
                 GS_ProgramStart,
                 GS_Menu,
                 GS_New_Game,
                 GS_New_Lobby,
                 GS_Lobby,
                 GS_Connect_To_Lobby,
                 GS_Exit,
                 GS_Testing,
                 GS_Game};

enum TGamePoint {GP_None,
                 GP_Timer_Start,
                 GP_Game,
                 GP_Win};
enum TConversationStage {CS_Create_New_Lobby};

enum TUpDown {UD_Up, UD_Down};

enum TDragon_Move{DM_Up, DM_Right, DM_Left};

///////////translation conversation CODE////////////////
////CRT = ConveRsaTion
/// TM = TheMe
const int TM_MY_NAME = 10001;
const int TM_ANSWER_MY_NAME = 20001;

const int TM_CREATE_NEW_LOBBY_NAME = 1001;
const int TM_ANSWER_CREATE_NEW_LOBBY_NAME = 2001;

const int TM_CREATE_NEW_LOBBY_PL1 = 1002;
const int TM_ANSWER_CREATE_NEW_LOBBY_PL1 = 2002;

const int TM_CREATE_NEW_LOBBY_PL2 = 1003;
const int TM_ANSWER_CREATE_NEW_LOBBY_PL2 = 2003;

const int TM_CREATE_NEW_LOBBY_PL3 = 1004;
const int TM_ANSWER_CREATE_NEW_LOBBY_PL3 = 2004;

const int TM_LOBBY_LIST = 1005;
const int TM_ANSWER_LOBBY_LIST = 2005;

const int TM_CONNECT_TO_LOBBY = 1006;
const int TM_ANSWER_CONNECT_TO_LOBBY = 2006;

const int TM_LOBBY_INFORM = 1007;
const int TM_ANSWER_LOBBY_INFORM = 2007;

const int TM_ANSWER_START_GAME = 1008;

const int TM_ANSWER_TIMER_START = 1009;

const int TM_ANSWER_PLAYER_CONFIG = 1010;

const int TM_ANSWER_START = 1011;

const int TM_KEY_PRESSED = 1012;
const int TM_ANSWER_KEY_PRESSED = 2012;

const int TM_ANSWER_ENEMY_POS = 1013;

const int TM_ANSWER_BULLET_POS = 1014;

const int TM_ANSWER_EXPL_POS = 1015;

const int TM_ANSWER_ENEMY_START_POS = 1016;

const int TM_ANSWER_DRAGON_INF = 1017;

const int TM_ANSWER_PAUSE_ON = 1018;

const int TM_ANSWER_PAUSE_OFF = 1019;

const int TM_ANSWER_WIN = 1020;

const int TM_NONE = 1999;

const int TM_SUCCESES = 1;
const int TM_ERROR = 0;
const int TM_ADMIN = 2;


//config
//Game Key
const int GK_Up = Qt::Key_Up;
const int GK_Down = Qt::Key_Down;
const int GK_Left = Qt::Key_Left;
const int GK_Right = Qt::Key_Right;
const int GK_Pause = Qt::Key_F9;
const int GK_Fire = Qt::Key_A;

//General Game Key
const int GGK_Up = 1;
const int GGK_Down = 2;
const int GGK_Left = 3;
const int GGK_Right = 4;
const int GGK_Pause = 5;
const int GGK_Fire = 6;

#endif // PROPERTIS_H
