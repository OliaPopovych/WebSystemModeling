#include "tablemodel.h"

void myTableModel::setProbMat(double **arr, int size)
{
    //this->probMat = arr;


}

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

    systemParams.reserve(100);
}

myTableModel::~myTableModel()
{
}

int myTableModel::rowCount(const QModelIndex& index) const
{
    return systemParams.size();
}
int myTableModel::columnCount(const QModelIndex& index) const
{
    return systemParams[0].size();
}
QVariant myTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
        return systemParams[index.column()][index.row()];
    return QVariant::Invalid;
}
