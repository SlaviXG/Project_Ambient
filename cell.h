#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
constexpr int kMaxEnergy = 500;
constexpr int kSteps = 20;
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
    double aggressiveness;
    Genotype genotype;
    int stepsCount = kSteps;
    bool isAliveStatus = true;
    
public:
    Cell();
    Cell(Point startingPosition);
    Cell(Cell& mother, Point freePosition);

    Point getPosition() const;
    double getCurrentEnergy();
    double getAggressiveness();
    Genotype getGenotype();
    bool isAlive();

    void setCurrentEnergy(double count){currentEnergy = count;}
    void setIsAlive(bool status){isAliveStatus = status;}
    void setPosition(Point newPosition){position = newPosition;}

    void move(int direction);
    void photosynthesis();
    void attack(Cell & opponent);

    void act(std::vector<double> inputs);
    // void duplicate();
};

#endif // CELL_H
