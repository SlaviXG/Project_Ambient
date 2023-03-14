#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
constexpr int kMaxEnergy = 500;
constexpr int kMoveCost = 10;
constexpr int kPhotosynthesis = 25;
constexpr int kAttackCoefficient = 4; // 1/4 * currentEnergy
constexpr int kAttackCost = 10;       // 1/10 * currentEnergy
constexpr int kPrise = 200;
class Cell
{
private:
    Point position;
    double currentEnergy;
    double aggressiveness = 0;
    int stepsCount = ;
    Genotype genotype;
    bool isAliveStatus = true;
    
public:
    Cell();
    Cell(Point startingPosition);

    Point getPosition() const;
    double getCurrentEnergy();
    double getAggressiveness();
    Genotype getGenotype();
    bool isAlive();

    void setCurrentEnergy(double count){currentEnergy = count;}
    void setIsAlive(bool status){isAliveStatus = status;}
    void move(int direction);
    void photosynthesis();
    void act(Matrix& inputs);
    void attack(Cell & opponent);
    // void duplicate();
};

#endif // CELL_H
