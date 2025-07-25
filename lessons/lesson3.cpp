#include "lesson3.h"
#include "ui_lesson3.h"

Lesson3::Lesson3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lesson3)
{
    ui->setupUi(this);

    personalitiesRadioGroup = new QButtonGroup(this);
    personalitiesRadioGroup->addButton(ui->radioButtonPersonality_1);
    personalitiesRadioGroup->addButton(ui->radioButtonPersonality_2);
    personalitiesRadioGroup->addButton(ui->radioButtonPersonality_3);

    sexRadioGroup = new QButtonGroup(this);
    sexRadioGroup->addButton(ui->radioButtonSex_1);
    sexRadioGroup->addButton(ui->radioButtonSex_2);

    model = new UserL3Model();
    ui->tableViewMain->setModel(model);
}

Lesson3::~Lesson3()
{
    delete ui;
}

void Lesson3::on_buttonBoxAcceptReject_accepted()
{
    QString name = ui->lineEditName->text();
    QString email = ui->lineEditEmail->text();
    QString description = ui->plainTextEditDescription->toPlainText();
    QDate birth_day = ui->dateEditBirthDay->date();
    int preffered_salary = ui->spinBoxSalary->value();
    QString sex = sexRadioGroup->checkedButton()->isChecked() ?
                    sexRadioGroup->checkedButton()->text() : " ";
    QString personality = personalitiesRadioGroup->checkedButton()->isChecked() ?
                    personalitiesRadioGroup->checkedButton()->text() : " ";


    UserL3 user(name, email, description, birth_day, preffered_salary, sex, personality, "");

    model->addUser(user);
}


void Lesson3::on_buttonBoxAcceptReject_rejected()
{
    ui->lineEditName->clear();
    ui->lineEditEmail->clear();
    ui->plainTextEditDescription->clear();
    ui->dateEditBirthDay->clear();
    ui->spinBoxSalary->minimum();


    //clear all
}

