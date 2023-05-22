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

    constexpr int kMaxEnergy = 2000;
    constexpr int kMinEnergy = 1600;

    constexpr int kSteps = 5;                   //
    constexpr int kMoveCost = 5;                // count of energy, that cell will loose after move
    constexpr int kPhotosynthesisAdd = 25;      // count of energy, that cell will recieve after Photosynthes
    constexpr float kAttackCoefficient = 0.5;  // opponent energy -= currentEnergy * kAC + minDamage
    constexpr float kAttackCost = 0.01;          // 1/10 * currentEnergy
    constexpr int kDuplicationCost = 1200;
    constexpr int kPrise = 500;                 // + energy after killing
    constexpr int movesToDeath = 800;           // every cell can make at max 250 actions
    constexpr int minDamage = 1000;
    constexpr int kDelay = 10;

    class Cell : public Frame
    {
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
