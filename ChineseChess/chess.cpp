#include "chess.h"

static int side = 80;
static int r = side / 3;

Chess::Chess(QWidget *parent) : QWidget(parent)
{
    //添加外部字体
    QFontDatabase::addApplicationFont(":/LCALLIG.TTF");
    int id = QFontDatabase::addApplicationFont(":/LCALLIG.TTF");
    qDebug() << "family" << QFontDatabase::applicationFontFamilies(id);

    preclicked = -1; //尚未点击棋子
    redGo = true;    //红棋先走棋
    for (int i = 0; i < 32; i++)
    {
        s[i].Initialize(i); //初始化棋子
    }
}

//将行列数转换成坐标
QPoint Chess::center(int row_, int column_)
{
    int newx = origin.x() + side * column_;
    int newy = origin.y() + side * row_;
    return QPoint(newx, newy);
}

void Chess::paintEvent(QPaintEvent *)
{
    //设置画笔及宽度
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);

    //外框
    painter.drawRect(QRect(origin.x() - 5, origin.y() - 5, side * 8 + 10, side * 9 + 10));

    //内框
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(QColor(239, 235, 231)); //内框填充色
    painter.drawRect(QRect(origin.x(), origin.y(), side * 8, side * 9));

    //绘制行
    for (int i = 1; i < 9; i++)
    {
        painter.drawLine(center(i, 0), center(i, 8));
    }

    // 绘制列
    for (int i = 1; i < 8; i++)
    {
        painter.drawLine(center(0, i), center(4, i));
        painter.drawLine(center(5, i), center(9, i));
    }

    // 九宫
    painter.drawLine(center(0, 3), center(2, 5));
    painter.drawLine(center(2, 3), center(0, 5));
    painter.drawLine(center(7, 3), center(9, 5));
    painter.drawLine(center(9, 3), center(7, 5));

    //楚河汉界
    painter.setPen(QColor(166, 166, 166));
    painter.setFont(QFont("STLiti", 30));
    painter.drawText(QRect(center(4, 1), center(5, 3)), QStringLiteral("楚河"), QTextOption(Qt::AlignCenter));
    painter.drawText(QRect(center(4, 5), center(5, 7)), QStringLiteral("汉界"), QTextOption(Qt::AlignCenter));

    // 炮、兵处的直角
    painter.setPen(QColor(127, 127, 127));
    RightAngle(painter, center(2, 1), 1);
    RightAngle(painter, center(2, 7), 1);
    RightAngle(painter, center(7, 1), 1);
    RightAngle(painter, center(7, 7), 1);
    RightAngle(painter, center(3, 2), 1);
    RightAngle(painter, center(3, 4), 1);
    RightAngle(painter, center(3, 6), 1);
    RightAngle(painter, center(6, 2), 1);
    RightAngle(painter, center(6, 4), 1);
    RightAngle(painter, center(6, 6), 1);
    RightAngle(painter, center(3, 0), 2);
    RightAngle(painter, center(6, 0), 2);
    RightAngle(painter, center(3, 8), 0);
    RightAngle(painter, center(6, 8), 0);

    // 绘制棋子
    for (int i = 0; i < 32; i++)
    {
        drawStone(painter, i);
    }
}

//绘制直角
void Chess::RightAngle(QPainter &pr, QPoint p, int i)
{
    int x = p.x();
    int y = p.y();
    int r = side / 25;
    if (i != 0)
    {
        pr.drawLine(x + r, y - 3 * r, x + r, y - r);
        pr.drawLine(x + r, y + r, x + r, y + 3 * r);
        pr.drawLine(x + r, y - r, x + 3 * r, y - r);
        pr.drawLine(x + r, y + r, x + 3 * r, y + r);
    }
    if (i != 2)
    {
        pr.drawLine(x - 3 * r, y - r, x - r, y - r);
        pr.drawLine(x - 3 * r, y + r, x - r, y + r);
        pr.drawLine(x - r, y - 3 * r, x - r, y - r);
        pr.drawLine(x - r, y + r, x - r, y + 3 * r);
    }
}

