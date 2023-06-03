#ifndef CELLTRACKER_H
#define CELLTRACKER_H

#include <QGraphicsScene>
#include <QLabel>
#include <QObject>
#include <QString>

#include "cell.h"
#include "CellView.h"
#include "Debouncer.h"

class CellTracker : public QObject
{
    Q_OBJECT

public:
    CellTracker(QGraphicsScene* sceneCellDemo, QLabel* labelEnergy, QLabel* labelAggressiveness);
    ~CellTracker();

    void displayInfo();
    CellView* getTrackedCell() const;

public slots:
    void boundCell(environment::Cell* cellPtr, CellView* cellViewPtr);
    void unboundCell();

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

    Debouncer debouncer;

    void updateScene();
};

#endif // CELLTRACKER_H
