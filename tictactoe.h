#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QDialog>
#include <QPushButton>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QStyleFactory>

namespace Ui {
class TicTacToe;
}

class TicTacToe : public QDialog
{
    Q_OBJECT

public:
    explicit TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    void on_pushButtonBackToMenu_clicked();

    void on_pushButtonStartGame_clicked();

    void on_pushButton_AnyField_clicked();

private:
    Ui::TicTacToe *ui;

    // Styles to remove hover colors
    QString buttonsCSS = R"(
        QPushButton {
            background-color: rgb(89, 89, 89);
            color: rgb(255, 255, 255);
        }
    )";

    //Game elements
    // player is O
    bool isGameContinue = false;
    bool isPlayerStart = false;

    QMap<QPushButton*, QPair<short, short>> gameButtonsDict;
    short gameTable[3][3] = {0};

    QChar playerSymbol;
    QChar opponentSymbol;

    QList<QPushButton*> allFields;
    QList<QPushButton*> avaliableFields;

    void opponentSelect();
    void checkWin();

    void gameTableValueSet(QPushButton* button, bool isPlayerTurn);
};

#endif // TICTACTOE_H
