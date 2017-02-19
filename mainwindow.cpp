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

    ui->tableView->setStyleSheet("QHeaderView::section { background-color:QColor(0,0,190) }");

    for(int i=1; i < tabModel->getProbMatSize(); i++){
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
        QString str = "V" + QString::number(i);
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(str));
    }
    // QT чомусь не вставляє спершу рядки а потім колонки
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->verticalHeader()->setVisible(false);

    fillContentFromWidget();

    ui->tableWidget->resizeColumnsToContents();

}

void MainWindow::fillContentFromWidget()
{
    // нам відомий розмір, скористаємось стаціонарним масивом
    double arr[] = { 0.3, 0.2, 0.2, 0.1};
    // double arr[] = { 0.5, 0.4, 0.3, 0.3, 0.1, 0.1 };
    QTableWidgetItem *item;
    // не спрацює. Для кожної комірки треба свій QTableWidgetItem
   // item = new QTableWidgetItem();

    for(int i = 0; i < 6; i++){
        item = new QTableWidgetItem();
        item->setText(QString::number(arr[i]));
        ui->tableWidget->setItem(0, i, item);
    }

    ui->doubleSpinBox_2->setValue(0.5);
    ui->doubleSpinBox->setValue(0.9);
    ui->doubleSpinBox_3->setValue(0.05);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabModel;
}
// натиснули "Обчислити"
void MainWindow::on_pushButton_clicked()
{
    // заповнюємо цю всю лабуду в моделі
    vector<double> arr;
    arr.resize(ui->tableWidget->columnCount());
    int i= 0;
    for(auto it = arr.begin(); it < arr.end(); it++, i++){
        *it = ui->tableWidget->item(0,i)->text().toDouble();
    }

    tabModel->setAvgServTime(arr);
    tabModel->setMinMaxLamb(ui->doubleSpinBox_2->value(), ui->doubleSpinBox->value());
    tabModel->setDeltaLamb(ui->doubleSpinBox_3->value());

    tabModel->findSystemParams();

    ui->tableView->resizeRowsToContents();

    ui->graph_button->setEnabled(true);
}

void MainWindow::on_graph_button_clicked()
{
    gr = new GraphWindow(tabModel->getParamsTable(), tabModel->getLamb(), tabModel->getProbMatSize() - 1);
    gr->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            gr->size(),
            qApp->desktop()->availableGeometry()
        )
    );
    gr->show();
}

