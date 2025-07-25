#include "lesson4.h"
#include "ui_lesson4.h"

Lesson4::Lesson4(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lesson4)
{
    ui->setupUi(this);

    // Connect to Database
    database = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    database->setPort(5477);
    database->setHostName("localhost");
    database->setDatabaseName("QtDb");
    database->setUserName("postgres");
    database->setPassword("zaq1@WSX");
    bool ok = database->open();

    // Check connection
    if(ok){
        qWarning() << "Database connect was successful";

        model = new QSqlTableModel;
        model->setTable("qtable");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        qWarning() << model->rowCount();

        if(model->lastError().isValid()){
            qDebug() << "ERROR:" << model->lastError().text();
        }

        ui->tableView->setModel(model);
        ui->tableView->hideColumn(0);
    }
    else{
        //Errors print
        qWarning() << "Database connect was unsuccessful";
        qDebug() << "Error:" << database->lastError().text();
    }
}

Lesson4::~Lesson4()
{
    delete ui;
}

void Lesson4::on_pushButtonSelectColor_clicked()
{
    //Select color on button and change text to HEX

    QColor color = QColorDialog::getColor(Qt::white, this, "Select color");

    if(color.isValid()){
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        QString rgbText = color.toRgb().name();
        clickedButton->setText(rgbText);
    }
}

void Lesson4::on_verticalSlider_valueChanged(int value)
{
    //Display size as a x b when slider was changed

    boxSize.second = value;

    QString text;
    QTextStream(&text) << boxSize.first << " x " << boxSize.second;

    ui->labelSizePresentation->setText(text);
}


void Lesson4::on_horizontalSlider_valueChanged(int value)
{
    //Display size as a x b when slider was changed

    boxSize.first = value;

    QString text;
    QTextStream(&text) << boxSize.first << " x " << boxSize.second;

    ui->labelSizePresentation->setText(text);
}


void Lesson4::on_pushButtonAdd_clicked()
{
    // Take arguments from fields
    QString name = ui->lineEdit->text();
    int code = ui->spinBox->value();
    int y = ui->verticalSlider->value();
    int x = ui->horizontalSlider->value();
    int area = x * y;
    QString color = ui->pushButtonSelectColor->text();
    QDate date = QDate::currentDate();

    // Add row
    int newRow = model->rowCount();
    model->insertRow(newRow);

    // Input arguments
    model->setData(model->index(newRow, 1), name);
    model->setData(model->index(newRow, 2), code);
    model->setData(model->index(newRow, 3), color);
    model->setData(model->index(newRow, 4), date);
    model->setData(model->index(newRow, 5), area);

    // Check if submit sucess
    if (!model->submitAll()) {
        QMessageBox::critical(this, "Error", "Insert data error: " + model->lastError().text());
        model->removeRow(newRow);
        model->submitAll();
    } else {

        // Success
        QMessageBox::information(this, "OK", "Data added successfuly");

        // Reset fields
        ui->lineEdit->setText("");
        ui->spinBox->setValue(1);
        ui->verticalSlider->setValue(0);
        ui->horizontalSlider->setValue(0);
        ui->pushButtonSelectColor->setText("Pick color");
    }
}


void Lesson4::on_pushButtonDelete_clicked()
{
    //Remove at index

    int index = ui->spinBoxDeleteIndex->value() - 1; //to compare with table indexing

    model->removeRow(index);

    if(model->submitAll() && index < model->rowCount()){
        QMessageBox::information(this, "Data deleted", "Data deleted successfuly");
    }
    else if(index > model->rowCount()){
        QMessageBox::critical(this, "Error", "Data delete error: index out of range");
    }
    else{
        QMessageBox::critical(this, "Error", "Data delete error: " + model->lastError().text());
    }
}

