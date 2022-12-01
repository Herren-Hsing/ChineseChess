#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "chess.h"
#include "step.h"
#include <QTimer>

class Single : public Chess
{
    Q_OBJECT
public:
    int aheadStep = 2;

    Single(QWidget *parent = nullptr);
    ~Single();

    virtual void click(int, int, int);
    void getAllarea(QVector<Step *> &steps);               //获取可移动范围
    void saveSteps(int, int, int, int, QVector<Step *> &); //存棋

    void fakemove(Step *);
    void backfakemove(Step *);

    Step *getBestScore();
    int getMinScore(int, int);
    int getMaxScore(int, int);
    int finalScore();

signals:
public slots:
    void pcMove();
};
#endif
