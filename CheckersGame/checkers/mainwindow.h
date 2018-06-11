#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QVector>
#include <QPair>
#include <QPointer>
#include "board.h"
#include "checker.h"
#include "ai.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void updateBoard();

private:
    Ui::MainWindow *ui;
    QVector<QLabel *> blackLab;
    QVector<QLabel *> whiteLab;
    QVector <Checker *> black;
    QVector <Checker *> white;
    Board * board;
    QPair<int, int> curr;
    bool isClicked = false;
    Move move;
    AI *comp;

};

#endif // MAINWINDOW_H
