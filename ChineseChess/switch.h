#ifndef SWITCH_H
#define SWITCH_H
#include "chess.h"
#include "singlegame.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QMediaPlayer>

class Switch : public QWidget
{
    Q_OBJECT
public:
    int gameType;

    Switch(int, QWidget *parent = nullptr);
    ~Switch();

signals:
public slots:
};
#endif
