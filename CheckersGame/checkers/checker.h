#ifndef CHECKER_H
#define CHECKER_H
#pragma once
#include <QVector>
#include <QStack>
#include <QObject>
#include "board.h"


enum cheColor { BLACK = 1, WHITE };

class Board;

class Checker:public QObject
{
    Q_OBJECT
public:
        Checker();
            void setCoords(int x, int y)
            {
                xCoord = x;
                yCoord = y;
            }
            int getXCoord()
            {
                return xCoord;
            }
            int getYCoord()
            {
                return yCoord;
            }
            void setColor(cheColor col)
            {
                color = col;
            }
            bool getKingCh()
            {
                return kingCh.top();
            }
            bool getWasKingMore1Step()
            {

                if(kingCh.top())
                {
                    kingCh.pop();
                    if(kingCh.top())
                    {
                        kingCh.push(true);
                        return true;
                    }
                    kingCh.push(true);
                }
                return false;
            }
            bool getIsEaten()
            {
                return isEaten;
            }
            void setIsEaten(bool val)
            {
                isEaten = val;
            }
            void endWasEaten()
            {
                wasEaten.push(-1);
            }
            void clearWasEaten()
            {

                while(wasEaten.top() != -1)
                {
                    wasEaten.pop();
                }
            }
            bool getEatInLastMove()
            {
                return eatInLastMove;
            }
            void setEatInLastMove()
            {
                eatInLastMove = false;
            }
            bool move(int x, int y, QVector<Checker *> &black, QVector<Checker *> &white, Board *board);
            void unmove(QVector<Checker *> &black, QVector<Checker *> &white, Board *board);
            bool eatCombo(QVector<Checker *> &black, QVector<Checker *> &white, Board *board);
private:

        cheColor color;
        QVector<QPair<int, int>> oldCoord;
        int xCoord;
        int yCoord;
        QStack<bool> kingCh;
        bool isEaten = false;
        bool eatInLastMove = false;
        QStack<int> wasEaten;
        QVector<QVector<int>> cpyGrid;
};

#endif // CHECKER_H
