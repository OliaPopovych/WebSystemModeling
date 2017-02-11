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
    double lambMin, lambMax;// мінімальне і максимальне значення інтенсивності вхідного потоку
    double deltaLamb;// крок зміни інтенсивності
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
    void setAvgServTime(vector<double> &arr);
    void setMinMaxLamb(double min, double max);
    void setDeltaLamb(double delta);

    void simplifyMatrix();
    void findSystemParams(); // головний метод для знах. значень таблиці
    void findIntensivities(vector<double> &lamb, double intensity); // знаходить інтенсивносі вх. потоків для кожної системи



};



#endif // TABLEMODEL_H
