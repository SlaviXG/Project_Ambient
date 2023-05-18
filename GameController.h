#ifndef FRAME_H_
#define FRAME_H_

#include "Environment.h"
#include "EnvironmentScene.h"
#include "mainwindow.h"
#include "Tick.h"
#include "point.h"
#include "cell.h"
#include "CellView.h"
#include "logger.h"

#include <QTimer>
#include <QObject>

#include <vector>
#include <string>
#include <map>

namespace controller
{
    constexpr int kCellSize = 2;
    constexpr int kFps = 1000000;
    constexpr int kViewPadding = kCellSize / 2;
    constexpr size_t kStartingCellCount = 20;

     /**
     * @brief The CellInteractor class
     *
     * Used to interact with the controller from the logic
     */
    class CellInteractor
    {
    public:
        virtual void addCell(environment::Cell* cell) = 0;
        virtual void removeCell(environment::Cell *cell) = 0;
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
        virtual void addCell(const Point &point,  const std::vector<int>& countOfWeights) = 0;
        virtual void GenerateRandomCells(size_t cell_count) = 0;
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
    public:
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment)
            : view(view), scene(scene), environment(environment), timer(this), loggers() {}

        virtual ~GameController(){};

        inline void addCell(const Point &point) override
        {
            auto cellptr = environment->AddCell(point);
            this->addCell(cellptr);
        }

        inline void addCell(const Point &point, const std::vector<int>& countOfWeights) override
        {
            auto cellptr = environment->AddCell(point, countOfWeights);
            this->addCell(cellptr);
        }
        inline void start() override
        {
            timer.disconnect();
            this->GenerateRandomCells(kStartingCellCount);
            connect(&timer, &QTimer::timeout, this, &GameController::execute);
            timer.start(1000 / kFps);
        }

        inline void stop() override
        {
            timer.stop();
            auto cells = environment->getCells();
            for (const auto& cell : cells)
            {
                environment->InvalidateCell(cell);
                environment->RemoveCell(cell);
            }
            assert(cellMap.empty());
        }

        inline void pause() override
        {
            timer.stop();
        }

        inline void resume() override
        {
            timer.start(1000 / kFps);
        }

        inline void AddLogger(Logger* logger)
        {
            loggers.push_back(logger);
        }

        inline void RemoveLogger(Logger* logger)
        {
            loggers.erase(std::remove(loggers.begin(), loggers.end(), logger), loggers.end());
        }

        void addCell(environment::Cell* cellptr) override;
        void removeCell(environment::Cell *cell) override;

    private:
        void processAI();
        void render();

        void execute()
        {
            this->processAI();
            this->render();
        }

        void NotifyLoggers(const std::string message)
        {
            for (auto& logger : loggers)
            {
                logger->log(message);
            }
        }

        void GenerateRandomCells(size_t cell_count) {
            assert(environment != nullptr);

            for (int i = 0; i < cell_count; ++i) {
                auto pos = environment::RandomGenerator::generateRandomPoint({0, 0}, {environment->getHeight() - 1, environment->getWidth() - 1});
                if (!environment->getFrame(pos))
                    this->addCell(pos);
                else
                    --i;
            }
        }

        void GenerateRandomCells(size_t cell_count, const std::vector<int>& countOfWeights) {
            assert(environment != nullptr);

            for (int i = 0; i < cell_count; ++i) {
                auto pos = environment::RandomGenerator::generateRandomPoint({0, 0}, {environment->getHeight() - 1, environment->getWidth() - 1});
                if (!environment->getFrame(pos))
                    this->addCell(pos, countOfWeights);
                else
                    --i;
            }
        }

        /**
         * @brief GenerateRandomCells
         * @param cell_count
         * @param top_left Top left corner of the bounding box
         * @param bottom_right Bottom right corner of the bounding box
         */
        void GenerateRandomCells(size_t cell_count, const Point& top_left, const Point& bottom_right) {
            assert(environment != nullptr);
            assert(environment->checkPositionCorrectness(top_left));
            assert(environment->checkPositionCorrectness(bottom_right));

            for (int i = 0; i < cell_count; ++i) {
                auto pos = environment::RandomGenerator::generateRandomPoint(top_left, bottom_right);
                if (!environment->getFrame(pos))
                    this->addCell(pos);
                else
                    --i;
            }
        }

        /**
         * @brief GenerateRandomCells
         * @param cell_count
         * @param countOfWeights
         * @param top_left Top left corner of the bounding box
         * @param bottom_right Bottom right corner of the bounding box
         */
        void GenerateRandomCells(size_t cell_count, const std::vector<int>& countOfWeights, const Point& top_left, const Point& bottom_right) {
            assert(environment != nullptr);
            assert(environment->checkPositionCorrectness(top_left));
            assert(environment->checkPositionCorrectness(bottom_right));

            for (size_t i = 0; i < cell_count; ++i) {
                auto pos = environment::RandomGenerator::generateRandomPoint(top_left, bottom_right);
                if (!environment->getFrame(pos))
                    this->addCell(pos, countOfWeights);
                else
                    --i;
            }
        }

        MainWindow *view;
        EnvironmentScene *scene;
        environment::Environment *environment;
        std::map<environment::Cell *, CellView *> cellMap;

        QTimer timer;
        std::vector<Logger*> loggers;
    };
};

#endif
