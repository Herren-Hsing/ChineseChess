#include "stone.h"

Stone::Stone() {}
Stone::~Stone() {}
QString Stone::stoneName()
{
    switch (this->type)
    {
    case BJIANG:
        return QStringLiteral("將");
    case BSHI:
        return QStringLiteral("士");
    case BZU:
        return QStringLiteral("卒");
    case BPAO:
        return QStringLiteral("砲");
    case BMA:
        return QStringLiteral("馬");
    case BXIANG:
        return QStringLiteral("象");
    case BJU:
        return QStringLiteral("車");
    case RSHUAI:
        return QStringLiteral("帥");
    case RSHI:
        return QStringLiteral("仕");
    case RBING:
        return QStringLiteral("兵");
    case RPAO:
        return QStringLiteral("炮");
    case RMA:
        return QStringLiteral("傌");
    case RXIANG:
        return QStringLiteral("相");
    case RJU:
        return QStringLiteral("俥");
    default:
        return "wrong";
    }
}
void Stone::Initialize(int i)
{
    struct
    {
        int row_, col_;
        Stone::Type type_;
    } pos[32] = {
    {0, 0, Stone::BJU},
    {0, 1, Stone::BMA},
    {0, 2, Stone::BXIANG},
    {0, 3, Stone::BSHI},
    {0, 4, Stone::BJIANG},
    {0, 5, Stone::BSHI},
    {0, 6, Stone::BXIANG},
    {0, 7, Stone::BMA},
    {0, 8, Stone::BJU},
    {2, 1, Stone::BPAO},
    {2, 7, Stone::BPAO},
    {3, 0, Stone::BZU},
    {3, 2, Stone::BZU},
    {3, 4, Stone::BZU},
    {3, 6, Stone::BZU},
    {3, 8, Stone::BZU},

    {9, 0, Stone::RJU},
    {9, 1, Stone::RMA},
    {9, 2, Stone::RXIANG},
    {9, 3, Stone::RSHI},
    {9, 4, Stone::RSHUAI},
    {9, 5, Stone::RSHI},
    {9, 6, Stone::RXIANG},
    {9, 7, Stone::RMA},
    {9, 8, Stone::RJU},
    {7, 1, Stone::RPAO},
    {7, 7, Stone::RPAO},
    {6, 0, Stone::RBING},
    {6, 2, Stone::RBING},
    {6, 4, Stone::RBING},
    {6, 6, Stone::RBING},
    {6, 8, Stone::RBING},
};

    dead = false;

    if (i > 15)
    {
        isRed = true;
    }
    else
        isRed = false;

    row = pos[i].row_;
    col = pos[i].col_;
    type = pos[i].type_;
}
