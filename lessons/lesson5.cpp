#include "lesson5.h"
#include "ui_lesson5.h"
#include <qevent.h>
#include <qmessagebox.h>

Lesson5::Lesson5(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lesson5)
{
    ui->setupUi(this);

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    ui->pushButton_result->setStyleSheet(cssResultButton);

    QList<QPushButton*> digitButtons = {
        ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
        ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
        ui->pushButton_6, ui->pushButton_7, ui->pushButton_8,
        ui->pushButton_9
    };

    for (auto button : digitButtons) {
        connect(button, &QPushButton::clicked, this, &Lesson5::onDigitButtonClicked);
    }

    connect(ui->pushButton_add, &QPushButton::clicked, this, &Lesson5::onOperatorButtonClicked);
    connect(ui->pushButton_sub, &QPushButton::clicked, this, &Lesson5::onOperatorButtonClicked);
    connect(ui->pushButton_mul, &QPushButton::clicked, this, &Lesson5::onOperatorButtonClicked);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &Lesson5::onOperatorButtonClicked);

    if (component_values_list.isEmpty()){
        component_values_list.append(0);
    }

}

Lesson5::~Lesson5()
{
    delete ui;
}

void Lesson5::onDigitButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    int value = clickedButton->text().toInt();

    if (component_values_list.isEmpty())
        component_values_list.append(0);

    component_values_list[actual_component_index] = component_values_list[actual_component_index] * 10 + value;
    ui->lcdNumber->display(component_values_list[actual_component_index]);
}

void Lesson5::onOperatorButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString op = clickedButton->text();
    Action currentAction = Action::None;

    // Select action depends on string
    if (op == "+") currentAction = Action::Add;
    else if (op == "-") currentAction = Action::Sub;
    else if (op == "*") currentAction = Action::Mul;
    else if (op == "/") currentAction = Action::Div;

    // Save action
    actions_to_values_list.append(currentAction);

    actual_component_index++;

    // If two operands then calculate
    if (component_values_list.size() >= 2 && actions_to_values_list.size() >= 1) {
        int a = component_values_list[component_values_list.size() - 2];
        int b = component_values_list[component_values_list.size() - 1];
        Action action = actions_to_values_list.last();

        switch (action) {
        case Action::Add: result_value = a + b; break;
        case Action::Sub: result_value = a - b; break;
        case Action::Mul: result_value = a * b; break;
        case Action::Div:
            if (b == 0) {
                QMessageBox::critical(this, "Division Error", "You can't divide by 0!");
                component_values_list[actual_component_index] = 0;
                return;
            }
            result_value = a / b;
            break;
        default: break;
        }

        ui->lcdNumber->display(result_value);
    }

    // Add new operand
    component_values_list.append(0);
}

void Lesson5::on_pushButton_C_clicked() {
    //Clear value and index
    result_value = 0;
    actual_component_index = 0;

    // Clear lists
    component_values_list.clear();
    actions_to_values_list.clear();

    // Add empty operand and display
    component_values_list.append(0);
    ui->lcdNumber->display(result_value);
}

void Lesson5::on_pushButton_del_clicked() {
    // Remove last digit from number
    if (!component_values_list.isEmpty()) {
        int val = component_values_list.takeLast();
        val /= 10;
        component_values_list.append(val);
        ui->lcdNumber->display(val);
    }
}

void Lesson5::on_pushButton_plus_minus_clicked() {
    // Swap sign of number
    if (!component_values_list.isEmpty()) {
        int val = component_values_list.takeLast();
        val *= -1;
        component_values_list.append(val);
        ui->lcdNumber->display(val);
    }
}

// Key press on keyboard
void Lesson5::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_0:
        ui->pushButton_0->click(); break;
    case Qt::Key_1:
        ui->pushButton_1->click(); break;
    case Qt::Key_2:
        ui->pushButton_2->click(); break;
    case Qt::Key_3:
        ui->pushButton_3->click(); break;
    case Qt::Key_4:
        ui->pushButton_4->click(); break;
    case Qt::Key_5:
        ui->pushButton_5->click(); break;
    case Qt::Key_6:
        ui->pushButton_6->click(); break;
    case Qt::Key_7:
        ui->pushButton_7->click(); break;
    case Qt::Key_8:
        ui->pushButton_8->click(); break;
    case Qt::Key_9:
        ui->pushButton_9->click(); break;

    case Qt::Key_Plus:
        ui->pushButton_add->click(); break;
    case Qt::Key_Minus:
        ui->pushButton_sub->click(); break;
    case Qt::Key_Asterisk:
        ui->pushButton_mul->click(); break;
    case Qt::Key_Backslash:
        ui->pushButton_div->click(); break;

    case Qt::Key_Equal:
        ui->pushButton_result->click(); break;

    default:
        QDialog::keyPressEvent(event);
        break;
    }
}

// Execute result
void Lesson5::on_pushButton_result_clicked()
{
    if (component_values_list.size() < 2 || actions_to_values_list.isEmpty())
        return;

    result_value = component_values_list[0];

    for (int i = 1; i < component_values_list.size(); ++i) {
        Action action = actions_to_values_list.value(i - 1);
        int operand = component_values_list[i];

        switch (action) {
        case Action::Add:
            result_value += operand;
            break;
        case Action::Sub:
            result_value -= operand;
            break;
        case Action::Mul:
            result_value *= operand;
            break;
        case Action::Div:
            if (operand == 0) {
                QMessageBox::critical(this, "Division Error", "You can't divide by 0!");
                return;
            }
            result_value /= operand;
            break;
        case Action::None:
            break;
        }
    }

    ui->lcdNumber->display(result_value);

    component_values_list.clear();
    actions_to_values_list.clear();
    actual_component_index = 0;
    component_values_list.append(result_value);
}

