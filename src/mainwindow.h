#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_dodaj_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString start = "G54\nF100000\n";
    QString end = "G0 M93\nG53 X0 Y0 C=0 G90 G0\nM1\nMSG()\nM30\n";
};
#endif // MAINWINDOW_H
