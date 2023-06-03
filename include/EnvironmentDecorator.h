#ifndef ENVIRONMENTDECORATOR_H
#define ENVIRONMENTDECORATOR_H

#include "Environment.h"
#include "Logger.h"

#include <chrono>
#include <memory>

namespace environment {

class EnvironmentDecorator : public Environment {
public:
    // Pass through constructors
    using Environment::Environment;

    // Inject logger
    void setLogger(std::unique_ptr<Logger> logger) {
        this->logger = std::move(logger);
    }

    void updateCellPosition(Cell* cell, const Point& oldPos) override {
        measureExecutionTime("updateCellPosition", [&]() { Environment::updateCellPosition(cell, oldPos); });
    }
    Cell* AddCell(Cell* cell) override {
        return measureExecutionTime("AddCell", [&]() { return Environment::AddCell(cell); });
    }
    Cell* AddCell(const Point& point) override {
        return measureExecutionTime("AddCell", [&]() { return Environment::AddCell(point); });
    }
    Cell* AddCell(const Point& point, std::vector<int> countOfWeights)  override {
        return measureExecutionTime("AddCell", [&]() { return Environment::AddCell(point, countOfWeights); });
    }

    void InvalidateCell(Cell* cell) override {
        measureExecutionTime("InvalidateCell", [&]() { Environment::InvalidateCell(cell); });
    }
    void RemoveCell(Cell* cell)  override {
        measureExecutionTime("RemoveCell", [&]() { Environment::RemoveCell(cell); });
    }
    std::vector<bool> getVisionField(const Point &point) const override {
        return measureExecutionTime("getVisionField", [&]() { return Environment::getVisionField(point); });
    }
    Point randomFreePosition(const Point &point) const override {
        return measureExecutionTime("randomFreePosition", [&]() { return Environment::randomFreePosition(point); });
    }


private:
    template <typename Func>
    std::invoke_result_t<Func> measureExecutionTime(const std::string& funcName, Func func) const {
        auto start = std::chrono::high_resolution_clock::now();

        if constexpr (std::is_void_v<std::invoke_result_t<Func>>) {
            std::invoke(func);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (logger) {
                logger->log("Execution time for " + funcName + ": " + std::to_string(duration.count()) + " microseconds");
            }
            // explicitly return void
            return;
        }
        else {
            auto result = std::invoke(func);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (logger) {
                logger->log("Execution time for " + funcName + ": " + std::to_string(duration.count()) + " microseconds");
            }
            return result;
        }
    }



    mutable std::unique_ptr<Logger> logger = nullptr;
};
}

#endif // ENVIRONMENTDECORATOR_H
