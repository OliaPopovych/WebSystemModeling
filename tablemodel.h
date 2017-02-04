#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QtWidgets>

using namespace std;

class myTableModel: public QAbstractTableModel
{
private:
    vector<int> systemParams;
    vector<int> allSystemParams;
    vector<int> S1;
};



#endif // TABLEMODEL_H
