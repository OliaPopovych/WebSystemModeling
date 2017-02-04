#include "startwindow.h"
#include "ui_startwindow.h"
//#include "mainwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButton_clicked()
{
    w->close();
    w = new MainWindow;
    w->show();
}
