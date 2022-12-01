#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:

    int row;
    int col;
    bool dead;
    bool isRed;

    enum Type
    {
        BJIANG,
        BSHI,
        BZU,
        BPAO,
        BMA,
        BXIANG,
        BJU,
        RSHUAI,
        RSHI,
        RBING,
        RPAO,
        RMA,
        RXIANG,
        RJU
    };
    enum Type type;

    Stone();
    ~Stone();
    QString stoneName();
    void Initialize(int);
};
#endif
