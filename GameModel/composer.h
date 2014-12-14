#ifndef COMPOSER_H
#define COMPOSER_H

#include <QString>

class Composer
{
public:
    Composer(char spliter);
    void Add(QString Text);
    void Add(int Text);
    QString get_Composite() { return Comp;}
private:
    QString Comp;
    char Spliter;
};

#endif // COMPOSER_H
