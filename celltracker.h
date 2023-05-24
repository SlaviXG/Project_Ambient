#ifndef CELLTRACKER_H
#define CELLTRACKER_H

#include <QGraphicsScene>
#include <QLabel>
#include <cell.h>
#include <CellView.h>
#include <QString>

class CellTracker
{
public:
    CellTracker(QGraphicsScene* sceneCellDemo, QLabel* labelEnergy, QLabel* labelAggressiveness);
    ~CellTracker();

    void boundCell(environment::Cell* cellPtr, CellView* cellViewPtr);
    void unboundCell();
    void displayInfo();

private:
    QGraphicsScene* sceneCellTracking = nullptr;
    QLabel* labelCurrentEnergy = nullptr;
    QLabel* labelAggressiveness = nullptr;

    environment::Cell* trackedCell;
    CellView* trackedCellView;

    bool isBounded;
    QGraphicsPixmapItem* curView;
    double curEnergy;
    double curAggress;

    void updateScene();
};

#endif // CELLTRACKER_H
