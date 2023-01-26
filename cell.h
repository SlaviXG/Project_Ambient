#ifndef CELL_H
#define CELL_H

#include "Genotype.h"
constexpr int kMaxEnergy = 500;

class Cell
{
private:
    Point position;
    double currentEnergy;
    Genotype genotype;
    
public:
    Cell();
    Cell(Point startingPosition);

    Point getPosition() const;
};

#endif // CELL_H
