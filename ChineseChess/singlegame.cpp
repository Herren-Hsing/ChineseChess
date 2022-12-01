#include "singlegame.h"

Single::Single(QWidget *parent) : Chess(parent) {}
Single::~Single() {}

void Single::click(int clickedred, int row, int col)
{
    if (!redGo)
        return;
    //红棋由人走棋，调用Chess类的click函数
    Chess::click(clickedred, row, col);
    //红棋走完轮到黑棋，由机器给出走法
    if (!redGo)
    {
        //设定一个计时器，红棋走完过0.1s黑棋再走
        QTimer::singleShot(100, this, SLOT(pcMove()));
    }
}

void Single::pcMove()
{
    //得到最佳走法
    Step *step = getBestScore();

    //移动到的地方如果有棋子则吃棋
    if (step->secondclicked != -1)
    {
        s[step->secondclicked].dead = true;
    }

    //走棋
    s[step->firstclicked].row = step->rowto;
    s[step->firstclicked].col = step->colto;
    delete step;

    checkvictory();
    redGo = !redGo;
    update();
}

//获取所有可移动范围
void Single::getAllarea(QVector<Step *> &steps)
{
    //黑棋红棋遍历棋子不同
    int min = 0, max = 16;
    if (redGo)
    {
        min = 16;
        max = 32;
    }

    for (int i = min; i < max; i++)
    {
        if (s[i].dead)
            continue;
        for (int row = 0; row <= 9; row++)
        {
            for (int col = 0; col <= 8; col++)
            {
                int clicked = StoneOccupies(row, col); //有棋子
                if (clicked != -1 && !s[clicked].isRed)
                    continue;
                if (canMove(i, row, col, clicked)) //判断能否走棋
                {
                    saveSteps(i, clicked, row, col, steps); //存棋
                }
                else
                    continue;
            }
        }
    }
}

//试走棋
void Single::fakemove(Step *step)
{
    s[step->firstclicked].row = step->rowto;
    s[step->firstclicked].col = step->colto;
    if (step->secondclicked > 0)
        s[step->secondclicked].dead = true;
    redGo = !redGo;
}

//退回试走棋
void Single::backfakemove(Step *step)
{
    s[step->firstclicked].row = step->rowfrom;
    s[step->firstclicked].col = step->colfrom;
    if (step->secondclicked > 0)
        s[step->secondclicked].dead = false;
    redGo = !redGo;
}

//保存走棋方法
void Single::saveSteps(int preclicked, int clicked, int row, int col, QVector<Step *> &steps)
{
    Step *step = new Step;
    step->colfrom = s[preclicked].col;
    step->colto = col;
    step->rowfrom = s[preclicked].row;
    step->rowto = row;
    step->firstclicked = preclicked;
    step->secondclicked = clicked;
    steps.append(step);
}

//得到最佳走法
Step *Single::getBestScore()
{
    QVector<Step *> steps;
    getAllarea(steps);

    int maxScore = -10000;

    Step *ret = nullptr;
    //遍历所有可能走法
    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        int score = getMinScore(aheadStep - 1, maxScore);
        backfakemove(step);

        if (score > maxScore)
        {
            maxScore = score;
            if (ret)
                delete ret;
            ret = step;
        }
        else
        {
            delete step;
        }
    }
    return ret;
}

//对方棋子得分最小
int Single::getMinScore(int a, int maxs)
{
    if (a == 0)
    {
        return finalScore();
    }

    QVector<Step *> steps;
    getAllarea(steps);

    double minScore = 10000;

    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        int score = getMaxScore(a - 1, minScore);
        backfakemove(step);
        delete step;

        //剪枝
        if (score <= maxs)
        {
            while (steps.count())
            {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if (score < minScore)
        {
            minScore = score;
        }
    }
    return minScore;
}

//己方棋子得分最高
int Single::getMaxScore(int a, int mins)
{
    if (a == 0)
    {
        return finalScore();
    }

    QVector<Step *> steps;
    getAllarea(steps);

    double maxScore = -10000;

    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        double score = getMinScore(a - 1, maxScore);
        backfakemove(step);
        delete step;

        //剪枝
        if (score >= mins)
        {
            while (steps.count())
            {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if (score > maxScore)
        {
            maxScore = score;
        }
    }
    return maxScore;
}

//计算得分
int Single::finalScore()
{

    int redSum = 0;
    int blackSum = 0;

    //将士卒炮马相車
    static int chessScore[] = {10000, 2, 1, 5, 5, 2, 10, 10000, 2, 1, 5, 5, 2, 10};

    for (int i = 0; i < 16; i++)
    {
        if (s[i].dead)
            continue;
        blackSum += chessScore[s[i].type];
    }

    for (int i = 16; i < 32; i++)
    {
        if (s[i].dead)
            continue;
        redSum += chessScore[s[i].type];
    }

    return blackSum - redSum;
}
