#ifndef GAME_H
#define GAME_H

#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLabel>
#include "board.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    QGraphicsScene *getScene()
    {
        return scene;
    }
private:
    QGraphicsScene * scene;
    class Board *board;
};

#endif // GAME_H
