#include "lesson1.h"
#include "ui_lesson1.h"

Lesson1::Lesson1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lesson1)
{
    ui->setupUi(this);

    //Dodać info w komendach
}

Lesson1::~Lesson1()
{
    delete ui;
}

void Lesson1::on_pushButtonAlert_clicked()
{
    if(ui->labelTextToClear->text().isEmpty()){
        QMessageBox::information(this, "Text back", "Text to Clear back to Label");
    }

    ui->labelTextToClear->setText("Text to Clear");
}


void Lesson1::on_pushButtonClearList_clicked()
{
    if(!ui->labelList->text().isEmpty()){
        QMessageBox::warning(this, "List cleared", "List cleared irreversibly");
    }

    ui->labelList->setText(QString());
}


void Lesson1::on_pushButtonList_clicked()
{
    QString text_new = ui->lineEditList->text() + '\n';

    if(text_new.length() > 1){

        QString text_old = ui->labelList->text();

        ui->labelList->setText(text_new + text_old);

        ui->lineEditList->clear();

    }
}


void Lesson1::on_pushButtonDisplayPersentage_clicked()
{
    QString value = ui->labeSliderPersentage->text();
    QString message("Persentage is "+ value);
    QMessageBox::about(this, "Persentage", message);
}


void Lesson1::on_verticalSlider_valueChanged(int value)
{
    QString string_value = QString::number(value) + "%";
    ui->labeSliderPersentage->setText(string_value);
}

