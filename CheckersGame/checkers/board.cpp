
#include "board.h"
#include <QList>
#include <QImage>
#include <QBrush>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QVector>
#define BOARD_SIZE 8



Board::Board()
{
    grid.resize(8);
    for(int i = 0; i < 8; i++)
    {
         grid[i].resize(8);
    }
}

  void Board::updateGrid(QVector<Checker *> black, QVector<Checker *> white)
  {
      for (int i = 0; i < BOARD_SIZE; i++)
      {
          for (int j = 0; j < BOARD_SIZE; j++)
          {
              grid[i][j] = 0;
          }
      }

      for (int i = 0; i < black.size(); i++)
      {
          if (!black[i]->getIsEaten())
          {

                  grid[black[i]->getYCoord()][black[i]->getXCoord()] = BLACK;

          }
      }
      for (int i = 0; i < white.size(); i++)
      {
          if (!white[i]->getIsEaten())
          {


                  grid[white[i]->getYCoord()][white[i]->getXCoord()] = WHITE;

          }
      }
  }

