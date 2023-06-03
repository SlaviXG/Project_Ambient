/**
 * @file GameController.h
 * @brief This header file contains GameController, GameInteractor and CellInteractor classes.
 *
 * GameController class manages the game logic and updates the graphical representation of the game.
 * GameInteractor and CellInteractor are interfaces for interaction between the controller and the view and logic layers, respectively.
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Environment.h"
#include "EnvironmentScene.h"
#include "mainwindow.h"
#include "point.h"
#include "cell.h"
#include "CellView.h"
#include "logger.h"
#include "CellViewGarbageCollector.h"

#include <QTimer>
#include <QObject>
#include <QMutex>
#include <QStack>
#include <QThread>
#include <QMutexLocker>

#include <vector>
#include <string>
#include <map>

class GameLogicThread;

namespace controller
{
    constexpr int kCellSize = 4;                ///< Default size of a cell
    constexpr int kFps = 10;                    ///< Frames per second of the game update
    constexpr int kViewPadding = kCellSize / 2; ///< Padding around the view
    constexpr size_t kStartingCellCount = 200;  ///< Initial cell count when the game starts

    /**
     * @brief CellInteractor interface for interacting with the controller from the logic layer.
     */
    class CellInteractor
    {
    public:
        /**
         * @brief Add a cell to the controller and view layer.
         * @param cell The cell to add.
         */
        virtual void addCell(environment::Cell *cell) = 0;
        /**
         * @brief Remove a cell from the the controller and view layers
         * @param cell The cell to remove.
         */
        virtual void removeCell(environment::Cell *cell) = 0;
        /**
         * @brief Add a cell to a specific point in the controller and view layer.
         * @param point The point to add the cell.
         */
        virtual void addCell(const Point &point) = 0;
        /**
         * @brief Add a cell with a specific genotype to a specific point in the controller and view layer.
         * @param point The point to add the cell.
         * @param genotype The genotype of the cell.
         */
        virtual void addCell(const Point &point, genotype::Genotype *genotype) = 0;
    };

    /**
     * @brief GameInteractor interface for interacting with the controller from the view layer.
     */
    class GameInteractor
    {
    public:
        /**
         * @brief Add a cell to a specific point in the game.
         * @param point The point to add the cell.
         */
        virtual void addCell(const Point &point) = 0;
        /**
         * @brief Add a cell to a specific point in the game with specific count of weights.
         * @param point The point to add the cell.
         * @param countOfWeights The count of weights for the cell.
         */
        virtual void addCell(const Point &point, const std::vector<int> &countOfWeights) = 0;
        /// Start the game.

        virtual void start() = 0;
        /// Stop the game.

        virtual void stop() = 0;
        /// Pause the game.

        virtual void pause() = 0;
        /// Resume the game.

        virtual void resume() = 0;
    };

    /**
     * @brief GameController class is responsible for managing the game logic and updating the graphical representation of the game.
     *
     * GameController inherits from QObject, CellInteractor and GameInteractor, and encapsulates game logic, interactions with
     * different parts of the application like views and environment, and provides an interface for generating random cells and
     * controlling the game.
     */
    class GameController : public QObject, public CellInteractor, public GameInteractor
    {
        Q_OBJECT

    public:
        /**
         * @brief Construct a GameController with a given view, scene and environment.
         * @param view The main window of the application.
         * @param scene The graphical scene of the game.
         * @param environment The game environment.
         */
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment);
        virtual ~GameController();

        /**
         * @brief Set the cell tracker for the game.
         * @param cellTracker The cell tracker object.
         */
        void setCellTracker(CellTracker *cellTracker);

        /**
         * @brief Add a cell to the game at a specific point.
         * @param point The point to add the cell.
         */
        void addCell(const Point &point) override;

        /**
         * @brief Add a cell to the game at a specific point with a specific count of weights.
         * @param point The point to add the cell.
         * @param countOfWeights The count of weights for the cell.
         */
        void addCell(const Point &point, const std::vector<int> &countOfWeights) override;

        /**
         * @brief Start the game.
         */
        void start() override;

        /**
         * @brief Stop the game.
         */
        void stop() override;

        /**
         * @brief Pause the game.
         */
        void pause() override;

        /**
         * @brief Resume the game.
         */
        void resume() override;

        /**
         * @brief This method adds a cell to the game at the given point and associates a genotype with it.
         * @param point: The point at which the new cell should be added.
         * @param genotype: The genotype to be associated with the new cell.
         */
        void addCell(const Point &point, genotype::Genotype *genotype);

        /**
         * @brief Adds a new logger to the list of loggers for the game.
         * @param logger: The logger to be added.
         */
        void AddLogger(Logger *logger) { loggers.push_back(logger); }
        /**
         * @brief Removes a specific logger from the list of loggers for the game.
         * @param logger: The logger to be removed.
         */
        void RemoveLogger(Logger *logger);

        /**
         * @brief Adds a new cell to the view and controller layers. This method takes a pointer to a cell object.
         * @param cellptr: A pointer to the cell object to be added.
         */
        void addCell(environment::Cell *cellptr) override;

        /**
         * @brief Removes a specific cell from the game.
         * @param cell: The cell to be removed.
         */
        void removeCell(environment::Cell *cell) override;

        /**
         * @brief Process AI actions for all active cells in the game.
         */
        void processAI();

    public slots:
        /**
         * @brief Slot to execute the game logic thread.
         */
        void executeLogicThread();
        /**
         * @brief Slot to generate random cells.
         */
        void GenerateRandomCellsSlot();

    protected:
        /**
         * @brief Render all cells in the game.
         */
        void render();

        /**
         * @brief Send a message to all loggers.
         * @param message: The message to be sent to all loggers.
         */
        void NotifyLoggers(const std::string message);

        /**
         * @brief Generate a number of random cells.
         * @param cell_count: The number of cells to generate.
         */
        virtual void GenerateRandomCells(size_t cell_count);

        /**
         * @brief Generate a number of random cells with specific weights.
         * @param cell_count: The number of cells to generate.
         * @param countOfWeights: The weights for the cells to generate.
         */
        virtual void GenerateRandomCells(size_t cell_count, const std::vector<int> &countOfWeights);

        /**
         * @brief Generate a number of random cells within a specific bounding box.
         * @param cell_count: The number of cells to generate.
         * @param top_left: The top left corner of the bounding box.
         * @param bottom_right: The bottom right corner of the bounding box.
         */
        virtual void GenerateRandomCells(size_t cell_count, const Point &top_left, const Point &bottom_right);

        /**
         * @brief Generate a number of random cells with specific weights within a specific bounding box.
         * @param cell_count: The number of cells to generate.
         * @param countOfWeights: The weights for the cells to generate.
         * @param top_left: The top left corner of the bounding box.
         * @param bottom_right: The bottom right corner of the bounding box.
         */
        virtual void GenerateRandomCells(size_t cell_count, const std::vector<int> &countOfWeights, const Point &top_left, const Point &bottom_right);

        QTimer timer;                 ///< The timer for updating the game at a specific FPS.
        GameLogicThread *logicThread; ///< The game logic thread.

    private:
        MainWindow *view;                                            ///< The main window of the application.
        EnvironmentScene *scene;                                     ///< The graphical scene of the game.
        environment::Environment *environment;                       ///< The game environment.
        std::unordered_map<environment::Cell *, CellView *> cellMap; ///< Map from Cell pointer to CellView pointer.
        CellTracker *cellTracker;                                    ///< The cell tracker for the game.

        std::vector<Logger *> loggers; ///< Vector of loggers for the game.

        QMutex mutex;                       ///< The mutex for thread safety.
        CellViewGarbageCollector collector; ///< The garbage collector for unused CellView objects.
    };
};

#endif