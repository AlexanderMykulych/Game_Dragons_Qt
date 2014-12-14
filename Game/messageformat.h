#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H
#include "gameclient.h"
#include <QString>

class MessageFormat
{
public:
    MessageFormat(GameClient *client) {Client = client;}
    inline void setTheme(int theme) {Theme = theme;}
    inline void setData(QString data) {Data = data;}
    int getTheme() {return Theme;}
    QString getData() {return Data;}
    inline void Clean() {Theme = 0; Data = "";}

    void Send_Message();
    void Send_Message(int theme, QString data);

private:
    GameClient *Client;
    int Theme;
    QString Data;
};

#endif // MESSAGEFORMAT_H
