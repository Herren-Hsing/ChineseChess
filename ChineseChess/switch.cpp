#include "switch.h"

Switch::Switch(int gType, QWidget *parent) : QWidget(parent)
{
    gameType = gType;

    //双人对弈模式
    if (gameType == 0)
    {
        Chess *game = new Chess;
        QHBoxLayout *g = new QHBoxLayout(this);
        g->addWidget(game);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("D:/QT/try/ChineseChess/Guiji.mp3"));
        player->setVolume(10);
        player->play();
    }

    //人机对弈模式
    else if (gameType == 1)
    {
        Single *game = new Single;
        QHBoxLayout *g = new QHBoxLayout(this);
        g->addWidget(game);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("D:/QT/try/ChineseChess/Geqian.mp3"));
        player->setVolume(10);
        player->play();
    }
}
Switch::~Switch() {}
