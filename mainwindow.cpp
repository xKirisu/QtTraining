#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    lesson1 = new Lesson1(this);
    lesson1->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    lesson2 = new Lesson2(this);
    lesson2->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    lesson3 = new Lesson3(this);
    lesson3->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    lesson4 = new Lesson4(this);
    lesson4->show();
}


void MainWindow::on_pushButton_5_clicked()
{
    lesson5 = new Lesson5(this);
    lesson5->show();
}

void MainWindow::on_pushButtonOpenTicTacToe_clicked()
{
    hide();
    tictactoe = new TicTacToe(this);
    tictactoe->exec();
    show();
}

