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
    constexpr int kCellSize = 4;
    constexpr int kFps = 10;
    constexpr int kViewPadding = kCellSize / 2;
    constexpr size_t kStartingCellCount = 200;

    /**
     * @brief The CellInteractor class
     *
     * Used to interact with the controller from the logic
     */
    class CellInteractor
    {
    public:
        virtual void addCell(environment::Cell *cell) = 0;
        virtual void removeCell(environment::Cell *cell) = 0;
        virtual void addCell(const Point &point) = 0;
        virtual void addCell(const Point &point, genotype::Genotype *genotype) = 0;
    };

    /**
     * @brief The GameInteractor class
     *
     * Used to interact with the controller from the view
     */
    class GameInteractor
    {
    public:
        virtual void addCell(const Point &point) = 0;
        virtual void addCell(const Point &point, const std::vector<int> &countOfWeights) = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
    };

    /**
     * @brief  GameController class is responsible for managing the game logic and updating the graphical representation of the game.
     *
     */
    class GameController : public QObject, public CellInteractor, public GameInteractor
    {
        Q_OBJECT

    public:
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment);
        virtual ~GameController();

        void setCellTracker(CellTracker *cellTracker);
        void addCell(const Point &point) override;
        void addCell(const Point &point, const std::vector<int> &countOfWeights) override;

        void start() override;
        void stop() override;
        void pause() override;
        void resume() override;

        void addCell(const Point &point, genotype::Genotype *genotype);

        void AddLogger(Logger *logger) { loggers.push_back(logger); }
        void RemoveLogger(Logger *logger);

        void addCell(environment::Cell *cellptr) override;
        void removeCell(environment::Cell *cell) override;

        void processAI();

    public slots:
        void executeLogicThread();
        void GenerateRandomCellsSlot();

    protected:
        void render();

        void NotifyLoggers(const std::string message);

        virtual void GenerateRandomCells(size_t cell_count);

        virtual void GenerateRandomCells(size_t cell_count, const std::vector<int> &countOfWeights);

        /**
         * @brief GenerateRandomCells
         * @param cell_count
         * @param top_left Top left corner of the bounding box
         * @param bottom_right Bottom right corner of the bounding box
         */
        virtual void GenerateRandomCells(size_t cell_count, const Point &top_left, const Point &bottom_right);

        /**
         * @brief GenerateRandomCells
         * @param cell_count
         * @param countOfWeights
         * @param top_left Top left corner of the bounding box
         * @param bottom_right Bottom right corner of the bounding box
         */
        virtual void GenerateRandomCells(size_t cell_count, const std::vector<int> &countOfWeights, const Point &top_left, const Point &bottom_right);

        QTimer timer;
        GameLogicThread *logicThread;

    private:
        MainWindow *view;
        EnvironmentScene *scene;
        environment::Environment *environment;
        std::unordered_map<environment::Cell *, CellView *> cellMap;
        CellTracker *cellTracker;

        std::vector<Logger *> loggers;

        QMutex mutex;
        CellViewGarbageCollector collector;
    };
};

#endif