//绘制棋子
void Chess::drawStone(QPainter &pr, int j)
{
    //棋子被吃不用绘制
    if (s[j].dead)
        return;

    pr.setPen(QPen(Qt::black, 2.5));
    //棋子被选中变色
    if (j != preclicked)
    {
        pr.setBrush(QColor(247, 244, 234));
    }
    else
    {
        pr.setBrush(QColor(256, 256, 256));
    }

    pr.setRenderHint(QPainter::Antialiasing, true);   //去锯齿
    pr.drawEllipse(center(s[j].row, s[j].col), r, r); //圆形轮廓

    pr.setFont(QFont("KaiTi", 22, QFont::Bold));
    //红棋与黑棋的字体颜色
    if (s[j].isRed)
    {
        pr.setPen(QColor(255, 0, 0));
    }
    else
    {
        pr.setPen(QColor(0, 0, 0));
    }
    //绘制文字
    QRect rect = QRect(center(s[j].row, s[j].col).x() - r, center(s[j].row, s[j].col).y() - r, 2 * r, 2 * r);
    pr.drawText(rect, s[j].stoneName(), QTextOption(Qt::AlignCenter));
}

//找到点击位置的归属点
bool Chess ::getClicked(QPoint q, int &row, int &col)
{
    for (row = 0; row <= 9; row++)
        for (col = 0; col <= 8; col++)
        {
            QPoint c = center(row, col) - q;
            //坐标点距离点击点距离小于r/2，即可判断点击的位置中心是该坐标点
            if (pow(c.x(), 2) + pow(c.y(), 2) < pow(side / 2, 2))
                return true;
        }
    return false;
}

//判断是否可以走棋
bool Chess::canMove(int precli, int row, int col, int cli)
{
    //选到同色棋子，不可move，需要移动的棋子变成了后选中的棋子
    if (cli != -1 && s[precli].isRed == s[cli].isRed)
    {
        preclicked = cli; //换点击的棋子
        update();
        return false;
    }
    //棋子移动后，将帅不能会面
    if (!Chess::tryGo(precli, row, col, cli))
    {
        return false;
    }
    //判断是是否符合棋子的走棋规则
    switch (s[precli].type)
    {
    case Stone::RSHUAI:
    case Stone::BJIANG:
        return canMovejiang(precli, row, col);
        break;
    case Stone::RSHI:
    case Stone::BSHI:
        return canMoveshi(precli, row, col);
        break;
    case Stone::RJU:
    case Stone::BJU:
        return canMoveju(precli, row, col);
        break;
    case Stone::BMA:
    case Stone::RMA:
        return canMovema(precli, row, col);
        break;
    case Stone::BPAO:
    case Stone::RPAO:
        return canMovepao(precli, row, col, cli);
        break;
    case Stone::RXIANG:
    case Stone::BXIANG:
        return canMovexiang(precli, row, col);
        break;
    case Stone::BZU:
    case Stone::RBING:
        return canMovebing(precli, row, col);
        break;
    }
    return true;
}

//将帅走棋规则
bool Chess::canMovejiang(int precl, int row, int col)
{
    //将帅不出九宫
    if (s[precl].type == Stone::RSHUAI)
    {
        if (row < 7 || col < 3 || col > 5)
            return false;
    }
    else if (s[precl].type == Stone::BJIANG)
    {
        if (row > 2 || col < 3 || col > 5)
            return false;
    }
    //一次走一格
    int disx = abs(s[precl].row - row);
    int disy = abs(s[precl].col - col);
    if ((disx == 1 && disy == 0) || (disx == 0 && disy == 1))
        return true;

    return false;
}

//士走棋规则
bool Chess::canMoveshi(int precil, int row, int col)
{
    //士不出九宫
    if (s[precil].isRed)
    {
        if (row < 7 || col < 3 || col > 5)
            return false;
    }
    else
    {
        if (row > 2 || col < 3 || col > 5)
            return false;
    }
    //只能斜走
    int disx = abs(s[precil].row - row);
    int disy = abs(s[precil].col - col);
    if (disx == 1 && disy == 1)
        return true;

    return false;
}

