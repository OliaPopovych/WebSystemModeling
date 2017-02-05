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
    int size_x, size_y;
public:
    myTableModel();
    myTableModel(vector<vector<double> > &arr);
    ~myTableModel();

    // ці віртуальні методи треба обов*язково перегрузити
    int rowCount(const QModelIndex& index) const;
    int columnCount(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
   /* bool insertRows(int row, int count, const QModelIndex& parent);
    bool removeRows(int row, int count, const QModelIndex& parent);
    bool insertColumns(int row, int count, const QModelIndex& parent);
    bool removeColumns(int row, int count, const QModelIndex& parent);*/

    QVariant data(const QModelIndex& index, int role) const;
};



#endif // TABLEMODEL_H
