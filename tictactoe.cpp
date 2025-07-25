#include "tictactoe.h"
#include "ui_tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    for (short row = 0; row < 3; ++row) {
        for (short col = 0; col < 3; ++col) {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(row, col);

            if (item) {
                QWidget* widget = item->widget();

                if (QPushButton* button = qobject_cast<QPushButton*>(widget)) {
                    gameButtonsDict.insert(button, qMakePair(row, col));
                    allFields.append(button);

                    button->setStyleSheet(buttonsCSS);
                }
            }
        }
    }

    if(!allFields.isEmpty()){
        for(auto element : std::as_const(allFields)){
            connect(element, &QPushButton::clicked, this, &TicTacToe::on_pushButton_AnyField_clicked);
            element->setEnabled(false);
        }
    }

    avaliableFields = allFields;

}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::on_pushButtonBackToMenu_clicked()
{
    close();
}


void TicTacToe::on_pushButtonStartGame_clicked()
{
    //Restart fields
    avaliableFields = allFields;

    //Restart table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            gameTable[i][j] = 0;

    for(auto field : allFields){
        field->setEnabled(true);
        field->setText(QString(""));
    }

    //Set first player
    isPlayerStart = QRandomGenerator::global()->bounded(2);

    if(!isPlayerStart){
        playerSymbol = 'X';
        opponentSymbol = 'O';

        opponentSelect();
    }
    else{
        playerSymbol = 'O';
        opponentSymbol = 'X';
    }

    //Game is continous flag
    isGameContinue = true;

    //Change Start Game Button to Restart Game Button
    ui->pushButtonStartGame->setText("Restart Game");
}

void TicTacToe::opponentSelect(){
    if(!avaliableFields.isEmpty()){

        //Select random button
        int index = QRandomGenerator::global()->bounded(avaliableFields.size());
        QPushButton* fieldButton = avaliableFields[index];

        //Set this button as selected
        fieldButton->setText(QString(opponentSymbol));
        fieldButton->setEnabled(false);

        //Remove button from avaliable to click buttons
        avaliableFields.removeOne(fieldButton);

        //Set this to game table
        gameTableValueSet(fieldButton, false);
    }
}

void TicTacToe::checkWin(){

    // win value if 1 player won if -1 enemy won
    int whoWin = 0;

    // Check win
    // rows
    for(int i = 0; i < 3; i++){
        if(gameTable[i][0]==gameTable[i][1] && gameTable[i][1]==gameTable[i][2] && gameTable[i][0]!=0){
            whoWin = gameTable[i][0];
            break;
        }
    }

    // columns
    for(int i = 0; i < 3; i++){
        if(gameTable[0][i]==gameTable[1][i] && gameTable[1][i]==gameTable[2][i] && gameTable[0][i]!=0){
            whoWin = gameTable[0][i];
            break;
        }
    }

    // 1st daigonal
    if(gameTable[0][0]==gameTable[1][1] && gameTable[1][1]==gameTable[2][2] && gameTable[0][0]!=0)
    {
        whoWin = gameTable[0][0];
    }

    // 2nd diagonal
    if(gameTable[0][2]==gameTable[1][1] && gameTable[1][1]==gameTable[2][0] && gameTable[0][2]!=0)
    {
        whoWin = gameTable[0][2];
    }

    // Won Result
    if(whoWin == 1){
        isGameContinue = false;
        ui->pushButtonStartGame->setText("Start Game");

        QMessageBox::information(this, "Game result", "Won");

        QString old_history = ui->labelGamesHistory->text();
        ui->labelGamesHistory->setText(old_history + "Won\n");
    }
    else if(whoWin == -1){
        isGameContinue = false;
        ui->pushButtonStartGame->setText("Start Game");

        QMessageBox::information(this, "Game result", "Loose");

        QString old_history = ui->labelGamesHistory->text();
        ui->labelGamesHistory->setText(old_history + "Loose\n");
    }


    if(avaliableFields.isEmpty() && whoWin == 0){
        isGameContinue = false;
        ui->pushButtonStartGame->setText("Start Game");

        QMessageBox::information(this, "Game result", "Draw");

        QString old_history = ui->labelGamesHistory->text();
        ui->labelGamesHistory->setText(old_history + "Draw\n");
    }

    for(int i = 0; i < 3; i++){

        qDebug() << gameTable[i][0] << gameTable[i][1] << gameTable[i][2];

    }
    qDebug() << "\nResult";
    qDebug() << whoWin;
}

void TicTacToe::on_pushButton_AnyField_clicked(){
    //get button from sender
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if(isGameContinue){
        //Set this button as selected
        clickedButton->setText(QString(playerSymbol));
        clickedButton->setEnabled(false);

        //Remove button from avaliable to click buttons
        avaliableFields.removeOne(clickedButton);

        //Set this to game table
        gameTableValueSet(clickedButton, true);

        //Check if player win
        checkWin();

        //Start opponent turn and check if win
        if(isGameContinue){
            opponentSelect();
            checkWin();
        }
    }
}

void TicTacToe::gameTableValueSet(QPushButton *button, bool isPlayerTurn){
    if (!gameButtonsDict.contains(button))
        return;

    QPair<short, short> pair = gameButtonsDict[button];
    short row = pair.first;
    short col = pair.second;

    gameTable[row][col] = isPlayerTurn ? 1 : -1;
}
