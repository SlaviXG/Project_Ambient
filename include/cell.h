#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
#include "frame.h"
#include "Environment.h"
#include "point.h"
#include "configs/default.h"

class CellTracker;

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

    class Cell : public Frame
    {
        friend class ::CellTracker;

    private:
        double currentEnergy;
        double maxEnergy;
        double aggressiveness;
        genotype::Genotype genotype;
        int stepsCount = kSteps;
        bool isAliveStatus = true;
        int numberOfMovesToDeath = movesToDeath;
        int totalScore = 0;                         // evaluation of cell's model
        int delayAfterDuplication = kDelay;

    public:
        void evaluateAction(int action);

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
        Cell(Point startingPosition, std::vector<int> countOfWeights, Environment* environment = nullptr);
        Cell(Cell &mother, Point freePosition);
        Cell(Point startingPosition, genotype::Genotype* genotype, Environment* environment = nullptr);

        double getCurrentEnergy() const;
        double getMaxEnergy() const;
        double getAggressiveness() const;
        genotype::Genotype getGenotype() const;
        bool isAlive() const;
        int getStepsCount() const;
        int getTotalScore() const;

        void setCurrentEnergy(double count) { currentEnergy = count; }
        void setIsAlive(bool status) { isAliveStatus = status; }

        bool cellCanMakeThisAction(Matrix& inputs,Matrix& outputs, int& actionIndex);

        void removeBadOutputs(Matrix& inputs, Matrix& outputs);
        void move(int direction);
        void photosynthesis();
        void attack(int action);
        /**
         * @brief Invalidates itself
         *
         */
        void die() { environment->InvalidateCell(this); this->isAliveStatus = false;};


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
