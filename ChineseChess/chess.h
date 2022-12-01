#ifndef CHESS_H
#define CHESS_H
#include "stone.h"
#include "step.h"
#include <QPen>
#include <QRect>
#include <cmath>
#include <QIcon>
#include <QPoint>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QIODevice>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPaintEvent>
#include <QApplication>
#include <QFontDatabase>

class Chess : public QWidget
{

    Q_OBJECT
public:
    QPoint origin = QPoint(80, 80); //原点
    Stone s[32];                    //棋子

    int preclicked; //首次点击的棋子
    bool redGo;     //轮到红方

    Chess(QWidget *parent = nullptr);
    ~Chess();

    QPoint center(int, int); //将行列数转换成坐标

    void paintEvent(QPaintEvent *);           //绘制棋盘等
    void RightAngle(QPainter &, QPoint, int); //绘制直角
    void drawStone(QPainter &, int);          //绘制棋子

    bool getClicked(QPoint, int &, int &); //找到点击的位置
    int StoneOccupies(int, int);           //判断位置是否有棋子，如果有，得到棋子的编号
    int StoneAtLine(int, int, int, int);   //同行/列两点之间之间棋子的个数

    void mouseReleaseEvent(QMouseEvent *); //鼠标释放
    virtual void click(int, int, int);

    bool tryGo(int, int, int, int);   //试走棋
    bool canMove(int, int, int, int); //是否可以走棋
    //不同棋子的走棋规则
    bool canMovejiang(int, int, int);
    bool canMoveshi(int, int, int);
    bool canMoveju(int, int, int);
    bool canMovema(int, int, int);
    bool canMovexiang(int, int, int);
    bool canMovebing(int, int, int);
    bool canMovepao(int, int, int, int);

    void checkvictory(); //胜负判断

signals:
public slots:
};
#endif
