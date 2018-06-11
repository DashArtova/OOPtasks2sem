#include "checker.h"
#include <QVector>
#include <QPair>
#define BOARD_SIZE 8

Checker::Checker()
{
    kingCh.push(false);
    wasEaten.push(-1);
}

bool Checker::move(int x, int y, QVector<Checker *> &black, QVector<Checker *> &white, Board *board)
    {
        cpyGrid = board->getGrid();
        //std::vector<std::vector<int>> grid = board->grid;
        eatInLastMove = false;
        oldCoord.push_back(QPair<int, int>(xCoord, yCoord));
        if (xCoord + x < 0 || xCoord + x >= BOARD_SIZE || yCoord + y < 0 || yCoord + y >= BOARD_SIZE)
        {
            return false;
        }
        else if (kingCh.top())
        {
            int xCpy = xCoord;
            int yCpy = yCoord;
            int yIter = y / abs(y);
            int xIter = x / abs(x);

            if (color == WHITE)
            {
                for (int i = 0; i < abs(x); i++)
                {
                    yCpy += yIter;
                    xCpy += xIter;

                    if(xCpy < 0 && xCpy >= BOARD_SIZE && yCpy < 0 && yCpy >=BOARD_SIZE)
                    {
                        return false;
                    }

                    if (board->getGrid()[yCpy][xCpy] == WHITE || (board->getGrid()[yCpy][xCpy] == BLACK && i == abs(x) - 1) ||
                        (board->getGrid()[yCpy][xCpy] == BLACK && board->getGrid()[yCpy + yIter][xCpy + xIter] != 0))
                    {
                        return false;
                    }
                    else if (board->getGrid()[yCpy][xCpy] == BLACK)
                    {
                        for (int i = 0; i < black.size(); i++)
                        {
                            if (black[i]->xCoord == xCpy && black[i]->yCoord == yCpy && !black[i]->getIsEaten())
                            {
                                black[i]->isEaten = true;
                                wasEaten.push(i);
                                eatInLastMove = true;
                            }
                        }
                        board->getGrid()[yCpy][xCpy] = 0;
                    }
                }
            }
            else
            {
                for (int i = 0; i < abs(x); i++)
                {
                    yCpy += yIter;
                    xCpy += xIter;

                    if(xCpy < 0 && xCpy >= BOARD_SIZE && yCpy < 0 && yCpy >=BOARD_SIZE)
                    {
                        return false;
                    }

                    if (board->getGrid()[yCpy][xCpy] == BLACK || (board->getGrid()[yCpy][xCpy] == WHITE && i == abs(x) - 1) ||
                        (board->getGrid()[yCpy][xCpy] == WHITE && board->getGrid()[yCpy + yIter][xCpy + xIter] != 0))
                    {
                        return false;
                    }
                    else if (board->getGrid()[yCpy][xCpy] == WHITE)
                    {
                        for (int i = 0; i < black.size(); i++)
                        {
                            if (white[i]->xCoord == xCpy && white[i]->yCoord == yCpy && !white[i]->getIsEaten())
                            {
                                white[i]->isEaten = true;
                                wasEaten.push(i);
                                eatInLastMove = true;
                                break;

                            }
                        }
                        board->getGrid()[yCpy][xCpy] = 0;
                    }
                }
            }
        }
        else if ((yCoord + y == BOARD_SIZE - 1 && board->getGrid()[yCoord + y][xCoord + x] == 0 && color == BLACK) ||
            (yCoord + y == 0 && board->getGrid()[yCoord + y][xCoord + x] == 0 && color == WHITE))
        {
            xCoord += x;
            yCoord += y;
            kingCh.push(true);
            return true;
        }//
      /* else if ((yCoord + y == BOARD_SIZE - 1 && color == WHITE) || (yCoord + y == 0 && color == BLACK))
        {
            return false;
        }*/
        else if ((color == WHITE && board->getGrid()[yCoord + y][xCoord + x] == BLACK))
        {
            if (((xCoord + 2*x < BOARD_SIZE && xCoord + 2*x >=0) && (yCoord + 2*y < BOARD_SIZE && yCoord + 2*y >= 0)) && board->getGrid()[yCoord + 2 * y][xCoord + 2 * x] == 0)
            {
                for (int i = 0; i < black.size(); i++)
                {
                    if (black[i]->yCoord == yCoord + y && black[i]->xCoord == xCoord + x && !black[i]->getIsEaten())
                    {
                       // black[i]->isEaten = true;
                        black[i]->setIsEaten(true);
                        wasEaten.push(i);
                        eatInLastMove = true;
                        break;
                    }
                }

                xCoord += 2 * x;
                yCoord += 2 * y;
                if(yCoord == 0)
                {
                    kingCh.push(true);
                }

                return true;
            }
            else
            {
                return false;
            }
        }
        else if (color == BLACK && board->getGrid()[yCoord + y][xCoord + x] == WHITE)
        {
            if (((xCoord + 2 * x < BOARD_SIZE && xCoord + 2 * x >= 0) && (yCoord + 2 * y < BOARD_SIZE && yCoord + 2 * y >= 0)) && board->getGrid()[yCoord + 2 * y][xCoord + 2 * x] == 0)
            {
                for (int i = 0; i < white.size(); i++)
                {
                    if (white[i]->yCoord == yCoord + y && white[i]->xCoord == xCoord + x && !white[i]->getIsEaten())
                    {
                        //white[i]->isEaten = true;
                        white[i]->setIsEaten(true);
                        wasEaten.push(i);
                        eatInLastMove = true;
                        break;
                    }
                }
                xCoord += 2 * x;
                yCoord += 2 * y;

                if(yCoord == BOARD_SIZE - 1)
                {
                    kingCh.push(true);
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (board->getGrid()[yCoord + y][xCoord + x] == color || board->getGrid()[yCoord + y][xCoord + x] == color + 2)
        {
            return false;
        }


        xCoord += x;
        yCoord += y;
        if(kingCh.top())
        {
            kingCh.push(true);
        }
        else
        {
            kingCh.push(false);
        }
        return true;
    }


void Checker::unmove(QVector<Checker *> &black, QVector<Checker *> &white, Board *board)
    {
        xCoord = oldCoord.back().first;
        yCoord = oldCoord.back().second;
        oldCoord.pop_back();

        //oldCoord.pop_back();
       // kingCh = false;
        kingCh.pop();
        if(kingCh.isEmpty())
        {
            kingCh.push(false);
        }

        //wasEaten.pop();
        if(wasEaten.top() != -1)
        {
            while (wasEaten.top() != -1)
            {
                if (color == BLACK)
                {
                    white[wasEaten.top()]->isEaten = false;
                }
                else
                {
                    black[wasEaten.top()]->isEaten = false;
                }
                wasEaten.pop();
            }
        }
    }


bool Checker::eatCombo(QVector<Checker *> &black, QVector<Checker *> &white, Board *board)
{
    bool canEat = false;

        if(kingCh.top())
        {

            for(int i= 1; i < 8; i++)
            {
                kingCh.push(true);
                move(i, i, black, white, board);
                if(eatInLastMove)
                {
                    canEat = true;
                }
                unmove(black, white, board);

                if(canEat)
                {
                    return true;
                }
                kingCh.push(true);
                move(-i, i, black, white, board);
                if(eatInLastMove)
                {
                    canEat = true;
                }
                unmove(black, white, board);
                if(canEat)
                {
                    return true;
                }
                kingCh.push(true);
                move(i, -i, black, white, board);
                if(eatInLastMove)
                {
                    canEat = true;
                }
                unmove(black, white, board);
                if(canEat)
                {
                    return true;
                }

                kingCh.push(true);
                move(-i, -i, black, white, board);
                if(eatInLastMove)
                {
                    canEat = true;
                }
                unmove(black, white, board);
                if(canEat)
                {
                    return true;
                }
            }
        }
        else
        {
            move(1, 1, black, white, board);
            if(eatInLastMove)
            {
                canEat = true;
            }
            unmove(black, white, board);

            if(canEat)
            {
                return true;
            }

            move(-1, 1, black, white, board);
            if(eatInLastMove)
            {
                canEat = true;
            }
            unmove(black, white, board);
            if(canEat)
            {
                return true;
            }

            move(1, -1, black, white, board);
            if(eatInLastMove)
            {
                canEat = true;
            }
            unmove(black, white, board);
            if(canEat)
            {
                return true;
            }


            move(-1, -1, black, white, board);
            if(eatInLastMove)
            {
                canEat = true;
            }
            unmove(black, white, board);
            if(canEat)
            {
                return true;
            }

        }
        return false;
}
