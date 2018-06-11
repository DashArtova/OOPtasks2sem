#include "game.h"
#include "board.h"
#include <QList>
#include <QImage>
#include <QBrush>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QVector>
#include <QTimer>


Game::Game(QWidget *parent){
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,0,0);
    setBackgroundBrush(QBrush(QImage(":/bg.bmp")));
    setScene(scene);
   // setFixedSize(400, 400);
    QTimer *timer = new QTimer();
    //board = new Board();

   // board->setPos(300,300);
 //   scene->setSceneRect(0,0,1080,1860);
   // board->setPos(-700, 0);
    //scene->addItem(board);

    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, 100, 100);
    //scene->addItem(lab);

    //scene->addItem(board->board);

    //QObject::connect(timer, SIGNAL(timeout()), board, SLOT(buildBoard()));
    //timer->start(20);

   // show();
}
