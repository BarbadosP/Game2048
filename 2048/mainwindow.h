#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void randomn();

    bool game=true;
    int win=0;//меняется на выигрыш, но позволяет продолжить игру
    int wow=0; //конечный выигрыш, не позволяет играть дальше

    const int WIDHTPOLE=25;
    const int HEIGHTPOLE=25;


private:

    QImage pole4x4=QImage(":/pic/unnamed.png");
    QImage pole5x5=QImage(":/pic/pole5x5.png");
    QImage p1024=QImage(":/pic/1024.png");
    QImage p128=QImage(":/pic/128.png");
    QImage p16=QImage(":/pic/16.png");
    QImage p2=QImage(":/pic/2.png");
    QImage p2048=QImage(":/pic/2048.png");
    QImage p256=QImage(":/pic/256.png");
    QImage p32=QImage(":/pic/32.png");
    QImage p4=QImage(":/pic/4.png");
    QImage p4096=QImage(":/pic/4096.png");
    QImage p512=QImage(":/pic/512.png");
    QImage p64=QImage(":/pic/64.png");
    QImage p8=QImage(":/pic/8.png");
    QImage p0=QImage(":/pic/p0.png");
    QImage pole;

    Ui::MainWindow *ui;

    int board[5][5] = {0};

    int maximum=5;
    int razmer_pole;
    int razmer_otstupov=11;
    int razmer_kletki=77;
    int ui_otstup = 20;
    int sdvig=1;
    int p=0;
    void over();


public slots:
    void slotFileItem();
    void update();
};

#endif // MAINWINDOW_H
