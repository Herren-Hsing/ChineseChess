#ifndef START_H
#define START_H
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class Start : public QDialog
{
    Q_OBJECT
public:
    int chosen;
    QPushButton *modes[2];

    Start(QWidget *parent = nullptr);
    ~Start();
signals:
public slots:
    void slotClicked();
};
#endif
