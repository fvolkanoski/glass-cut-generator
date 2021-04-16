#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_dodaj_clicked()
{
    if(ui->le_dimOne->text() != "" && ui->le_dimTwo->text() != "")
    {
        if(ui->te_dimenzii->toPlainText() == "")
        {
            ui->te_dimenzii->setText("Visina: " + ui->le_dimOne->text() + "mm Shirina: " + ui->le_dimTwo->text() + "mm");
        }
        else
        {
            ui->te_dimenzii->setText(ui->te_dimenzii->toPlainText() + "\nVisina: " + ui->le_dimOne->text() + "mm Shirina: " + ui->le_dimTwo->text() + "mm");
        }
    }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Greska");
        error.setText("Nema dimenzii.");
        error.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->te_dimenzii->toPlainText() != "")
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Odberi kade da se zacuva"), "C:/", tr("Kod fajlovi (*.mpf *.MPF)"));
        qDebug() << fileName;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
               return;

        QTextStream out(&file);
        out << start;

        // actual cutting gcode goes here.

        out << end;

        file.close();
    }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Greska");
        error.setText("Nema dimenzii.");
        error.exec();
    }
}
