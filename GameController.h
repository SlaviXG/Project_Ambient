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
    constexpr double kFps = 0.5;

    /**
     * @brief  GameController class is responsible for managing the game logic and updating the graphical representation of the game.
     * 
     */
    class GameController
    {
        using gen = environment::RandomGenerator;

    public:
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment)
            : view(view), scene(scene), environment(environment){ tick = Tick(kFps); };
        virtual ~GameController()
        {
            auto cells = environment->getCells();
            for (auto cell : cells)
                delete cell;
        };

        inline void processAI()
        {
            auto cells = environment->getCells();
            for (auto &cell : cells)
                cell->act();
            environment->updateMap();
        };

        void addCell(const Point &point)
        {
            environment::Cell *cellptr = new environment::Cell(point, environment);
            environment->AddCell(cellptr);

            double x = point.i * view->getWidth() / environment->getWidth();
            double y = point.j * view->getHeight() / environment->getHeight();
            CellView *cellViewptr = new CellView(x, y, kCellSize, kCellSize);

            cellMap.insert({cellptr, cellViewptr});
        }

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

    private:
        MainWindow *view;
        EnvironmentScene *scene;
        environment::Environment *environment;

        std::map<environment::Cell *, CellView *> cellMap;

        Tick tick;
    };
};

/* = {gen::generateRandomNumber(0, environment->getHeight()),
                                  gen::generateRandomNumber(0, environment->getWidth())}*/
#endif