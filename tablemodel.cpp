#include "tablemodel.h"

myTableModel::myTableModel(){
}
myTableModel::myTableModel(vector<vector<double> > &arr)
{
    probMat.reserve(50);
    probMat.resize(arr.size());

    for(int i=0; i<arr.size(); i++){
        probMat[i].resize(arr.size());
        for(int j =0; j<arr.size(); j++){
           probMat[i][j] = arr[j][i];
        }
    }

    this->size_x = 0;
    this->size_y = 0;
}

myTableModel::~myTableModel()
{
}

int myTableModel::rowCount(const QModelIndex& index) const
{
    return this->size_x;
}
int myTableModel::columnCount(const QModelIndex& index) const
{
    return 12;
}

QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0:
                return QString("Інтенсивність \nвхідного потоку");
            case 1:
                return QString("Pi_0j");
            case 2:
                return  QString("Pj");
            case 3:
                return QString("lj");
            case 4:
                return QString("mj");
            case 5:
                return QString("wj");
            case 6:
                return QString("uj");
            case 7:
                return QString("l");
            case 8:
                return QString("m");
            case 9:
                return QString("w");
            case 10:
                return QString("u");
            }
        }
    }
    // без цього не працює...
    // Хедери не виводяться
    return QVariant();
}

/*bool myTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
}

bool myTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent,row, row - count + 1);
    endRemoveRows();
}

/*bool myTableModel::insertColumns(int row, int count, const QModelIndex& parent)
{
    beginInsertColumns(parent, row, row + count - 1);
    endInsertColumns();
}

bool myTableModel::removeColumns(int row, int count, const QModelIndex& parent)
{
    beginRemoveColumns(parent,row, row - count + 1);
    endRemoveColumns();
}*/

QVariant myTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
        return systemParams[index.column()][index.row()];
    return QVariant::Invalid;
}
