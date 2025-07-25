#ifndef LESSON5_H
#define LESSON5_H

#include <QDialog>
#include <QStyleFactory>

namespace Ui {
class Lesson5;
}

class Lesson5 : public QDialog
{
    Q_OBJECT

public:
    explicit Lesson5(QWidget *parent = nullptr);
    ~Lesson5();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onDigitButtonClicked();
    void onOperatorButtonClicked();
    void on_pushButton_C_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_plus_minus_clicked();

    void on_pushButton_result_clicked();

private:
    enum class Action { None, Add, Sub, Mul, Div };

    Ui::Lesson5 *ui;

    QVector<int> component_values_list;
    QVector<Action> actions_to_values_list;

    int actual_component_index = 0;
    int result_value = 0;
    Action action = Action::None;

    // style to remove hover coloring
    QString cssResultButton = R"(
        #pushButton_result {
            background-color: #a20000;
            color: #ffffff;
            font-size: 16px;
            font-weight: bold;
        }
    )";

};

#endif // LESSON5_H
