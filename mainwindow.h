#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lessons/lesson1.h"
#include "lessons/lesson2.h"
#include "lessons/lesson3.h"
#include "lessons/lesson4.h"
#include "lessons/lesson5.h"
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButtonOpenTicTacToe_clicked();

private:
    Ui::MainWindow *ui;

    Lesson1 *lesson1;
    Lesson2 *lesson2;
    Lesson3 *lesson3;
    Lesson4 *lesson4;
    Lesson5 *lesson5;

    TicTacToe *tictactoe;

};
#endif // MAINWINDOW_H
