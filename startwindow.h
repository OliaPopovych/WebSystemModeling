#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

    void getTableContent(vector<vector<double>>& arr) const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::StartWindow *ui;
    MainWindow *w;
};

#endif // STARTWINDOW_H
