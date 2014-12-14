#include "messageformat.h"



void MessageFormat::Send_Message()
{
    QString Message = QString::number(Theme);
    Message += "!";

    Message += Data;
    Message += "!";

    Client->Send_Message(Message);
}

void MessageFormat::Send_Message(int theme, QString data)
{
    QString Message = QString::number(theme);
    Message += "!";

    Message += data;
    Message += "!";
    Message += "}";

    Client->Send_Message(Message);
}
