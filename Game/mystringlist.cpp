#include "mystringlist.h"

MyStringList::MyStringList()
{
}

void MyStringList::push(bool ifLock, QString List_Item)
{
    Lock.push_back(ifLock);
    List += List_Item;
}

void MyStringList::pop()
{
    Lock.pop_back();
    List.pop_back();
}
