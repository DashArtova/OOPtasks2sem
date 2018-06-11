#ifndef BOARD_H
#define BOARD_H

#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QLabel>

#include "checker.h"

class Checker;

class Board:public QObject
{
    Q_OBJECT
public:
    Board();
    void updateGrid(QVector<Checker *> black, QVector<Checker *> white);
    QVector<QVector<int>> getGrid()
        {
            return grid;
        }
    void setGrid(QVector<QVector<int>> cpyGrid)
    {
        grid = cpyGrid;
    }
    void changeGrid(int x, int y, int val)
    {
        grid[y][x] = val;
    }
private:
    QVector<QVector<int>> grid;
};
#endif // BOARD_H
