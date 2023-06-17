/**
 * @file CellTracker.h
 * @brief Header file for the CellTracker class
 */

#ifndef CELLTRACKER_H
#define CELLTRACKER_H

#include <QGraphicsScene>
#include <QLabel>
#include <QObject>
#include <QString>

#include "cell.h"
#include "CellView.h"
#include "Debouncer.h"
#include "EnvironmentScene.h"

/**
 * @class CellTracker
 * @brief Class tracking a cell and displaying its information.
 *
 * The CellTracker class provides functionality to track and display the state 
 * of a specific cell in a graphical scene.
 */
class CellTracker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the CellTracker class.
     * @param sceneCellDemo The scene for cell demonstration.
     * @param labelEnergy The QLabel to display energy information.
     * @param labelAggressiveness The QLabel to display aggressiveness information.
     * @param scene The scene to track cells.
     */
    CellTracker(QGraphicsScene* sceneCellDemo, QLabel* labelEnergy, QLabel* labelAggressiveness, EnvironmentScene* scene);

    /**
     * @brief Destructor for the CellTracker class.
     */
    ~CellTracker();

    /**
     * @brief Displays the information of the tracked cell.
     */
    void displayInfo();

    /**
     * @brief Gets the tracked cell.
     * @return The tracked cell.
     */
    CellView* getTrackedCell() const;

public slots:
    /**
     * @brief Binds a cell to the tracker.
     * @param cellPtr Pointer to the cell to be tracked.
     * @param cellViewPtr Pointer to the cell view to be tracked.
     */
    void boundCell(environment::Cell* cellPtr, CellView* cellViewPtr);

    /**
     * @brief Unbinds the currently tracked cell from the tracker.
     */
    void unboundCell();

private:
    QGraphicsScene* sceneCellTracking = nullptr;
    QLabel* labelCurrentEnergy = nullptr;
    QLabel* labelAggressiveness = nullptr;

    environment::Cell* trackedCell;
    CellView* trackedCellView;
    EnvironmentScene* scene;

    bool isBounded;
    QGraphicsPixmapItem* curView;
    double curEnergy;
    double curAggress;

    Debouncer debouncer;

    /**
     * @brief Updates the scene with the information of the tracked cell.
     */
    void updateScene();
};

#endif // CELLTRACKER_H
