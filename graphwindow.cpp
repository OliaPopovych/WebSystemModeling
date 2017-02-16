#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(vector<vector<double> >& arr, vector<double> &lamb, int numOfSystems, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    params.resize(arr.size());
    params.shrink_to_fit();
numOfSystems--;
    for(int i=0, j=0; i < params.size(); i++){
        if(j+i >= params.size())
            j=0;
        params[i].resize(arr[0].size());
        //for(int j =0; j < params.size() - numOfSystems; j++)
           params[i] = arr[i + j];
           j += numOfSystems;
    }
    /*int i = 0;
    while(i < params.size()){
        for(int j = 0; j < params.size(); j += numOfSystems){
            params[i] = arr[i + j];
            i++;
        }
    }*/

    this->lamb = lamb;
}



GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::drawCharts()
{
    vector<double> all;
    vector<double> single;
    all.resize(params.size());
    //for()
}

void GraphWindow::drawChart(QString name, vector<double> &row)
{
    QBarSet *set = new QBarSet(name);

    // znesty v set

    QBarSeries *series = new QBarSeries();
    series->append(set);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();
    chart->legend()->setAlignment(Qt::AlignBottom);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView,0,0);
}
