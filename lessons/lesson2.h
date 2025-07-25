#ifndef LESSON2_H
#define LESSON2_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QPrinter>

namespace Ui {
class Lesson2;
}

class Lesson2 : public QDialog
{
    Q_OBJECT

public:
    explicit Lesson2(QWidget *parent = nullptr);
    ~Lesson2();

private slots:
    void on_pushButtonSelectFilePath_clicked();

    void on_pushButtonOpenFilePath_clicked();

    void on_pushButtonExportPDF_clicked();

    void on_pushButtonSaveAsExisting_clicked();

    void on_pushButtonSaveAsNew_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::Lesson2 *ui;
};

#endif // LESSON2_H
