#ifndef FRAME_H_
#define FRAME_H_

#include "Environment.h"
#include "EnvironmentScene.h"
#include "mainwindow.h"
#include "Tick.h"
#include "point.h"
#include "cell.h"
#include "CellView.h"

#include <vector>
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

        virtual ~GameController()
        {
            auto cells = environment->getCells();
            for (auto cell : cells)
                delete cell;
        };

        void addCell(const Point &point) override
        {
            // Check whether the cell already exists
            bool exists = false;
            for (const auto &cell : cellMap)
            {
                if (cell.first->getPosition() == point)
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                environment::Cell *cellptr = new environment::Cell(point, environment);
                environment->AddCell(cellptr);

                double x = point.i * view->getWidth() / environment->getWidth();
                double y = point.j * view->getHeight() / environment->getHeight();
                CellView *cellViewptr = new CellView(x, y, kCellSize, kCellSize);

                cellMap.insert({cellptr, cellViewptr});
            }
        }

        void removeCell(environment::Cell *cell) override
        {
            if (cellMap.find(cell) != cellMap.end())
            {
                this->scene->removeCell(cellMap.at(cell));
                cellMap.erase(cell);
                environment->RemoveCell(cell);
            }
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

    private:
        void processAI()
        {
            auto cells = environment->getCells();
            for (auto &cell : cells)
            {
                //cell->act();

                /*if (aggressiveness.first)
                    cellMap.at(cell)->setGradient(aggressiveness.second)*/
            }
        };

        void render()
        {
            auto cells = environment->getCells();
            for (auto &cell : cells)
            {
                auto point = cell->getPosition();
                double x = point.i * view->getWidth() / environment->getWidth();
                double y = point.j * view->getHeight() / environment->getHeight();

                auto cellViewptr = cellMap.at(cell);
                cellViewptr->setPos(x, y);
            }
        };

        MainWindow *view;
        EnvironmentScene *scene;
        environment::Environment *environment;
        std::map<environment::Cell *, CellView *> cellMap;
        Tick tick;
    };
};

#endif
