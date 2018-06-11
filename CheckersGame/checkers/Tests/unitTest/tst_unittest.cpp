#include <QString>
#include <QtTest>
#include <QWidget>

#include "../../ai.h"
#include "../../checker.h"
#include "../../board.h"

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:
    void testCase1();
};

UnitTest::UnitTest()
{
}

void UnitTest::testCase1()
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
}

//QTEST_APPLESS_MAIN(UnitTest)

//#include "tst_unittest.moc"
