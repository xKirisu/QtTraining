#include "lesson2.h"
#include "ui_lesson2.h"

Lesson2::Lesson2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lesson2)
{
    ui->setupUi(this);
}

Lesson2::~Lesson2()
{
    delete ui;
}

void Lesson2::on_pushButtonSelectFilePath_clicked()
{
    // Get filepath and put it to top line (lineEditFilePath)
    QString fileName = QFileDialog::getOpenFileName(this, "Open a File", QDir::currentPath(), "Text (*.txt);; Markdown (*.md);; Comma Separated (*.csv);; All (*.*)");

    ui->lineEditFilePath->setText(fileName);
}


void Lesson2::on_pushButtonOpenFilePath_clicked()
{
    // Open file from top line (lineEditFilePath)

    QString path = ui->lineEditFilePath->text();

    QFile file(path);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        ui->labelOpenedFile->setText("Opened file: " + path);

        QTextStream get_content(&file);
        QString content = get_content.readAll();
        ui->plainTextMain->setPlainText(content);

        QMessageBox::information(this, "File was opened", "File was opened successfully");

        file.close();
    }
    else{
        QMessageBox::warning(this, "Wrong file", "Can not open file");
    }
}


void Lesson2::on_pushButtonExportPDF_clicked()
{
    // Export text to pdf file

    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");

    if(fileName.isEmpty()) return;

    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QString content = ui->plainTextMain->toPlainText();

    QTextDocument doc;
    doc.setHtml(content);
    doc.print(&printer);

    QMessageBox::information(this, "PDF Saved", "File has been successfully saved as PDF.");
}


void Lesson2::on_pushButtonSaveAsExisting_clicked()
{
    // Save to opened file

    QString path = ui->labelOpenedFile->text().split(' ')[2];

    QFile file(path);

    qDebug()<<path;

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << ui->plainTextMain->toPlainText();

        file.close();

        QMessageBox::information(this, "Saved", "Data was saved in new file");

    } else {

        QMessageBox::warning(this, "Error", "Can not save file");
    }
}


void Lesson2::on_pushButtonSaveAsNew_clicked()
{
    // Save as new file

    QString fileName = QFileDialog::getSaveFileName(this, "Save as new", "", "Text file (*.txt)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream out(&file);
        out << ui->plainTextMain->toPlainText();

        file.close();

        QMessageBox::information(this, "Saved", "Data was saved in new file");

    } else {

        QMessageBox::warning(this, "Error", "Can not save file");

    }
}


void Lesson2::on_pushButtonClear_clicked()
{
    // Clear text

    ui->plainTextMain->clear();
}

