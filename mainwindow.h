#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablemodel.h"
#include "graphwindow.h"

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
    void getTableContent(vector<vector<double> > &arr) const;

private slots:
    void on_pushButton_clicked();

    void on_graph_button_clicked();

private:
    Ui::MainWindow *ui;
    GraphWindow *gr;
    myTableModel *tabModel;
};

#endif // MAINWINDOW_H
