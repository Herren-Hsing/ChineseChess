#include "start.h"

Start::Start(QWidget *parent) : QDialog(parent)
{
    //窗体大小、logo、标题
    this->setWindowIcon(QIcon(":/logo.png"));
    setWindowTitle("The winner of the game is the player who makes the next-to-last mistake.");
    setFixedSize(750, 550);

    //开始界面图片美化
    QLabel *label1, *label2, *label3;
    QPixmap picture1, picture2, picture3;

    picture1.load(":/logo.png");
    label1 = new QLabel(this);
    label1->setPixmap(picture1);
    label1->setScaledContents(true); //自适应大小
    label1->resize(120, 120);
    label1->move(100, 50);

    picture2.load(":/pic1.png");
    label2 = new QLabel(this);
    label2->setPixmap(picture2);
    label2->setScaledContents(true);
    label2->resize(600, 100);
    label2->move(200, 55);

    picture3.load(":/SHIELD.png");
    label3 = new QLabel(this);
    label3->setPixmap(picture3);
    label3->setScaledContents(true);
    label3->resize(100, 100);
    label3->move(335, 280);

    //模式选择按钮
    QPushButton *b1 = new QPushButton(QStringLiteral("双人对弈"), this);
    b1->setFont(QFont("STKaiti", 16));
    b1->setCursor(QCursor(Qt::BusyCursor));
    b1->setFlat(true);
    b1->move(120, 310);
    b1->setFixedSize(150, 50);
    modes[0] = b1;
    QPushButton *b2 = new QPushButton(QStringLiteral("人机对弈"), this);
    b2->setFont(QFont("STKaiti", 16));
    b2->setCursor(QCursor(Qt::BusyCursor));
    b2->setFlat(true);
    b2->move(490, 310);
    b2->setFixedSize(150, 50);
    modes[1] = b2;

    connect(b1, SIGNAL(clicked()), this, SLOT(slotClicked()));
    connect(b2, SIGNAL(clicked()), this, SLOT(slotClicked()));
}
void Start::slotClicked()
{
    //当QPushButton发出一个信号时就记录发出这个信号的对象，sender获取发出信号的对象
    QPushButton *s = qobject_cast<QPushButton *>(sender());

    if (modes[0] == s)
    {
        this->chosen = 0;
        accept();
        return;
    }
    else
    {
        this->chosen = 1;
        accept();
        return;
    }
}
Start::~Start() {}
