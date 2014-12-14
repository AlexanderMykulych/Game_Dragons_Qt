#ifndef MYSTRINGLIST_H
#define MYSTRINGLIST_H

#include <QStringList>
#include <vector>
#include <QString>

//using namespace std;

class MyStringList
{
public:
    MyStringList();
    void push(bool ifLock, QString List_Item);
    void pop();
    QStringList List;
    std::vector<bool> Lock;

};

#endif // MYSTRINGLIST_H
