#include "ai.h"
#include "board.h"
#include "checker.h"
#define BOARD_SIZE 8
#define KING_VALUE 7
#define INF 1000


AI::AI(int depth)
{
    depthAI = depth;

}

int AI::eval(Board *board)
    {
        int score = 0;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board->getGrid()[i][j] == WHITE)
                {
                    score++;
                }
                else if (board->getGrid()[i][j] == WHITE + 2)
                {
                    score += KING_VALUE;
                }
                else if (board->getGrid()[i][j] == BLACK)
                {
                    score--;
                }
                else if (board->getGrid()[i][j] == BLACK + 2)
                {
                    score -= KING_VALUE;
                }
            }
        }
        return score;
    }


int AI::minimax(Board *board, int depth, bool isMax, QVector<Checker *> &black, QVector<Checker *> &white, cheColor color)
    {
        board->updateGrid(black, white);
        int score = eval(board);

        if (depth == 0 || score >= 40 || score <= -40)
        {
            return score;
        }
        bool isPosibleToMove = true;
        bool cantMove = true;
        int curr;
        if (isMax)
        {
            int best = -INF;
            if (color == BLACK)
            {
            //	for (int i = 0; i < black.size(); i++)
            //	{
            //		if (!black[i]->getIsEaten())
            //		{
            //			if (black[i]->getKingCh())
            //			{
            //				for (int j = 0; j < BOARD_SIZE; j++)
            //				{
            //					black[i]->move(j, j, black, white, board);
            //					best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //					black[i]->unmove(black, white);

            //					black[i]->move(j, -j, black, white, board);
            //					best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //					black[i]->unmove(black, white);

            //					black[i]->move(-j, j, black, white, board);
            //					best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //					black[i]->unmove(black, white);

            //					black[i]->move(-j, -j, black, white, board);
            //					best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //					black[i]->unmove(black, white);
            //				}
            //			}
            //			else
            //			{
            //				black[i]->move(1, 1, black, white, board);//move left
            //				best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //				black[i]->unmove(black, white);

            //				black[i]->move(-1, 1, black, white, board);//move right
            //				best = std::max(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
            //				black[i]->unmove(black, white);
            //			}
            //		}
            //	}
            }
            else
            {
                for (int i = 0; i < white.size(); i++)
                {
                    if (!white[i]->getIsEaten())
                    {
                        if (white[i]->getKingCh())
                        {
                            for (int j = 1; j < BOARD_SIZE; j++)
                            {
                                isPosibleToMove = white[i]->move(j, j, black, white, board);
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (white[i]->getEatInLastMove())
                                    {
                                        curr += INF;
                                    }
                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = j;
                                            bestMove.y = j;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }

                                isPosibleToMove = white[i]->move(-j, j, black, white, board);
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (white[i]->getEatInLastMove())
                                    {
                                        curr += INF;
                                    }
                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = -j;
                                            bestMove.y = j;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }


                                isPosibleToMove = white[i]->move(j, -j, black, white, board);
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (white[i]->getEatInLastMove())
                                    {
                                        curr += INF;
                                    }
                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = j;
                                            bestMove.y = -j;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }


                                isPosibleToMove = white[i]->move(-j, -j, black, white, board);
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (white[i]->getEatInLastMove())
                                    {
                                        curr += INF;
                                    }
                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = -j;
                                            bestMove.y = -j;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }
                            }
                        }
                        else
                        {

                            isPosibleToMove = white[i]->move(1, -1, black, white, board);//move right
                            board->updateGrid(black, white);
                            if (isPosibleToMove)
                            {
                                cantMove = false;
                                isPosibleToMove = false;
                                curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                if(curr == 2*INF&& depth == depthAI)
                                {
                                    return curr;
                                }
                                if (white[i]->getEatInLastMove())
                                {
                                    curr += INF;

                                }
                                if (best < curr)
                                {
                                    best = curr;
                                    if (depth == depthAI)
                                    {
                                        bestMove.color = WHITE;
                                        bestMove.pos = i;
                                        bestMove.x = 1;
                                        bestMove.y = -1;
                                    }
                                }
                                white[i]->unmove(black, white, board);
                                board->updateGrid(black, white);
                            }

                            isPosibleToMove = white[i]->move(-1, -1, black, white, board);//move left
                            board->updateGrid(black, white);
                            if (isPosibleToMove)
                            {
                                cantMove = false;
                                isPosibleToMove = false;
                                 curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                 if(curr == 2*INF&& depth == depthAI)
                                 {
                                     return curr;
                                 }
                                 if (white[i]->getEatInLastMove())
                                 {
                                     curr += INF;

                                 }
                                if (best < curr)
                                {
                                    best = curr;
                                    if (depth == depthAI)
                                    {
                                        bestMove.color = WHITE;
                                        bestMove.pos = i;
                                        bestMove.x = -1;
                                        bestMove.y = -1;
                                    }
                                }
                                white[i]->unmove(black, white, board);
                                board->updateGrid(black, white);
                            }

                            if (white[i]->getYCoord() + 2 < BOARD_SIZE && white[i]->getXCoord() + 2 < BOARD_SIZE && board->getGrid()[white[i]->getYCoord() + 1][white[i]->getXCoord() + 1] == BLACK && board->getGrid()[white[i]->getYCoord() + 2][white[i]->getXCoord() + 2] == 0)
                            {
                                isPosibleToMove = white[i]->move(1, 1, black, white, board);//move left
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                        curr += INF;

                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = 1;
                                            bestMove.y = 1;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }
                            }


                            /////
                            if (white[i]->getYCoord() + 2 < BOARD_SIZE && white[i]->getXCoord() - 2 >= 0 && board->getGrid()[white[i]->getYCoord() + 1][white[i]->getXCoord() - 1] == BLACK && board->getGrid()[white[i]->getYCoord() + 2][white[i]->getXCoord() - 2] == 0)
                            {
                                isPosibleToMove = white[i]->move(-1, 1, black, white, board);//move left
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, BLACK);
                                    if(curr == 2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    curr += INF;

                                    if (best < curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = WHITE;
                                            bestMove.pos = i;
                                            bestMove.x = -1;
                                            bestMove.y = 1;
                                        }
                                    }
                                    white[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }
                            }

                        }
                    }
                }
            }
            if (!cantMove)
            {
                if(best >= INF/2)
                {
                return best - INF;
                }
                return best;
            }
            return -2*INF;
        }
        else
        {
                int best = INF;
                if (color == BLACK)
                {
                    for (int i = 0; i < black.size(); i++)
                    {

                        if (!black[i]->getIsEaten())
                        {
                            if (black[i]->getKingCh())
                            {
                                for (int j = 1; j < BOARD_SIZE; j++)
                                {
                                    isPosibleToMove = black[i]->move(j, j, black, white, board);
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        isPosibleToMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF&& depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        if (black[i]->getEatInLastMove())
                                        {
                                            curr -= INF;
                                        }
                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = j;
                                                bestMove.y = j;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }

                                    isPosibleToMove = black[i]->move(j, -j, black, white, board);
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        isPosibleToMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF&& depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        if (black[i]->getEatInLastMove())
                                        {
                                            curr -= INF;
                                        }
                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = j;
                                                bestMove.y = -j;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }

                                    isPosibleToMove = black[i]->move(-j, j, black, white, board);
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        isPosibleToMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF&& depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        if (black[i]->getEatInLastMove())
                                        {
                                            curr -= INF;
                                        }
                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = -j;
                                                bestMove.y = j;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }


                                    isPosibleToMove = black[i]->move(-j, -j, black, white, board);
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        isPosibleToMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF&& depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        if (black[i]->getEatInLastMove())
                                        {
                                            curr -= INF;
                                        }
                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = -j;
                                                bestMove.y = -j;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }
                                }
                            }
                            else
                            {

                                isPosibleToMove = black[i]->move(1, 1, black, white, board);//move left
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                    if(curr == -2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (black[i]->getEatInLastMove())
                                    {
                                        curr -= INF;

                                    }
                                    if (best > curr)
                                    {

                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = BLACK;
                                            bestMove.pos = i;
                                            bestMove.x = 1;
                                            bestMove.y = 1;
                                        }
                                    }
                                    black[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }


                                isPosibleToMove = black[i]->move(-1, 1, black, white, board);//move right
                                board->updateGrid(black, white);
                                if (isPosibleToMove)
                                {
                                    cantMove = false;
                                    isPosibleToMove = false;
                                    curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                    if(curr == -2*INF&& depth == depthAI)
                                    {
                                        return curr;
                                    }
                                    if (black[i]->getEatInLastMove())
                                    {
                                        curr -= INF;

                                    }
                                    if (best > curr)
                                    {
                                        best = curr;
                                        if (depth == depthAI)
                                        {
                                            bestMove.color = BLACK;
                                            bestMove.pos = i;
                                            bestMove.x = -1;
                                            bestMove.y = 1;
                                        }
                                    }
                                    black[i]->unmove(black, white, board);
                                    board->updateGrid(black, white);
                                }

                                if (black[i]->getYCoord() - 2 >= 0 && black[i]->getXCoord() + 2 < BOARD_SIZE && board->getGrid()[black[i]->getYCoord() - 1][black[i]->getXCoord() + 1] == WHITE && board->getGrid()[black[i]->getYCoord() - 2][black[i]->getXCoord() + 2] == 0)
                                {
                                    isPosibleToMove = black[i]->move(1, -1, black, white, board);//move left
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF&& depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        curr -= INF;

                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = 1;
                                                bestMove.y = -1;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }
                                }


                                if (black[i]->getYCoord() - 2 >= 0 && black[i]->getXCoord() - 2 >= 0 && board->getGrid()[black[i]->getYCoord() - 1][black[i]->getXCoord() - 1] == WHITE && board->getGrid()[black[i]->getYCoord() - 2][black[i]->getXCoord() - 2] == 0)
                                {
                                    isPosibleToMove = black[i]->move(-1, -1, black, white, board);//move left
                                    board->updateGrid(black, white);
                                    if (isPosibleToMove)
                                    {
                                        cantMove = false;
                                        curr = minimax(board, depth - 1, !isMax, black, white, WHITE);
                                        if(curr == -2*INF && depth == depthAI)
                                        {
                                            return curr;
                                        }
                                        curr -= INF;

                                        if (best > curr)
                                        {
                                            best = curr;
                                            if (depth == depthAI)
                                            {
                                                bestMove.color = BLACK;
                                                bestMove.pos = i;
                                                bestMove.x = -1;
                                                bestMove.y = -1;
                                            }
                                        }
                                        black[i]->unmove(black, white, board);
                                        board->updateGrid(black, white);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    //for (int i = 0; i < white.size(); i++)
                    //{
                    //	if (!white[i]->getIsEaten())
                    //	{
                    //		if (white[i]->getKingCh())
                    //		{
                    //			for (int j = 0; j < BOARD_SIZE; j++)
                    //			{
                    //				white[i]->move(j, j, black, white, board);
                    //				best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //				white[i]->unmove(black, white);

                    //				white[i]->move(-j, j, black, white, board);
                    //				best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //				white[i]->unmove(black, white);

                    //				white[i]->move(j, -j, black, white, board);
                    //				best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //				white[i]->unmove(black, white);

                    //				white[i]->move(-j, -j, black, white, board);
                    //				best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //				white[i]->unmove(black, white);
                    //			}
                    //		}
                    //		else
                    //		{
                    //			white[i]->move(1, -1, black, white, board);//move right
                    //			best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //			white[i]->unmove(black, white);

                    //			white[i]->move(-1, -1, black, white, board);//move left
                    //			best = std::min(best, minimax(board, depth - 1, !isMax, black, white, WHITE));
                    //			white[i]->unmove(black, white);
                    //		}
                    //	}
                    //}
                }

                if (!cantMove)///
                {
                    if(best < -INF/2)
                    {
                    return best + INF;
                    }
                    return best;
                }
                return 2*INF;
        }

    }


Move AI::findBestMove(Board *board, QVector<Checker *> &black, QVector<Checker *> &white, cheColor color)
    {
        int tempScore = 0;
        if (color == BLACK)
        {
            tempScore = minimax(board, depthAI, false, black, white, BLACK);
        }
        else
        {
            tempScore = minimax(board, depthAI, true , black, white, WHITE);
        }
        if (tempScore == 2*INF )
        {
            bestMove.pos = 2*INF;
        }
        else if(tempScore == -2*INF)
        {
            bestMove.pos = -2*INF;
        }
        return bestMove;
    }
