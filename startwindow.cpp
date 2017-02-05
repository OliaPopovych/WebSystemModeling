#include "startwindow.h"
#include "ui_startwindow.h"

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
//натиснули ОК
void StartWindow::on_pushButton_clicked()
{
    w->close();

    // створюємо масив матриці ймовірностей
    vector<vector<double>> arr;
    arr.reserve(50);

    getTableContent(arr);
    // матрицю ймовірностей передаємо у модель вікна w
    w = new MainWindow(arr);
    w->show();
}
//натиснули +
void StartWindow::on_pushButton_2_clicked()
{
    int kst = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(kst);
    QString str = "S" + QString::number(kst);
    ui->tableWidget->setVerticalHeaderItem(kst, new QTableWidgetItem(str));

    ui->tableWidget->insertColumn(kst);
    ui->tableWidget->setHorizontalHeaderItem(kst, new QTableWidgetItem(str));

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}
//натиснули -
void StartWindow::on_pushButton_3_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    ui->tableWidget->removeColumn(ui->tableWidget->columnCount()-1);
}

void StartWindow::getTableContent(vector<vector<double>>& arr) const
{
    int size = ui->tableWidget->rowCount();
    arr.resize(size);
    for(int i=0; i < size; i++){
        arr[i].resize(size);
        for(int j=0; j < size; j++){
            arr[i][j] = ui->tableWidget->item(i,j)->text().toDouble();
        }
    }
}

