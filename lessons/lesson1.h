#ifndef LESSON1_H
#define LESSON1_H

#include <QDialog>
#include <QVector>
#include <QMessageBox>

namespace Ui {
class Lesson1;
}

class Lesson1 : public QDialog
{
    Q_OBJECT

public:
    explicit Lesson1(QWidget *parent = nullptr);
    ~Lesson1();

private slots:
    void on_pushButtonAlert_clicked();

    void on_pushButtonClearList_clicked();

    void on_pushButtonList_clicked();

    void on_pushButtonDisplayPersentage_clicked();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::Lesson1 *ui;
};

#endif // LESSON1_H
