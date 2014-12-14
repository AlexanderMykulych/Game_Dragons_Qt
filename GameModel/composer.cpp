#include "composer.h"

Composer::Composer(char spliter)
{
    this->Spliter = spliter;
    this->Comp = "";
}

void Composer::Add(QString Text)
{
    Comp += Text + Spliter;
}

void Composer::Add(int Text)
{
    Add(QString::number(Text));
}