//車走棋规则
bool Chess::canMoveju(int precil, int row, int col)
{
    //車只能走直线，而且不能跳子
    int disx = abs(s[precil].row - row);
    int disy = abs(s[precil].col - col);
    if ((!disx || !disy) && !StoneAtLine(row, col, s[precil].row, s[precil].col))
        return true;
    return false;
}

//象走棋规则
bool Chess::canMovexiang(int precil, int row, int col)
{
    //相走田
    int disx = abs(s[precil].row - row);
    int disy = abs(s[precil].col - col);
    if (disx != 2 || disy != 2)
        return false;
    //田字中间不能有棋子
    int midx = (s[precil].row + row) / 2;
    int midy = (s[precil].col + col) / 2;
    if (StoneOccupies(midx, midy) != -1)
        return false;
    //不能过楚河汉界
    if (s[precil].isRed)
    {
        if (row < 4)
            return false;
    }
    else
    {
        if (row > 5)
            return false;
    }
    return true;
}

//马走棋规则
bool Chess::canMovema(int precil, int row, int col)
{
    //马走田 不能蹩腿马
    int disx = abs(s[precil].row - row);
    int disy = abs(s[precil].col - col);
    if (disx == 1 && disy == 2)
    {
        if (StoneOccupies(s[precil].row, (s[precil].col + col) / 2) == -1)
            return true;
    }
    else if (disx == 2 && disy == 1)
    {
        if (StoneOccupies((s[precil].row + row) / 2, s[precil].col) == -1)
            return true;
    }
    return false;
}

//兵卒走棋规则
bool Chess::canMovebing(int precil, int row, int col)
{
    //未过楚河汉界之前，只能前进；过后，可前后左右移动；每次只能移动一格
    int disx = s[precil].row - row;
    int absdisx = abs(s[precil].row - row);
    int absdisy = abs(s[precil].col - col);
    if (s[precil].isRed && row > 4)
    {
        if (disx == 1 && absdisy == 0)
            return true;
    }
    else if (s[precil].isRed && row < 5)
    {
        if ((absdisx == 1 && absdisy == 0) || (absdisy == 1 && absdisx == 0))
            return true;
    }
    else if (!s[precil].isRed && row < 5)
    {
        if (disx == -1 && absdisy == 0)
            return true;
    }
    else if (!s[precil].isRed && row > 4)
    {
        if ((absdisx == 1 && absdisy == 0) || (absdisy == 1 && absdisx == 0))
            return true;
    }
    return false;
}

//炮走棋规则
bool Chess::canMovepao(int precil, int row, int col, int cli)
{
    //吃棋要有炮架，跳子吃棋
    if (cli != -1 && StoneAtLine(row, col, s[precil].row, s[precil].col) == 1)
        return true;
    //不吃棋可直线移动，不能跳子
    if (cli == -1 && StoneAtLine(row, col, s[precil].row, s[precil].col) == 0)
        return true;
    return false;
}

//判断位置是否有棋子，如果有，得到棋子的编号
int Chess::StoneOccupies(int row, int col)
{
    //遍历棋子
    for (int i = 0; i < 32; i++)
    {
        if (s[i].row == row && s[i].col == col && !s[i].dead)
            return i;
    }
    return -1;
}

//同行/列两点之间之间棋子的个数
int Chess::StoneAtLine(int row, int col, int prerow, int precol)
{
    int num = 0;
    //不在同一行/列
    if (row != prerow && col != precol)
        return -1;
    //两点重合，未移动
    if (row == prerow && col == precol)
        return -1;
    //同一行，两点之间按列遍历，每点判断是否有棋子
    if (row == prerow)
    {
        int min = col < precol ? col : precol;
        int max = col < precol ? precol : col;
        for (int i = min + 1; i < max; i++)
        {
            if (StoneOccupies(row, i) != -1)
                num++;
        }
    }
    //同一列，两点之间按行遍历，每点判断是否有棋子
    else
    {
        int min = row < prerow ? row : prerow;
        int max = row < prerow ? prerow : row;
        for (int i = min + 1; i < max; i++)
        {
            if (StoneOccupies(i, col) != -1)
                num++;
        }
    }
    return num;
}

