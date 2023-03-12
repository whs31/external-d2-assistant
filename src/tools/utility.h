#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

class Utility
{
public:
    Utility() = default;
    static QString getHeroNameByID(int id);
private:
    static const QString heroNames[138];
};

#endif // UTILITY_H
