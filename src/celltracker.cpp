#include "../include/celltracker.h"

static constexpr int kDebouncerDelay = 100;// ms


CellTracker::CellTracker(QGraphicsScene* sceneCellDemo, QLabel* labelEnergy, QLabel* labelAggressiveness, EnvironmentScene* scene)
    : debouncer(std::chrono::milliseconds(kDebouncerDelay)), scene(scene)
{
    this->sceneCellTracking = sceneCellDemo;
    this->labelCurrentEnergy = labelEnergy;
    this->labelAggressiveness = labelAggressiveness;
    this->isBounded = false;
    this->curView = new QGraphicsPixmapItem();
    this->sceneCellTracking->addItem(curView);
}

CellTracker::~CellTracker()
{
    delete curView;
}

CellView* CellTracker::getTrackedCell() const {
    return trackedCellView;
}


void CellTracker::boundCell(environment::Cell *cellPtr, CellView *cellViewPtr)
{
    debouncer.debounce([this, cellPtr, cellViewPtr]() {
        this->trackedCell = cellPtr;
        this->trackedCellView = cellViewPtr;
        this->isBounded = true;
    });
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
        QPixmap pixmap = scene->getOriginalGradation(trackedCell->getAggressiveness() * 100)->scaled(this->sceneCellTracking->width()*0.8, this->sceneCellTracking->width()*0.8, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->curView->setPixmap(pixmap);
    }
}
