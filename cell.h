#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
#include "frame.h"
#include "Environment.h"
#include "point.h"


namespace environment
{

    enum actions
    {
        kMoveUp,
        kMoveUpRight,
        kMoveRight,
        kMoveRightDown,
        kMoveDown,
        kMoveLeftDown,
        kMoveLeft,
        kMoveLeftUp,
        kPhotosynthesis,
        kAttackUp,
        kAttackUpRight,
        kAttackRight,
        kAttackRightDown,
        kAttackDown,
        kAttackLeftDown,
        kAttackLeft,
        kAttackLeftUp,
        kDuplication,
        kCellIsDead,
        kNegativeAction = -1
    };
    
    constexpr int kMaxEnergy = 500;
    constexpr int kMinEnergy = 400;
    constexpr int kSteps = 50;
    constexpr int kMoveCost = 10;
    constexpr int kPhotosynthesisAdd = 25;
    constexpr float kAttackCoefficient = 0.35;
    constexpr float kAttackCost = 0.1;       // 1/10 * currentEnergy
    constexpr int kPrise = 200;           // + energy after killing


    class Cell : public Frame
    {
    private:
        double currentEnergy;
        double maxEnergy;
        double aggressiveness;
        genotype::Genotype genotype;
        int stepsCount = kSteps;
        bool isAliveStatus = true;

    public:
        Cell() : Frame() {};
        Cell(const Cell& cell) : Frame(cell)
        {
            this->genotype = cell.getGenotype();
            this->maxEnergy = cell.getMaxEnergy();
            this->currentEnergy = cell.getCurrentEnergy();
            this->aggressiveness = cell.getAggressiveness();
            this->isAliveStatus = cell.isAlive();
            this->stepsCount = cell.getStepsCount();
        }
        Cell(Point startingPosition, Environment* environment = nullptr);
        Cell(Cell &mother, Point freePosition);

        double getCurrentEnergy() const;
        double getMaxEnergy() const;
        double getAggressiveness() const;
        genotype::Genotype getGenotype() const;
        bool isAlive() const;
        int getStepsCount() const;

        void setCurrentEnergy(double count) { currentEnergy = count; }
        void setIsAlive(bool status) { isAliveStatus = status; }

        void move(int direction);
        void photosynthesis();
        void attack(int action);
        /**
         * @brief Invalidates itself
         *
         */
        void die() { environment->InvalidateCell(this); this->isAliveStatus = false; };


        /**
         * @brief Make choice and perform action
         * 
         * @return Action performed 
         */
        //actions act() {/* TODO */}
        actions act();  //std::vector<double> inputs
        void duplicate();

        int makeChoice(Matrix& inputs);
        int bestPossibleChoiceIndex(Matrix& outputs, Matrix& inputs);
    };

}

#endif // CELL_H
