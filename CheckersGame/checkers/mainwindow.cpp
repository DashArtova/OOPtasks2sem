#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "checker.h"
#include "ai.h"
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QRect>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QBrush>
#include <QScreen>
#include <QDebug>
#include <QPointer>
#include <QDebug>
#include <QMessageBox>
#define INF 1000

class Board;
class Checker;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QScreen *screen = QApplication::screens().at(0);
    int width = screen->size().width();
    int height = screen->size().height();
    QImage img(":/images/boardGreen.png");
    ui->label1->setGeometry(0, (height - (img.height()*width)/img.width()) / 2, width, (img.height()*width)/img.width());
    ui->label1->setPixmap(QPixmap::fromImage(img));

    ui->label1->setScaledContents(true);

    this->setStyleSheet("background-image: url(\":/images/bg.bmp\");");


    blackLab.resize(12);
    whiteLab.resize(12);

    int checkerWidth = ui->label1->size().width() / 8;
    int checkerHeight = ui->label1->size().height() / 8;

    QImage blackCheckerImg(":/images/blackCh.png");
    QImage whiteCheckerImg(":/images/whiteCh.png");

    //createBoard();
    //createCheckers();
    black.resize(12);
    white.resize(12);
    for(int i= 0 ; i < 12; i++)
    {
        blackLab[i] = new QLabel(ui->label1);
        blackLab[i]->setPixmap(QPixmap::fromImage(blackCheckerImg));
        blackLab[i]->setScaledContents(true);
        black[i] = new Checker();
        black[i]->endWasEaten();

        whiteLab[i] = new QLabel(ui->label1);
        whiteLab[i]->setPixmap(QPixmap::fromImage(whiteCheckerImg));
        whiteLab[i]->setScaledContents(true);
        white[i] = new Checker();
        white[i]->endWasEaten();
    }

    board = new Board();


    for (int i = 0, j = 0, k = 1, flag = 0; i < 12; i++)
    {
        blackLab[i]->setGeometry(k * checkerWidth + 10, j * checkerHeight + 10, checkerWidth - 20, checkerHeight - 20);
        black[i]->setCoords(k, j);
        black[i]->setColor(BLACK);
        board->getGrid()[k][j] = 1;

        if (k + 2 >= 8)
            {
                k = flag;
                flag = 1 - flag;
                j++;
            }
            else
            {
                k += 2;
            }
    }

    for (int i = 0, j = 8 - 1, k = 0, flag = 1; i < 12; i++)
    {
        whiteLab[i]->setGeometry(k * checkerWidth +10, j * checkerHeight + 10, checkerWidth - 20, checkerHeight - 20);
        white[i]->setCoords(k, j);
        white[i]->setColor(WHITE);
        board->getGrid()[k][j] = 2;

        if (k + 2 >= 8)
        {
            k = flag;
            flag = 1 - flag;
            j--;
        }
        else
        {
            k += 2;
        }
    }
    comp = new AI(2);
    //comp = new AI();


 // QPixmap pix("C:/Users/mixon/Desktop/lol/8.png");
   // QImage img("C:/Users/mixon/Desktop/lol/8T6G5CwO5Co.jpg");
    //QPixmap pix(":/8.png");
    //ui->label1->setPixmap(pix);
   // QPixmap pixmapTarget = QPixmap("C:/8.png");
    //pixmapTarget = pixmapTarget.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //ui->label->setPixmap(pixmapTarget );
 //   QImage img("q.png");

   // QRect rect ;
    //rect.setRect(0, 0, 100,100);
   // rect.moveTo(100,100);
    //QPainter *painter = new QPainter(this);
    //painter->drawImage(rect, img);
    //QString str = "123";
    //painter->drawText(100, 100, str);
    //ui->label->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBoard()
{
    for(int i = 0; i < 12; i++)
    {
        if(black[i]->getIsEaten())
        {
           blackLab[i]->setGeometry(0,0,0,0);
           // delete blackLab[i];
           // blackLab[i] = Q_NULLPTR;
        }
        if(white[i]->getIsEaten())
        {
            //delete whiteLab[i];
           // whiteLab[i] = Q_NULLPTR;
            whiteLab[i]->setGeometry(0,0,0,0);
        }

        if(black[i]->getKingCh())
        {
            blackLab[i]->setPixmap(QPixmap(":/images/blackKing.jpg"));
        }
        if(white[i]->getKingCh())
        {
            whiteLab[i]->setPixmap(QPixmap(":/images/whiteKing.jpg"));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int height = event->y() - ui->label1->y();
    int width = event->x();
    if(!isClicked)
    {
        curr.first = -1;
       for(int i = 0; i < 12; i++)
       {
           if(blackLab[i] && blackLab[i]->x() <= width && blackLab[i]->x() + blackLab[i]->size().width() >= width &&
               blackLab[i]->y() <= height && blackLab[i]->y() + blackLab[i]->size().height() >= height    )
           {
               curr.first = i;
               curr.second = 1;
           }

           else if (whiteLab[i] && whiteLab[i]->x() <= width && whiteLab[i]->x() + whiteLab[i]->size().width() >= width &&
                    whiteLab[i]->y() <= height && whiteLab[i]->y() + whiteLab[i]->size().height() >= height    )
           {
               curr.first = i;
               curr.second = 2;

               if(white[curr.first]->getKingCh())
               {
                   whiteLab[i]->setPixmap(QPixmap(":/images/whiteKingActive.bmp"));
               }
               else
               {
                    whiteLab[i]->setPixmap(QPixmap(":/images/whiteActive.bmp"));
               }

           }
       }
       if(curr.first != -1)
       {

       isClicked = true;
       }
    }
    else
    {
        int widthBoard = ui->label1->size().width() / 8;
        int heightBoard = ((ui->label1->size().height()* ui->label1->size().width())/ui->label1->size().width()) / 8;

        int row = height / heightBoard;
        int col = width / widthBoard;

        int oldCol;
        int oldRow;


        QLabel *current;



        if(curr.second == 1)
        {
            /*current = blackLab[curr.first];
            oldCol = current->x() / widthBoard;
            oldRow = current->y() / heightBoard;




            board->getGrid()[row][col] = 1;*/


        }
        else
        {
            int isEat = false;
            current = whiteLab[curr.first];
            oldCol = current->x()/ widthBoard;
            oldRow = current->y()/ heightBoard;

            //board->getGrid()[row][col] = 2;

                isEat = false;
            white[curr.first]->move(col - white[curr.first]->getXCoord(), row -  white[curr.first]->getYCoord(),black, white, board);
            if(white[curr.first]->getEatInLastMove())
            {
                isEat = true;
            }

            white[curr.first]->clearWasEaten();
            if(white[curr.first]->getKingCh())
            {
                whiteLab[curr.first]->setPixmap(QPixmap(":/images/whiteKing.png"));
            }
            else
            {
                whiteLab[curr.first]->setPixmap(QPixmap(":/images/whiteCh.png"));
            }
            board->updateGrid(black, white);
            updateBoard();
            if(!isEat || !white[curr.first]->eatCombo(black, white, board))
            {
                white[curr.first]->clearWasEaten();
                white[curr.first]->setEatInLastMove();

            }
            else
            {
                isClicked = false;
                current->setGeometry((white[curr.first]->getXCoord()) * widthBoard + 10, (white[curr.first]->getYCoord()) * heightBoard + 10, current->size().width(), current->size().height());
                return;
            }



        }


            current->setGeometry((white[curr.first]->getXCoord()) * widthBoard + 10, (white[curr.first]->getYCoord()) * heightBoard + 10, current->size().width(), current->size().height());

           // board->getGrid()[oldRow][oldCol] = 0;



    isClicked = false;

    move.pos = 2 * INF;
    move.x = move.y = INF;
    move.color = BLACK;

    board->updateGrid(black, white);
    updateBoard();
    while(true)
    {
    move = comp->findBestMove(board, black, white, BLACK);
    if (move.pos == 2*(-INF))
    {
        break;
      QMessageBox msg;
      msg.setText("You lose");
      msg.exec();
    }
    else if(move.pos == 2*INF)
    {
        break;
        QMessageBox msg;
        msg.setText("You win");
        msg.exec();
    }



                if (move.color == BLACK)
                {
                    black[move.pos]->move(move.x, move.y, black, white, board);
                    black[move.pos]->clearWasEaten();
                    if(black[move.pos]->getEatInLastMove() && !black[move.pos]->getWasKingMore1Step())
                    {
                        move.x *= 2;
                        move.y *= 2;
                    }
                    blackLab[move.pos]->setGeometry( blackLab[move.pos]->x() + (move.x) * widthBoard, blackLab[move.pos]->y()+(move.y) * heightBoard, blackLab[move.pos]->size().width(), blackLab[move.pos]->size().height());

                }
               /* else
                {
                    white[move.pos]->move(move.x, move.y, black, white, board);
                    whiteLab[move.pos]->setGeometry((oldRow + move.x) * widthBoard + 10, (oldCol + move.y) * heightBoard + 10, current->size().width(), current->size().height());

                    if (!white[move.pos]->getEatInLastMove())
                    {
                        if (isEat)
                        {
                            white[move.pos]->setEatInLastMove();
                            white[move.pos]->endWasEaten();
                            isEat = false;
                        }
                       // break;
                    }
                    else
                    {
                        isEat = true;
                    }
                }*/


            board->updateGrid(black, white);
            updateBoard();

            if(!black[move.pos]->getEatInLastMove() || !black[move.pos]->eatCombo(black, white, board))
            {
                black[move.pos]->clearWasEaten();
                black[move.pos]->setEatInLastMove();
                blackLab[move.pos]->setGeometry( black[move.pos]->getXCoord()* widthBoard + 10, black[move.pos]->getYCoord() * heightBoard + 10, blackLab[move.pos]->size().width(), blackLab[move.pos]->size().height());
                board->updateGrid(black, white);

                updateBoard();
                break;
            }

        }

            updateBoard();
            bool isAbleToMove = false;
            for(int i = 0; i < white.size(); i++)
            {
                if(!white[i]->getIsEaten())
                {
                    isAbleToMove = true;
                    break;
                }
            }
            if(!isAbleToMove)
            {
                QMessageBox msg;
                msg.setText("You lose");
                msg.exec();
            }
            else
            {
                isAbleToMove = false;
                for(int i = 0; i < black.size(); i++)
                {
                    if(!black[i]->getIsEaten())
                    {
                        isAbleToMove = true;
                        break;
                    }
                }
                if(!isAbleToMove)
                {
                    QMessageBox msg;
                    msg.setText("You win");
                    msg.exec();
                }
            }


    }
   // ui->label1->setGeometry(event->x(), event->y(), 300, 300);
}
