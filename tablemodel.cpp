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
    return 8;
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
                return QString("p_0j");
            case 3:
                return  QString("r_j");
            case 4:
                return QString("lj");
            case 5:
                return QString("mj");
            case 6:
                return QString("wj");
            case 7:
                return QString("uj");
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
        if(index.column() == 0)
            return QString("%1").arg(intens[index.row() / probMat.size()]);
        if(index.column() == 1 && (index.row()+1) % probMat.size() == 0)
            return QString("Для всієї \nсистеми");
        if(index.column() == 1){

            return QString("S%1").arg(index.row() % probMat.size() + 1);
        }
        return QString("%1").arg(systemParams[index.row()][index.column()-2]); // саме тут ми визначаємо, дані з якого 2д вектора виводити
    }
    if(role == Qt::BackgroundRole){
        if((index.row()+1) % probMat.size() == 0)
            return QBrush(QColor(255,255,140));
    }
    return QVariant();
}
// insertRow i RemoveRow викликають insertRows i RemoveRows
bool myTableModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
}

bool myTableModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(count!=0){
        beginRemoveRows(parent, row, row + count - 1);
        endRemoveRows();
    }
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

void myTableModel::findBetas(vector<double>& betas, vector<double>& lamb)
{
    for(int i = 0, j = 1; i < betas.size(); i++, j++){
        betas[i] = lamb[j] * v[i];
    }
}
void myTableModel::findRo(vector<double>& ro, vector<double>& betas)
{
    ro[0] = betas[0] / 2;
    for(int i = 1; i < ro.size(); i++){
        ro[i] = betas[i];
    }
}

void myTableModel::findP0(vector<double>& p0, vector<double>& ro, vector<double> &betas)
{
    p0[0] = 1 / (betas[0] + betas[0] / (2*(1 - betas[0]/2)));
    for(int i = 1; i < p0.size(); i++){
        p0[i] = 1 - ro[i];
    }

}

void myTableModel::findAvgQueue(vector<double>& L, vector<double>& betas, vector<double>& p0)
{
    L[0] = (betas[0]*betas[0]*p0[0]) / (4*(1 - betas[0]/2)*(1 - betas[0]/2));
    for(int i = 1; i < L.size(); i++){
        L[i] = (betas[i] * p0[i]) / ((1 - betas[0])*(1 - betas[0]));
    }
}
void myTableModel::findAvgNumOfApps(vector<double>& m, vector<double>& L, vector<double>& betas)
{
    for(int i = 0; i < m.size(); i++){
        m[i] = L[i] + betas[i];
    }
}
void myTableModel::findAvgWaitTime(vector<double>& w, vector<double>& L, vector<double>& lamb)
{
    for(int i = 0; i < w.size(); i++){
        w[i] = L[i] / lamb[i];
    }
}
void myTableModel::findAvgBeingTime(vector<double>& u, vector<double>& m, vector<double>& lamb)
{
    for(int i = 0; i < u.size(); i++){
        u[i] = m[i] / lamb[i];
    }
}
void myTableModel::findTransmissionRates(vector<double>& a, vector<double>& lamb)
{
    for(int i = 0, j = 1; i < a.size(); i++, j++){
        a[i] = lamb[j] / lamb[0];
    }
}

void myTableModel::findSystemParams()
{

    this->removeRows(0,this->rowCount(QModelIndex()), QModelIndex());
    this->size_x = 0;

    vector<double> lamb, betas, ro, p0, l, m, w, u, a;
    double L = 0, M = 0, W = 0, U = 0;
    double intensity;
    int size = probMat.size() - 1;
    betas.resize(size);
    ro.resize(size);
    p0.resize(size);
    l.resize(size);
    m.resize(size);
    w.resize(size);
    u.resize(size);
    a.resize(size);

    simplifyMatrix();

    findIntensivities(lamb, intensity);

    vector<vector<double>>::iterator it, prev;
    vector<double>::iterator el;
    size_t s = (lambMax - lambMin) / deltaLamb + 1;
    systemParams.resize(s * 7);
    for(it = systemParams.begin(); it < systemParams.end(); it++){
        (*it).reserve(10);
    }

    int shift = size;
    prev = systemParams.begin();
    // intensity - інт. вхідноого потоку до всієї системи
    lambMax = lambMax + 0.000001; //До заданої точності
    for(double intensity = lambMin; intensity <= lambMax; intensity += deltaLamb){
        intens.push_back(intensity);

        findIntensivities(lamb, intensity);
        findTransmissionRates(a, lamb);
        findBetas(betas, lamb);
        findRo(ro, betas);
        findP0(p0, ro, betas);
        findAvgQueue(l, betas, p0);
        findAvgNumOfApps(m, l, betas);
        findAvgWaitTime(w, l, lamb);
        findAvgBeingTime(u, m, lamb);

        int i = 0;
        for(it = prev; it < prev+shift; it++){
            // вставляємо рядок в таблицю
            this->insertRow(this->rowCount(QModelIndex()), QModelIndex());
            size_x++;

            (*it).push_back(p0[i]);
            (*it).push_back(ro[i]);
            (*it).push_back(l[i]);
            (*it).push_back(m[i]);
            (*it).push_back(w[i]);
            (*it).push_back(u[i]);
            i++;
        }
        prev = prev + shift + 1;

        for(size_t i = 0; i < l.size(); i++){
            L += l[i];
        }
        for(size_t i = 0; i < m.size(); i++){
            M += m[i];
        }
        for(size_t i = 0; i < w.size(); i++){
            W += w[i] * a[i];
        }
        for(size_t i = 0; i < u.size(); i++){
            U += u[i] * a[i];
        }
        // вставляємо рядок в таблицю
        this->insertRow(this->rowCount(QModelIndex()), QModelIndex());
        size_x++;

        it->push_back(0);
        it->push_back(0);
        it->push_back(L);
        it->push_back(M);
        it->push_back(W);
        it->push_back(U);

        L = M = W = U = 0;
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
void myTableModel::setNumbOfChannels(int num)
{
    this->numbOfChannels = num;
}
