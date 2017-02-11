#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   // explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(vector<vector<double>>& arr, QWidget *parent = 0);
    ~MainWindow();

    // заповнимо TableWidget стандартними V
    void fillContentFromWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    myTableModel *tabModel;
};

#endif // MAINWINDOW_H
