#ifndef PROPERTIS_H
#define PROPERTIS_H

#include <vector>
#include <QString>

const int CLIENT_SCREEN_WIDTH = 1366;
const int CLIENT_SCREEN_HEIGHT = 768;

const int PORT = 1234;
const quint16 CLIENT_PORT = 1235;
const QString SERVER_PASSWORD = "1111";
const QString CLIENT_PASSWORD = "9999";


const int DRAGON_WIDTH = 100;
const int DRAGON_HEIGHT = 100;
const int DRAGON_LIFE = 100;

const int ENEMY_WIDTH = 100;
const int ENEMY_HEIGHT = 100;
const int ENEMY_SPEED_X = 1;
const int ENEMY_SPEED_Y = 1;


///////////translation conversation CODE////////////////
////CRT = ConveRsaTion
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

struct TClient_Message
{
    int ID;
    int Theme;
    QString Data;
};

struct TTheme_Data
{
    int ID = -1;
    int Theme = -1;
    QString Data = "";
};

struct TPoint
{
    int X;
    int Y;
};

struct TBlockInf
{
    TPoint Pos;
    int Type;
    TPoint Size;
    TPoint Rect;
    TPoint Speed;
};

//side to move dragon
const int SM_Left = 1;
const int SM_Up = 2;
const int SM_Right = 3;
const int SM_Down = 4;

struct TLevelInf
{
    std::vector<TBlockInf> Inf;
};

enum TGameStage {GS_None, GS_Timer_To_Start, GS_Player_Config, GS_Start, GS_Pause, GS_Win};

enum TClientStage {CS_None, CS_Timer_To_Start};
enum TPlayerType {PT_Bot, PT_Player, PT_None};

enum TBulletType {BT_Dragon, BT_Enemy};

//Enemy move type
const int EMT_Down = 1;
const int EMT_Aside = 2;
const int EMT_Down_And_Aside = 3;
const int EMT_Sin = 4;
const int EMT_ACos = 5;
const int EMT_CosB = 6;
const int EMT_M_Sin = 7;
const int EMT_M_ACos = 8;
const int EMT_M_CosB = 9;
const int EMT_BOSS_1 = 10;
const int EMT_BOSS_2 = 11;
const int EMT_BOSS_3 = 12;

//General Game Key
const int GGK_Up = 1;
const int GGK_Down = 2;
const int GGK_Left = 3;
const int GGK_Right = 4;
const int GGK_Pause = 5;
const int GGK_Fire = 6;

#endif // PROPERTIS_H
