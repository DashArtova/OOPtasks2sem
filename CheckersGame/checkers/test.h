#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QtTest>
#include <QWidget>
#include "checker.h"
#include "ai.h"
#include "board.h"
#include "mainwindow.h"


class Test : public QObject
{
    Q_OBJECT

public:
    Test();

private Q_SLOTS:
    void testCase1();
    void testCase2();
    void testCase3();
};

#endif // TEST_H
