#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H
#include "gameserver.h"
#include <QString>
#include "propertis.h"
#include "composer.h"

class MessageFormat
{
public:
    MessageFormat(GameServer *server) {Server = server;}
    inline void setTheme(int theme) {Theme = theme;}
    inline void setData(QString data) {Data = data;}
    int getTheme() {return Theme;}
    QString getData() {return Data;}
    inline void Clean() {Theme = 0; Data = "";}

    void Send_Message(int clientNum);
    void Send_Message(int clientNum, int theme, QString data);
    void Send_Message(TTheme_Data Theme_Data) {Send_Message(Theme_Data.ID, Theme_Data.Theme, Theme_Data.Data);}

private:
    GameServer *Server;
    int Theme;
    QString Data;
};

#endif // MESSAGEFORMAT_H
