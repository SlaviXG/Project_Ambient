#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
#include "frame.h"
#include "Environment.h"

namespace environment
{

    constexpr int kMaxEnergy = 500;
    constexpr int kSteps = 20;
    constexpr int kMoveCost = 10;
    constexpr int kPhotosynthesis = 25;
    constexpr int kAttackCoefficient = 4; // 1/4 * currentEnergy
    constexpr int kAttackCost = 10;       // 1/10 * currentEnergy
    constexpr int kPrise = 200;


    class Cell : public Frame
    {
    private:
        double currentEnergy;
        double aggressiveness;
        Genotype genotype;
        int stepsCount = kSteps;
        bool isAliveStatus = true;

    public:
        Cell() {};
        Cell(Point startingPosition, Environment* environment = nullptr);
        Cell(Cell &mother, Point freePosition);

        double getCurrentEnergy() const;
        double getAggressiveness() const;
        Genotype getGenotype() const;
        bool isAlive();

        void setCurrentEnergy(double count) { currentEnergy = count; }
        void setIsAlive(bool status) { isAliveStatus = status; }

        void move(int direction);
        void photosynthesis();
        void attack(Cell &opponent);

        void act(std::vector<double> inputs);
        // void duplicate();

        // TODO: Create static method Cell randomCell()
    };

}

#endif // CELL_H
