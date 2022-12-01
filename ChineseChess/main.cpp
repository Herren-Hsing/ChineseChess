#include "chess.h"
#include "start.h"
#include "switch.h"
#include "singlegame.h"
#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("D:/QT/try/ChineseChess/H.mp3"));
    player->setVolume(10);
    player->play();

    Start pattern;
    if (pattern.exec() != QDialog::Accepted)
        return 0;

    Switch w(pattern.chosen); //游戏模式
    player->pause();
    w.show();
    w.setWindowIcon(QIcon(":/logo.png"));
    w.setWindowTitle(QString("Chinese Chess"));
    w.setFixedSize(830, 900);

    return app.exec();
}
