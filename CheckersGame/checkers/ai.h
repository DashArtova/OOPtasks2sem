#ifndef AI_H
#define AI_H
#pragma once
#include "board.h"
#include "checker.h"
#include <QObject>

struct Move {
    cheColor color;
    int pos;
    int x;
    int y;
};
class AI:public QObject
{
    Q_OBJECT
private:
    int depthAI;
    int score;

    Move bestMove;
public:
    AI(int depth);
    int eval(Board *board);
    int minimax(Board *board, int depth, bool isMax, QVector<Checker *> &black, QVector<Checker *> &white, cheColor color);
    Move findBestMove(Board *board, QVector<Checker *> &black, QVector<Checker *> &white, cheColor color);
};

#endif // AI_H
