#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QtCharts>

#include "tablemodel.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit GraphWindow(vector<vector<double>> &arr, QWidget *parent = 0);
    explicit GraphWindow(vector<vector<double> > &arr, vector<double>& lamb, int numOfSystems, QWidget *parent = 0);
    ~GraphWindow();

protected:
    void drawChart(QString name, vector<double> &row);
    void drawCharts();

private:
    Ui::GraphWindow *ui;
    vector<vector<double>> params;
    vector<double> lamb;
};

#endif // GRAPHWINDOW_H
