#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <QPair>
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
        QPair<QString, QString> pairDim;
        pairDim.first = ui->le_dimOne->text();
        pairDim.second = ui->le_dimTwo->text();
        dimensionPairs.push_back(pairDim);

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

        // for one rectangle
        // actual cutting gcode goes here

        // TODO check dali nozho na 0 e svrten po X ili po Y na pocetok
        out << "G0 M93 C=0.00\n";
        out << "G0 X" + dimensionPairs[0].first + "Y0\n";
        out << "G0 M93 C=90.00\n";
        out << "G0 X" + dimensionPairs[0].first + "Y" + dimensionPairs[0].second + "\n";
        out << "G0 M93 C=0.00\n";
        out << "G0 X0Y" + dimensionPairs[0].second + "\n";
        out << "G0 M93 C=90.00\n";
        out << "G0 X0Y0\n";

        out << end;

        file.close();

        QMessageBox success;
        success.setWindowTitle("Uspesno");
        success.setText("Kodot bese uspesno generiran.");
        success.exec();
    }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Greska");
        error.setText("Nema vneseno dimenzii.");
        error.exec();
    }
}

void MainWindow::on_pb_izbrisi_clicked()
{
    if(ui->le_eraseNum->text() != "")
    {
        QVector<QPair<QString, QString>>::iterator it = dimensionPairs.begin();
        if (ui->le_eraseNum->text().toInt() <= dimensionPairs.size())
        {
            dimensionPairs.erase(it + (ui->le_eraseNum->text().toInt() - 1));
            ui->te_dimenzii->clear();
            ui->le_eraseNum->clear();

            for(int i=0; i<dimensionPairs.size(); i++)
            {
                if(i == 0)
                {
                    ui->te_dimenzii->setText("Visina: " + dimensionPairs[i].first + "mm Shirina: " + dimensionPairs[i].second + "mm");
                }
                else
                {
                    ui->te_dimenzii->setText(ui->te_dimenzii->toPlainText() + "\nVisina: " + dimensionPairs[i].first + "mm Shirina: " + dimensionPairs[i].second + "mm");
                }
            }
        }
        else
        {
            QMessageBox error;
            error.setWindowTitle("Greska");
            error.setText("Vneseniot element ne postoi.");
            error.exec();
        }
    }
    else
    {
        QMessageBox error;
        error.setWindowTitle("Greska");
        error.setText("Nema vneseno broj na par dimenzii za brisenje.");
        error.exec();
    }
}
