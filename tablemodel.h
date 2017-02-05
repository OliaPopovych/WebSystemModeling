#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QtWidgets>

using namespace std;

class myTableModel: public QAbstractTableModel
{
private:
    vector<vector<double>> systemParams;
    vector<vector<double>> allSystemParams;
    vector<vector<double>> probMat;
public:
    myTableModel();
    myTableModel(vector<vector<double> > &arr);
    ~myTableModel();

    // ці віртуальні методи треба обов*язково перегрузити
    int rowCount(const QModelIndex& index) const;
    int columnCount(const QModelIndex& index) const;
    QVariant data(const QModelIndex& index, int role) const;

    void setProbMat(double **arr, int size);
};



#endif // TABLEMODEL_H
