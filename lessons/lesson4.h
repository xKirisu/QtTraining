#ifndef LESSON4_H
#define LESSON4_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QColorDialog>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QVector2D>
#include <QDate>
#include <QMessageBox>

namespace Ui {
class Lesson4;
}

class Lesson4 : public QDialog
{
    Q_OBJECT

public:
    explicit Lesson4(QWidget *parent = nullptr);
    ~Lesson4();

private slots:
    void on_pushButtonSelectColor_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::Lesson4 *ui;
    QSqlDatabase *database;
    QSqlTableModel* model;

    QPair<short, short> boxSize;
};

#endif // LESSON4_H
