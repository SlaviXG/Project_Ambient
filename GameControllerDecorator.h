#ifndef GAMECONTROLLERDECORATOR_H
#define GAMECONTROLLERDECORATOR_H

#include "GameController.h"
#include "GameLogicThread.h"
#include "Logger.h"

#include <chrono>


namespace controller {

class GameControllerDecorator : public GameController
{
    Q_OBJECT
public:
    using GameController::GameController;

    void addCell(const Point &point) override {
        measureExecutionTime("addCell(const Point &point)", [&]() { GameController::addCell(point); });
    }

    void addCell(const Point &point, const std::vector<int>& countOfWeights) override {
        measureExecutionTime("addCell(const Point &point, const std::vector<int>& countOfWeights)", [&]() { GameController::addCell(point, countOfWeights); });
    }

    void addCell(environment::Cell* cellptr) override {
        measureExecutionTime("addCell(environment::Cell* cellptr)", [&]() { GameController::addCell(cellptr); });
    }
    void removeCell(environment::Cell *cellptr) override {
        measureExecutionTime("removeCell(environment::Cell *cell", [&]() { GameController::removeCell(cellptr); });
    }

    void GenerateRandomCells(size_t cell_count) override {
        measureExecutionTime("GenerateRandomCells", [&]() { GameController::GenerateRandomCells(cell_count); });
    }

    void start() override
    {
        timer.disconnect();
        this->logicThread->start();

        logicThread->queueTask([this]() { this->GenerateRandomCells(kStartingCellCount); });

        connect(&timer, &QTimer::timeout, this, &GameController::executeLogicThread);
        timer.start(1000 / kFps);
    }

private:
    template <typename Func>
    void measureExecutionTime(const std::string& funcName, Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        NotifyLoggers("Execution time for " + funcName + ": " + std::to_string(duration.count()) + " microseconds");
    }
};
}

#endif // GAMECONTROLLERDECORATOR_H
