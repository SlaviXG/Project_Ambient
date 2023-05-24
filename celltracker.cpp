#include "celltracker.h"


CellTracker::CellTracker(QGraphicsScene* sceneCellDemo, QLabel* labelEnergy, QLabel* labelAggressiveness)
{
    this->sceneCellTracking = sceneCellDemo;
    this->labelCurrentEnergy = labelEnergy;
    this->labelAggressiveness = labelAggressiveness;
    this->isBounded = false;
    this->curView = new QGraphicsPixmapItem;
    this->sceneCellTracking->addItem(curView);
}

CellTracker::~CellTracker()
{
    delete curView;
}

void CellTracker::boundCell(environment::Cell *cellPtr, CellView *cellViewPtr)
{
    this->trackedCell = cellPtr;
    this->trackedCellView = cellViewPtr;
    this->isBounded = true;
}

void CellTracker::unboundCell()
{
    this->trackedCell = nullptr;
    this->trackedCellView = nullptr;
    this->isBounded = false;
}


void CellTracker::displayInfo()
{
    if(isBounded){
        if(this->curEnergy != this->trackedCell->getCurrentEnergy()){
            this->labelCurrentEnergy->setText(QString::number(trackedCell->getCurrentEnergy()));
        }

        if(this->curAggress != this->trackedCell->getAggressiveness()){
            this->labelAggressiveness->setText(QString::number(trackedCell->getAggressiveness()));
            this->updateScene();
        }
    }
}

void CellTracker::updateScene()
{
    if(isBounded){
        this->curView->setPixmap(trackedCellView->getCurrentPixmap().scaledToHeight(this->sceneCellTracking->height()*0.8));
    }
}
