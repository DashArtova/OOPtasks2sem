#include <QString>
#include <QtTest>
#include <QWidget>
#include "test.h"


Test::Test()
{
}

void Test::testCase1()//checker::move()
{
    Board *board = new Board();
    QVector<Checker*> black;
    QVector<Checker*> white;
    black.resize(12);
    white.resize(12);

    for(int i = 0; i < 12; i++)
    {
        black[i] = new Checker();
        white[i] = new Checker();
        black[i]->setColor(BLACK);
        white[i]->setColor(WHITE);
        black[i]->setIsEaten(true);
        white[i]->setIsEaten(true);
    }
    black[0]->setCoords(7,6);
    black[0]->setIsEaten(false);
    board->changeGrid(6, 7, 1);
    black[0]->move(1,1, black, white, board);


    QCOMPARE(black[0]->getXCoord(), 7);
    QCOMPARE(black[0]->getYCoord(), 6);

    board->changeGrid(6, 7, 0);
    black[0]->setCoords(0, 1);
    board->changeGrid(0, 1, 1);
    white[0]->setIsEaten(false);
    white[0]->setCoords(1, 2);
    board->changeGrid(1, 2, 2);
    black[0]->move(1, 1,black, white, board);

    QCOMPARE(black[0]->getXCoord(), 2);
    QCOMPARE(black[0]->getYCoord(), 3);
    QCOMPARE(white[0]->getIsEaten(), true);

    black[0]->unmove(black, white, board);

    QCOMPARE(black[0]->getXCoord(), 0);
    QCOMPARE(black[0]->getYCoord(), 1);
    QCOMPARE(white[0]->getIsEaten(), false);

    black[0]->move(1, 1, black, white, board);

    board->changeGrid(1, 2, 0);
    board->changeGrid(2, 3, 0);
    board->changeGrid(1, 4, 1);
    black[0]->move(-1, 1, black, white, board);
    QCOMPARE(black[0]->getXCoord(), 2);
    QCOMPARE(black[0]->getYCoord(), 3);

     board->changeGrid(1, 4, 0);

     black[0]->move(-1, 1, black, white, board);
     QCOMPARE(black[0]->getXCoord(), 1);
     QCOMPARE(black[0]->getYCoord(), 4);

     black[0]->unmove(black, white, board);
     QCOMPARE(black[0]->getXCoord(), 2);
     QCOMPARE(black[0]->getYCoord(), 3);

     black[0]->setCoords(1,6);
     black[0]->move(-1, 1, black, white, board);
     QCOMPARE(black[0]->getKingCh(), true);

     black[0]->unmove(black, white, board);
     QCOMPARE(black[0]->getKingCh(), false);

     black[0]->move(-1, 1, black, white, board);
     black[0]->move(2, -2 , black, white, board);

     QCOMPARE(black[0]->getXCoord(), 2);
     QCOMPARE(black[0]->getYCoord(), 5);

     white[0]->setIsEaten(false);
     white[0]->setCoords(6, 1);
     board->changeGrid(6,1,2);
      board->changeGrid(2,5,1);

     black[0]->move(5, -5, black, white, board);
     QCOMPARE(white[0]->getIsEaten(), true);

     black[0]->unmove(black, white, board);


     white[0]->move(1, -1 , black, white, board);
     white[0]->move(-1, 1, black, white, board);
     black[0]->move(5, -5, black, white, board);

     QCOMPARE(white[0]->getIsEaten(), false);





}

void Test::testCase2()
{
    Board *board = new Board();
    QVector<Checker*> black;
    QVector<Checker*> white;
    black.resize(12);
    white.resize(12);

    for(int i = 0; i < 12; i++)
    {
        black[i] = new Checker();
        white[i] = new Checker();
        black[i]->setColor(BLACK);
        white[i]->setColor(WHITE);
        black[i]->setIsEaten(true);
        white[i]->setIsEaten(true);
    }

    board->changeGrid(6, 1, 1);
    black[0]->setCoords(6,1);
    black[0]->setIsEaten(false);
    board->changeGrid(4, 3, 1);
    black[1]->setCoords(4,3);
    black[1]->setIsEaten(false);

    white[0]->setCoords(3,4);
    white[0]->setIsEaten(false);
    board->changeGrid(3, 4, 2);

    white[0]->move(1, -1, black, white, board);
    if(white[0]->eatCombo(black, white, board))
    {
        white[0]->move(1, -1, black, white, board);
    }

    QCOMPARE(white[0]->getXCoord(), 7);
    QCOMPARE(white[0]->getYCoord(), 0);



}

void Test::testCase3()
{
    Board *board = new Board();
    QVector<Checker*> black;
    QVector<Checker*> white;
    black.resize(12);
    white.resize(12);
    AI*comp = new AI(2);

    for(int i = 0; i < 12; i++)
    {
        black[i] = new Checker();
        white[i] = new Checker();
        black[i]->setColor(BLACK);
        white[i]->setColor(WHITE);
        black[i]->setIsEaten(true);
        white[i]->setIsEaten(true);
    }

    board->changeGrid(6, 1, 2);
    white[0]->setCoords(6,1);
    white[0]->setIsEaten(false);
    board->changeGrid(4, 3, 2);
    white[1]->setCoords(4,3);
    white[1]->setIsEaten(false);
    board->changeGrid(3, 4, 2);
    white[2]->setCoords(3,4);
    white[2]->setIsEaten(false);
    board->changeGrid(4, 1, 1);
    black[2]->setCoords(4,1);
    black[2]->setIsEaten(false);
    board->changeGrid(6, 3, 2);
    white[3]->setCoords(6,3);
    white[3]->setIsEaten(false);
    board->changeGrid(7, 4, 1);
    black[1]->setCoords(7,4);
    black[1]->setIsEaten(false);

    board->changeGrid(3, 0, 2);
    white[4]->setCoords(3,0);
    white[4]->setIsEaten(false);

    board->changeGrid(5, 2, 2);
    black[0]->setCoords(5,2);
    black[0]->setIsEaten(false);

    Move move = comp->findBestMove(board, black, white, BLACK);

    black[move.pos]->move(move.x, move.y, black, white,board);

    QCOMPARE(black[move.pos]->getXCoord(), 7);
    QCOMPARE(black[move.pos]->getYCoord(), 0);

}

//QTEST_APPLESS_MAIN(UnitTest)

//#include "tst_unittest.moc"