//试走棋
bool Chess::tryGo(int precl, int tryrow, int trycol, int cl)
{
    int temprow = s[precl].row;
    int tempcol = s[precl].col;
    s[precl].row = tryrow;
    s[precl].col = trycol;
    if (cl > 0)
        s[cl].dead = true;
    //如果走棋后将帅会面
    bool b = true;
    if (s[4].col == s[20].col && StoneAtLine(s[4].row, s[4].col, s[20].row, s[20].col) == 0 && !s[4].dead && !s[20].dead)
    {
        s[precl].row = temprow;
        s[precl].col = tempcol;
        b = false;
    }
    s[precl].row = temprow;
    s[precl].col = tempcol;
    if (cl > 0)
        s[cl].dead = false;
    return b;
}

void Chess::mouseReleaseEvent(QMouseEvent *p)
{
    if (p->button() != Qt::LeftButton)
    {
        return;
    }
    QPoint clickedpos = p->pos(); //鼠标点击的位置
    int row = 0, col = 0;
    //点击到了棋盘外面的地方
    if (!getClicked(clickedpos, row, col))
        return;
    int clicked = StoneOccupies(row, col);
    click(clicked, row, col);
}

void Chess::click(int clicked, int row, int col)
{
    //第一次选中
    if (preclicked == -1)
    {
        //选到棋子
        if (clicked != -1)
        {
            //选择的棋子是该走棋的一方
            if (redGo == s[clicked].isRed)
            {
                //将第一次选中的位置存给preclicked
                preclicked = clicked;
                //重新绘制,使选中的棋子发生变化
                update();
            }
        }
    }
    //第二次选中
    else
    {
        //如果符合走棋规则就走棋
        if (canMove(preclicked, row, col, clicked))
        {
            //选中的这个位置有棋子，该棋子被吃
            if (clicked != -1)
            {
                s[clicked].dead = true;
            }

            //第一次点击的棋子的位置变成第二次点击的位置
            s[preclicked].row = row;
            s[preclicked].col = col;

            //换色走棋，重新进行下一轮选择
            preclicked = -1;
            redGo = !redGo;

            //判断有无获胜方
            checkvictory();
            update();
        }
    }
}

//胜负判断
void Chess::checkvictory()
{
    //红方胜利
    if (s[4].dead)
    {
        QMessageBox::information(this, QStringLiteral("棋局结束"),
                                 QStringLiteral("<p></span><p align='center'><span style='color: rgb(255, 0, 0); font-size: 28px;font-family:STXingkai; '>红方胜利</span></p>")
                                 + char(10) +
                                 QStringLiteral("<p></span><p align='center'><span style='color: rgb(0, 0, 0); font-size: 15px;font-family: Lucida Calligraphy; '>Wit beyond measure is man's greatest treasure.</span></p>"),
                                 QStringLiteral("再来一局"));
        //初始化
        preclicked = -1;
        redGo = true;
        for (int i = 0; i < 32; i++)
        {
            s[i].Initialize(i);
        }
    }
    //黑方胜利
    else if (s[20].dead)
    {
        QMessageBox::information(this, QStringLiteral("棋局结束"),
                                 QStringLiteral("<p></span><p align='center'><span style='color: rgb(0, 0, 0); font-size: 28px;font-family:STXingkai; '>黑方胜利</span></p>") + char(10) + QStringLiteral("<p></span><p align='center'><span style='color: rgb(0, 0, 0); font-size: 15px;font-family: Lucida Calligraphy; '>Wit beyond measure is man's greatest treasure.</span></p>"),
                                 QStringLiteral("再来一局"));
        //初始化
        redGo = true;
        for (int i = 0; i < 32; i++)
        {
            s[i].Initialize(i);
        }
    }
}
Chess::~Chess() {}
