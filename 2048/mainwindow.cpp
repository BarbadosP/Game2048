#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include "time.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));//таймер для апдейта
    srand(time(0));//генератор рандомных чисел

    connect(ui->action4x4, SIGNAL(triggered(bool)),this,SLOT(slotFileItem())); //вид игры 4х4
    connect(ui->action5x5, SIGNAL(triggered(bool)),this,SLOT(slotFileItem())); //вид игры 5х5
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (game)
    {
        if (event->key()==Qt::Key_Left)
        {
            for (int i = 0; i < maximum; i++)
            {
                int j=0, k=1;
                while (k < maximum)
                {
                    if(board[i][k]!=0)
                    {
                       if (board[i][j]==0) //сдвигаем
                       {
                           board[i][j]=board[i][k];
                           board[i][k]=0;
                           sdvig++;
                       }
                       else
                       {
                           if(board[i][j]==board[i][k])
                           {
                                board[i][j] = board[i][j]+board[i][k];//складываем
                                board[i][k]=0;
                                j++;
                                sdvig++;
                           }
                           else
                           {
                               j++;
                               if (j==k) k++;
                           }
                       }
                    }
                    else k++;
                }
            } 
         over();
         randomn();
         repaint();
         }

        if (event->key()==Qt::Key_Right)
        {
            for (int i = 0; i < maximum; i++)
            {
                int j=maximum-1, k=maximum-2;
                while (k > -1)
                {
                    if(board[i][k]!=0)
                    {
                       if (board[i][j]==0)
                       {
                           board[i][j]=board[i][k]; //сдвигаем
                           board[i][k]=0;
                           sdvig++;
                       }
                       else
                       {
                           if(board[i][j]==board[i][k])
                           {
                                board[i][j] = board[i][j]+board[i][k];//складываем
                                board[i][k]=0;
                                j--;
                                sdvig++;
                           }
                           else
                           {
                               j--;
                               if (j==k) k--;
                           }
                       }
                    }
                    else k--;
                }
            }
         over();
         randomn();
         repaint();
         }

        if (event->key()==Qt::Key_Up)
        {
            for (int j = 0; j < maximum; j++)
            {
                int i=0, k=1;
                while (k < maximum)
                {
                    if(board[k][j]!=0)
                    {
                       if (board[i][j]==0)
                       {
                           board[i][j]=board[k][j]; //сдвигаем
                           board[k][j]=0;
                           sdvig++;
                       }
                       else
                       {
                           if(board[i][j]==board[k][j])
                           {
                                board[i][j] = board[i][j]+board[k][j];//складываем
                                board[k][j]=0;
                                i++;
                                sdvig++;
                           }
                           else
                           {
                               i++;
                               if (i==k) k++;
                           }
                       }
                    }
                    else k++;
                }
            }
         over();
         randomn();
         repaint();
         }


        if (event->key()==Qt::Key_Down)
        {
            for (int j = 0; j < maximum; j++)
            {
                int i=maximum-1, k=maximum-2;
                while (k >-1)
                {
                    if(board[k][j]!=0)
                    {
                       if (board[i][j]==0)
                       {
                           board[i][j]=board[k][j]; //сдвигаем
                           board[k][j]=0;
                           sdvig++;
                       }
                       else
                       {
                           if(board[i][j]==board[k][j])
                           {
                                board[i][j] = board[i][j]+board[k][j];//складываем
                                board[k][j]=0;
                                i--;
                                sdvig++;
                           }
                           else
                           {
                               i--;
                               if (i==k) k--;
                           }
                       }
                    }
                    else k--;
                }
            }
         over();
         randomn();
         repaint();
         }
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    if (game)
    {

        int coordX, coordY;
        QPainter pa (this);
        pa.drawImage(QRect(0, ui_otstup, razmer_pole, razmer_pole), pole);


        for (int i = 0; i < maximum; i++) //строки
            {
                for (int j = 0; j < maximum; j++) //столбцы
                {
                    QImage r;
                    


                    r=(board[i][j]==0?p0:board[i][j]==2?p2:board[i][j]==4?p4:board[i][j]==8?p8:board[i][j]==16?p16:board[i][j]==32?p32:board[i][j]==64?p64:board[i][j]==128?p128:board[i][j]==256?p256:board[i][j]==512?p512:board[i][j]==1024?p1024:board[i][j]==2048?p2048:board[i][j]==4096?p4096:p0);

                    coordY = razmer_otstupov * i + razmer_kletki * i + razmer_otstupov + ui_otstup;      //вычисляем размеры клетки и отступы
                    coordX = razmer_otstupov * j + razmer_kletki * j + razmer_otstupov;
                    pa.drawImage(QRect(coordX, coordY, razmer_kletki, razmer_kletki), r);
                }
             }
    }
}

void MainWindow::randomn() //фунцкия рандомит новые элементы и проверяет игру на проигрыш
{
    if (game)
    {
        if (sdvig>0) //новый элемент появляется только при условии, что на поле элементы изменили местоположение
        {
            int dx, dy;
            do //рандомим новый элемент
            {
                dx = rand()%maximum;
                dy = rand()%maximum;
            }
            while (board[dx][dy]!=0);

            int r=rand()%100;
            if (r<=90)
                board[dx][dy] = 2;
            else
                board[dx][dy] = 4;
            sdvig=0;
        }
    }
}

void MainWindow::over() //проверка на проигрыш или выигрыш
{
    p=0;
    for (int i = 0; i < maximum; i++)
    {
        for (int j = 0; j < maximum; j++)
        {
            if (board[i][j]==0) p++;
            if (win==0) if (board[i][j]==2048) win++; //проверка на выигрыш в игре, проверка делается только при условии, что до этого выигрыша не было
            if (wow==0) if (board[i][j]==4096) wow++;
        }
    }

    if (p==0)
    {
        game=false;
    }

    if (game==0)        //завершает игру
        {
            QMessageBox::information(this, "ERROR", "GAME OVER");
            qApp->exit();
        }
    if (win==1)        //табличка о победе
        {
            QMessageBox::information(this, "2048", "ПОБЕДА");
            win++; //единократно увеличивает на 1, чтобы при каждом ходе не высвечивалась табличка о выигрыше
        }
    if (wow==1)        //завершает игру, табличка о победе при счете 4096
        {
            QMessageBox::information(this, "WOOW", "ПОБЕДА 2X, набрано 4096!");
            qApp->exit();
        }
}


void MainWindow::slotFileItem()
{
    QAction *obj=(QAction*) sender();

    if (obj==ui->action4x4)
    {
        pole=pole4x4;
        razmer_pole=363; //объявялем размеры поля для игры 4x4
        maximum=4;
    }
    if (obj==ui->action5x5)
    {
        pole=pole5x5;
        razmer_pole=450; //объявялем размеры поля для игры 4x4
        maximum=5;
    }

    setFixedSize(razmer_pole,razmer_pole+ui_otstup);
    randomn(); //выводим первый элемент для начала игры
    repaint();
}

void MainWindow::update()
{
}
