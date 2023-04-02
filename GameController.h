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
    constexpr int kFps = 10;

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
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
    };

    /**
     * @brief  GameController class is responsible for managing the game logic and updating the graphical representation of the game.
     *
     */
    class GameController : public CellInteractor, public GameInteractor
    {
        using gen = environment::RandomGenerator;

    public:
        explicit GameController(MainWindow *view, EnvironmentScene *scene, environment::Environment *environment)
            : view(view), scene(scene), environment(environment), tick(std::bind(&GameController::execute, this), kFps){};

        virtual ~GameController(){};

        inline void addCell(const Point &point) override
        {
            auto cellptr = environment->AddCell(point);
            this->addCell(cellptr);
        }

        inline void start() override
        {
            tick.Start();
        }

        inline void stop() override
        {
            tick.Stop();
        }

        inline void pause() override
        {
            tick.Pause();
        }

        inline void resume() override
        {
            tick.Resume();
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

        static void execute(GameController *gameController)
        {
            gameController->processAI();
            gameController->render();
        }

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
