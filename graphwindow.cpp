#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(vector<vector<double> >& arr, vector<double> &lamb, int numOfSystems, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    this->numOfSystems = numOfSystems;

    params.resize(arr.size());

    for(int m = 0, i=0, j=0, k=0; i < params.size(); i++, k++){
        if(k+j >= params.size()){
            j = ++m;
            k = 0;
        }
        params[i].resize(arr[0].size());
        params[i] = arr[k + j];
        j += numOfSystems;
    }

    this->lamb = lamb;

    drawCharts();
}



GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::drawCharts()
{
    vector<vector<double>> vec;
    vec.resize(lamb.size());
    int curSys = 1;

    QGridLayout *gridLayout = new QGridLayout;
    QWidget *wid = new QWidget();
    wid->setLayout(gridLayout);
    ui->scrollArea->setWidget(wid);

    for(auto it = vec.begin(); it < vec.end(); it++){
        (*it).resize(params[0].size());
    }
    int i = 0, j = 0, k;
    while(i < params.size()){
        for(k =0, j = i; j < (i + lamb.size()); j++, k++){
            vec[k] = params[j];
        }
        i = j;

        drawChart(vec, gridLayout, curSys);
        curSys++;
    }

}
void GraphWindow::drawChart(vector<vector<double>> &vec, QGridLayout* gridLayout, int curSys)
{
    QBarSet *set;
    static int index = 1;
    QString str;

    if(curSys  <= numOfSystems)
        str = "S" + QString::number(curSys);
    else
        str = "Вся система";

    for(int j = 0; j < 6; j++){
        switch(j){
        case 0:
        {
            if(str == "Вся система")
                continue;
            set = new QBarSet(QString(str + " p_0j"));
            break;
        }
        case 1:
        {
            if(str == "Вся система")
                continue;
            set = new QBarSet(str + " r_j");
            break;
        }
        case 2:
        {
            set = new QBarSet(str + " lj");
            break;
        }
        case 3:
        {
            set = new QBarSet(str + " mj");
            break;
        }
        case 4:
        {
            set = new QBarSet(str + " wj");
            break;
        }
        case 5:
        {
            set = new QBarSet(str + " uj");
            break;
        }
        }

    // znesty v set
        for(int i = 0; i < vec.size(); i++){
            *set << vec[i][j];
        }

        QBarSeries *series = new QBarSeries();
        series->append(set);
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QValueAxis *axis = new QValueAxis();
        axis->setRange(lamb[0], lamb[lamb.size() - 1]);
        chart->createDefaultAxes();
        chart->setAxisX(axis);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        gridLayout->addWidget(chartView, index, 0);
        index++;
    }

}
