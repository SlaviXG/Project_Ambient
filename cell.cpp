#include "cell.h"

namespace environment
{

    void Cell::move(int direction)
    {
        switch (direction)
        {
        case 0:
            position.i--;
            break;
        case 1:
            position.i--;
            position.j++;
            break;
        case 2:
            position.j++;
            break;
        case 3:
            position.i++;
            position.j++;
            break;
        case 4:
            position.i++;
            break;
        case 5:
            position.i++;
            position.j--;
            break;
        case 6:
            position.j--;
            break;
        case 7:
            position.i--;
            position.j--;
            break;
        default:
            return;
        }

        currentEnergy -= kMoveCost;
        isAliveStatus = currentEnergy > 0;
    }

    void increaseEnergy(double &currentEnergy, double count)
    {
        currentEnergy += count;
        if (currentEnergy > kMaxEnergy)
            currentEnergy = kMaxEnergy;
    }

    void Cell::photosynthesis()
    {
        increaseEnergy(currentEnergy, kPhotosynthesis);
    }

    void Cell::attack(Cell &opponent)
    {
        double opponentEnergy = opponent.getCurrentEnergy();
        opponentEnergy -= currentEnergy / kAttackCoefficient;
        currentEnergy -= currentEnergy / kAttackCost;

        aggressiveness += 0.1;
        if (aggressiveness > 1)
            aggressiveness == 1;

        if (opponentEnergy <= 0)
        {
            opponent.setIsAlive(false);
            increaseEnergy(currentEnergy, kPrise);
        }
    }

    Cell::Cell(Point startingPosition, Environment* environment)
        : Frame(startingPosition, environment)
    {
        genotype = Genotype();
        aggressiveness = 0;
        currentEnergy = kMaxEnergy;
    }
    Cell::Cell(Cell &mother, Point freePosition)
    {
        Genotype g = Genotype(mother.getGenotype());

        genotype = g;
        aggressiveness = mother.getAggressiveness();
        currentEnergy = mother.getCurrentEnergy() / 2;
        this->position = freePosition;
    }

    double Cell::getAggressiveness() const
    {
        return aggressiveness;
    }
    double Cell::getCurrentEnergy() const 
    {
        return currentEnergy;
    }
    Genotype Cell::getGenotype() const
    {
        return genotype;
    }
    bool Cell::isAlive()
    {
        return isAliveStatus;
    }

    void Cell::act(std::vector<double> inputs)
    {
        if (isAliveStatus == 0) // Remove or delete cell
            return;

        inputs.push_back(currentEnergy);
        inputs.push_back(aggressiveness);

        Matrix mInputs(0, 25);
        mInputs.addColumn(Row(inputs));

        int indexOfAction = genotype.makeChoise(mInputs, position);

        if (indexOfAction < 0)
        {
            std::cout << "negative action!" << std::endl;
        }

        if (indexOfAction < 8)
        {
            move(indexOfAction);
        }
        else if (indexOfAction == 8)
        {
            photosynthesis();
        }
        else if (indexOfAction == 9) // find opponent!!!
        {
            // attack(opponent);
        }
        else if (indexOfAction == 10)
        {
        }
    }

}