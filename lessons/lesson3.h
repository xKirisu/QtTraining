#ifndef LESSON3_H
#define LESSON3_H

#include "models/userl3model.h"
#include <QDialog>
#include <QStandardItem>
#include <QButtonGroup>

namespace Ui {
class Lesson3;
}

class Lesson3 : public QDialog
{
    Q_OBJECT

public:
    explicit Lesson3(QWidget *parent = nullptr);
    ~Lesson3();

private slots:
    void on_buttonBoxAcceptReject_accepted();

    void on_buttonBoxAcceptReject_rejected();

private:
    Ui::Lesson3 *ui;
    UserL3Model *model;

    QButtonGroup *personalitiesRadioGroup;
    QButtonGroup *sexRadioGroup;
};

#endif // LESSON3_H
