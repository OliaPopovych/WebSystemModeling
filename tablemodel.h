#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QtWidgets>

using namespace std;

class myTableModel: public QAbstractTableModel
{
private:
    vector<vector<double>> systemParams;
    vector<vector<double>> probMat;
    int size_x, size_y;// к-сть рядків і стовпців в tableView
    vector<double> v; // вектор середніх часів обслуговування каналами
    vector<double> intens; // вектор інтенсивностей
    double lambMin, lambMax;// мінімальне і максимальне значення інтенсивності вхідного потоку
    double deltaLamb;// крок зміни інтенсивності
    int numbOfChannels;
public:
    myTableModel();
    myTableModel(vector<vector<double> > &arr);
    ~myTableModel();

    // ці віртуальні методи треба обов*язково перегрузити
    int rowCount(const QModelIndex& index) const;
    int columnCount(const QModelIndex& index) const;
    QVariant data(const QModelIndex& index, int role) const;
    // ці, що вище
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);


    int getProbMatSize() const;
    vector<vector<double> > &getParamsTable();
    vector<double> &getLamb();
    void setAvgServTime(vector<double> &arr);
    void setMinMaxLamb(double min, double max);
    void setDeltaLamb(double delta);
    // ВИДАЛИТИ
    void setNumbOfChannels(int num);

    void simplifyMatrix();
    void findSystemParams(); // головний метод для знах. значень таблиці
    // знаходить інтенсивносі вх. потоків для кожної системи
    void findIntensivities(vector<double> &lamb, double intensity);
    void findBetas(vector<double>& betas, vector<double> &lamb);
    void findRo(vector<double>& ro, vector<double> &betas);
    void findP0(vector<double> &p0, vector<double>& ro, vector<double> &betas);
    void findAvgNumOfApps(vector<double> &m, vector<double>& L, vector<double>& betas);
    void findAvgQueue(vector<double>& L, vector<double>& betas, vector<double>& p0);
    void findAvgWaitTime(vector<double>& w, vector<double>& L, vector<double>& lamb);
    void findAvgBeingTime(vector<double>& u, vector<double>& m, vector<double>& lamb);
    void findTransmissionRates(vector<double>& a, vector<double>& lamb);


};



#endif // TABLEMODEL_H
