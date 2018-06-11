#include "mainwindow.h"
#include "board.h"
#include "game.h"
#include "test.h"
//#include "Tests/unitTest/tst_unittest.cpp"

#include <QApplication>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QtTest/Qtest>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //freopen("testing.log", "w", stdout);
    MainWindow w;
    //QTest::qExec(new Test, argc, argv);
    w.show();
    // Game *game = new Game();
    // game->show();


    /*QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsRectItem * rect = new QGraphicsRectItem();
    rect->setRect(100,100,100, 100);
    scene->addItem(rect);
    QGraphicsView * view = new QGraphicsView(scene);
    view->show();*/
    QTest::qExec(new Test, argc, argv);
    return a.exec();
}
