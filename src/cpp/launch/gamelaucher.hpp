
#ifndef GAMELAUCHER_H
#define GAMELAUCHER_H


#include <QObject>


class GameLaucher : public QObject
{
    Q_OBJECT
public:
    explicit GameLaucher(QObject *parent = nullptr);

signals:

};

#endif // GAMELAUCHER_H
