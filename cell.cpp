#include "cell.h"
#include "Environment.h"
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

    int Cell::bestPossibleChoiceIndex(Matrix outputs, Matrix inputs)
    {
        genotype::Point cellPosition = position;
        int maxValue = outputs[0][0];
        int index = 0;

        for (int i = 1; i < outputs.getY(); i++) {
            if (maxValue < outputs[i][0]) {
                index = i;
                maxValue = outputs[i][0];
            }
        }

        switch (index)
        {
            case 0:
                if (cellPosition.i == 0) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[7][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 1:
                if (cellPosition.i == 0 || cellPosition.j == genotype::kMapSize - 1)             // mapSIze == 100
                {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[8][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 2:
                if (cellPosition.j == genotype::kMapSize - 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[12][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 3:
                if (cellPosition.i == genotype::kMapSize - 1 || cellPosition.j == genotype::kMapSize - 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[17][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 4:
                if (cellPosition.i == genotype::kMapSize - 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[16][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 5:
                if (cellPosition.i == genotype::kMapSize - 1 || cellPosition.j == 0) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[15][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 6:
                if (cellPosition.j == 0) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[11][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 7:
                if (cellPosition.i == 0 || cellPosition.j == 0) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[6][0] == 1) {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case 9:
                if (genotype::opponentIsNearby(inputs))
                    return index;
                else
                    outputs[index][0] = 0;
                return bestPossibleChoiceIndex(outputs, inputs);
            case 10:
                if (inputs[24][0] < 300 )                     // indexation ? ; 300 == min_star_energy - 100
                {
                    outputs[index][0] = 0;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }

                return index;
                    default:
                        return index;
        }
    }

    int Cell::makeChoice(Matrix inputs)
    {
        Matrix firstLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(1) * inputs + genotype.getBaesMatrixByIndex(1));
        Matrix secondLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(2) * firstLayer + genotype.getBaesMatrixByIndex(2));
        Matrix thirdLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(3) * secondLayer + genotype.getBaesMatrixByIndex(3));
        Matrix outputs = genotype.getWeightsMatrixByIndex(4) * thirdLayer + genotype.getBaesMatrixByIndex(4);

        return bestPossibleChoiceIndex(outputs, inputs);
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
            aggressiveness = 1;

        if (opponentEnergy <= 0)
        {
            opponent.setIsAlive(false);
            increaseEnergy(currentEnergy, kPrise);
        }
    }
    
    void Cell::duplicate(Environment* environment)                    
    {
        genotype::Point freePosition = environment->randomFreePosition(position);
        environment->AddCell(new Cell(*this, freePosition));
        genotype = genotype::Genotype(genotype);
    }

    Cell::Cell(genotype::Point startingPosition, Environment* environment)
        : Frame(startingPosition, environment)
    {
        genotype = genotype::Genotype();
        aggressiveness = RandomGenerator::generateRandomNumber(0,1);
        maxEnergy = RandomGenerator::generateRandomNumber(kMinEnergy,kMaxEnergy);
        currentEnergy = maxEnergy;
    }

    Cell::Cell(Cell &mother, genotype::Point freePosition)
    {
        genotype::Genotype g = genotype::Genotype(mother.getGenotype());

        genotype = g;
        aggressiveness = mother.getAggressiveness();
        currentEnergy = mother.getCurrentEnergy() / 2;
        maxEnergy = mother.getMaxEnergy();
        position = environment->randomFreePosition(this->getPosition());
    }

    double Cell::getAggressiveness() const
    {
        return aggressiveness;
    }

    double Cell::getCurrentEnergy() const 
    {
        return currentEnergy;
    }

    double Cell::getMaxEnergy() const
    {
        return maxEnergy;
    }

    genotype::Genotype Cell::getGenotype()
    {
        return genotype;
    }

    bool Cell::isAlive()
    {
        return isAliveStatus;
    }

    void Cell::act(std::vector<double> inputs, Environment* environment)
    {
        if (isAliveStatus == 0) // Remove or delete cell
            return;

        inputs.push_back(currentEnergy);
        inputs.push_back(aggressiveness);

        Matrix mInputs(0, 25);
        mInputs.addColumn(Row(inputs));

        int indexOfAction = makeChoice(mInputs);

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
            // TODO attack(opponent);
        }
        else if (indexOfAction == 10)
        {
            duplicate(environment);
        }
    }
}
