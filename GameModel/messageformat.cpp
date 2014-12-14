#include "messageformat.h"



void MessageFormat::Send_Message(int clientNum)
{
    QString Message = QString::number(Theme);
    Message += "!";

    Message += Data;
    Message += "!";

    Server->SendMessage(clientNum, Message);
}

void MessageFormat::Send_Message(int clientNum, int theme, QString data)
{
    Composer Message('!');
    Message.Add(QString::number(theme));
    Message.Add(data);
    QString Msg_Text = Message.get_Composite() + "}";

    Server->SendMessage(clientNum, Msg_Text);
}
