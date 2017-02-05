#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(vector<vector<double> > &arr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // створюємо модель і присвоюємо її tableView
    tabModel = new myTableModel(arr);
    ui->tableView->setModel(tabModel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabModel;
}
