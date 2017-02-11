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
// ПОМІНЯТИ ПІСЛЯ ВІДЛАГОДЖЕННЯ
int myTableModel::columnCount(const QModelIndex& index) const
{
    return 5;
}

QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0:
                return QString("Інтенсивність \nвхідного потоку");
            case 1:
                return QString("Номер \nсистеми");
            case 2:
                return QString("Pi_0j");
            case 3:
                return  QString("Pj");
            case 4:
                return QString("lj");
            case 5:
                return QString("mj");
            case 6:
                return QString("wj");
            case 7:
                return QString("uj");
            /*case 7:
                return QString("l");
            case 8:
                return QString("m");
            case 9:
                return QString("w");
            case 10:
                return QString("u");*/
            }
        }
    }
    // без цього не працює...
    // Хедери не виводяться
    return QVariant();
}

QVariant myTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole){
        if((index.row() == systemParams.size() - 2) && (index.column() == 1))
            return QString("Для всієї \nсистеми");
        return QString("%1").arg(probMat[index.row()][index.column()]); // саме тут ми визначаємо, дані з якого 2д вектора виводити
    }
    return QVariant();
}
// insertRow i RemoveRow викликають insertRows i RemoveRows
bool myTableModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
}

bool myTableModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row - count + 1);
    endRemoveRows();
}

void myTableModel::simplifyMatrix()
{
    // спростимо матрицю
    // жодна інтенсивіність не переходить сама в себе
    // можемо поставити -1 по діагоналі
    for(int i = 0; i < probMat.size(); i++){
        probMat[i][i] = -1;
    }

    double tmp, mul, hlp;

    // спрощуэмо матрицю і рішаємо методом Гаусса
    for(int i = 0; i < probMat.size(); i++){
        hlp = probMat[i][i];
        for(int del = i; del < probMat.size(); del++){
            probMat[i][del] = probMat[i][del] / (hlp * -1);
        }

        for(int down = i+1; down < probMat.size(); down++){
            mul = probMat[down][i];
            for(int right = i; right < probMat.size(); right++){
                // елемент mul на який множимо треба запам*ятати,
                // бо в масиві він змінився
                tmp = probMat[i][right] * mul;
                probMat[down][right] = tmp + probMat[down][right];
            }
        }
    }
}

void myTableModel::findSystemParams()
{
    vector<double> lamb, betas;
    double intensity;

    //Для дебагу
    for(int i = 0; i < probMat.size(); i++){
    this->insertRow(this->rowCount(QModelIndex()), QModelIndex());
        size_x++;
    }
    //***

    simplifyMatrix();

    findIntensivities(lamb, intensity);

    // intensity - інт. вхідноого потоку до всієї системи
    for(double intensity = lambMin; intensity <= lambMax; intensity += deltaLamb){
        findIntensivities(lamb, intensity);


    }
}
// Для 5го варіанту і більшої к-ті ПВВ. Переписати функцію знаходження
// ітенсивностей з матриці ймовірностей
void myTableModel::findIntensivities(vector<double>& lamb, double intensity)
{
    // CAUTION: gavnokod
    lamb.resize(probMat.size());

    lamb[0] = intensity;
    lamb[1] = lamb[0] / probMat[0][1];

    int index, last;
    double elem;
    last = probMat.size()-1;
    elem = lamb[1] / probMat[1][last];
    for(int i = 2; i < last; i++){
        lamb[i] = elem * probMat[i][last];
    }
    if(probMat.size() > 5){
        lamb[last-1] = (probMat[last-1][last] * elem) / (1 + probMat[last-1][last]);
        lamb[last] = elem - lamb[last-1];
    }
    else
        lamb[last] = lamb[1] / probMat[1][last];

    // END OF gavnokod SECTION
}

int myTableModel::getProbMatSize() const
{
    return this->probMat.size();
}

void myTableModel::setAvgServTime(vector<double> &arr)
{
    v.resize(arr.size());
    vector<double>::iterator it = arr.begin(), itv = v.begin();
    for(; it  < arr.end(); it++, itv++){
        *itv = *it;
    }
}

void myTableModel::setMinMaxLamb(double min, double max)
{
    this->lambMin = min;
    this->lambMax = max;
}

void myTableModel::setDeltaLamb(double delta)
{
    this->deltaLamb = delta;
}
