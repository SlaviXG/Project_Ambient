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

#include <vector>
#include <string>
#include <map>

namespace controller
{
    constexpr int kCellSize = 20;
    constexpr int kFps = 1;

    class CellInteractor
    {
    public:
        virtual void addCell(const Point &point) = 0;
        virtual void removeCell(environment::Cell *cell) = 0;
    };

    /**
     * @brief  GameController class is responsible for managing the game logic and updating the graphical representation of the game.
     *
     */
    class GameController : public CellInteractor
    {
        using gen = environment::RandomGenerator;

    public:
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment)
            : view(view), scene(scene), environment(environment), tick(std::bind(&GameController::execute, this), kFps){};

        virtual ~GameController(){};

        void addCell(const Point &point) override
        {
            auto cellptr = environment->AddCell(point);

            double x = point.i * view->getEnvironmentWidth() / environment->getWidth();
            double y = point.j * view->getEnvironmentHeight() / environment->getHeight();
            auto cellViewptr = scene->genCellViewPtr(x, y, kCellSize, kCellSize, cellptr->getAggressiveness() * 100);
            scene->addCell(cellViewptr);

            NotifyLoggers("Cell  " + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) +
                          "  { " + std::to_string(point.i) + ", " + std::to_string(point.j) + " } ""  was added ");

            NotifyLoggers("Cell's (" + std::to_string(reinterpret_cast<std::uintptr_t>(cellptr)) + ") position: Environment {" +
                          std::to_string(cellptr->getPosition().i) + ", " + std::to_string(cellptr->getPosition().j) + "}" +
                          ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}");

            cellMap.insert({cellptr, cellViewptr});
        }

        void removeCell(environment::Cell *cell) override
        {
            this->scene->removeCell(cellMap.at(cell));
            cellMap.erase(cell);

            NotifyLoggers("Cell (" + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + ") was removed");
        }

        inline void start()
        {
            tick.Start();
        }

        inline void stop()
        {
            tick.Stop();
        }

        inline void pause()
        {
            tick.Pause();
        }

        inline void resume()
        {
            tick.Resume();
        }

        static void execute(GameController *gameController)
        {
            gameController->processAI();
            gameController->render();
        }

        inline void AddLogger(Logger* logger)
        {
            loggers.push_back(logger);
        }

        inline void RemoveLogger(Logger* logger)
        {
            loggers.erase(std::remove(loggers.begin(), loggers.end(), logger), loggers.end());
        }

    private:
        void processAI()
        {
            auto cells = environment->getCells();
            for (auto &cell : cells)
            {
                environment::actions action = cell->act();

                switch (action) {
                case environment::kMoveUp:
                    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " moved");
                    break;
                case environment::kPhotosynthesis:
                    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " photosynthesized");
                    break;
                case environment::kDuplication:
                    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " duplicated");
                    break;
                case environment::kAttackUp:
                    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " attacked");
                    break;
                default:
                    NotifyLoggers("Cell " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " did magic");
                    break;
                }
            }
        };

        void render()
        {
            auto cells = environment->getCells();
            for (const auto &cell : cells)
            {
                auto point = cell->getPosition();
                double x = point.i * view->getEnvironmentWidth() / environment->getWidth();
                double y = point.j * view->getEnvironmentHeight() / environment->getHeight();

                NotifyLoggers("Cell's " + std::to_string(reinterpret_cast<std::uintptr_t>(cell)) + " position: Environment {" +
                              std::to_string(cell->getPosition().i) + ", " + std::to_string(cell->getPosition().j) + "}" +
                              ", Scene {" + std::to_string(x) + ", " + std::to_string(y) + "}");

                scene->updateCell(cellMap.at(cell), x, y, cell->getAggressiveness() * 100);
            }
        };

        void NotifyLoggers(const std::string message)
        {
            for (auto& logger : loggers)
            {
                logger->log(message);
            }
        }

        MainWindow *view;
        EnvironmentScene *scene;
        environment::Environment *environment;
        std::map<environment::Cell *, CellView *> cellMap;

        Tick tick;
        std::vector<Logger*> loggers;
    };
};

#endif
