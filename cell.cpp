#include "cell.h"
#include "Environment.h"

namespace environment
{
    void Cell::move(int direction)
    {
        auto oldPos = position;

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

        assert(environment != nullptr);
        environment->updateCellPosition(this, oldPos);

        if(currentEnergy <= 0)
        {
            die();
            return;
        }
    }

    int Cell::bestPossibleChoiceIndex(Matrix& outputs, Matrix& inputs)
    {
        Point cellPosition = position;
        double maxValue = outputs[0][0];
        int index = 0;
        Point freePosition;

        for (int i = 1; i < outputs.getY(); i++) {
            if (maxValue < outputs[i][0]) {
                index = i;
                maxValue = outputs[i][0];
            }
        }

        switch (index)
        {
            case kMoveUp:
                if (cellPosition.i == 0) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[7][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveUpRight:
                if (cellPosition.i == 0 || cellPosition.j == genotype::kMapSize - 1)             // mapSIze == 100
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[8][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveRight:
                if (cellPosition.j == genotype::kMapSize - 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[12][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveRightDown:
                if (cellPosition.i == genotype::kMapSize - 1 || cellPosition.j == genotype::kMapSize - 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[17][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveDown:
                if (cellPosition.i == genotype::kMapSize - 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[16][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeftDown:
                if (cellPosition.i == genotype::kMapSize - 1 || cellPosition.j == 0) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[15][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeft:
                if (cellPosition.j == 0) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[11][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeftUp:
                if (cellPosition.i == 0 || cellPosition.j == 0) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                if (inputs[6][0] == 1) {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackUp:
                if(inputs[7][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackUpRight:
                if(inputs[8][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackRight:
                if(inputs[12][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackRightDown:
                if(inputs[17][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackDown:
                if(inputs[16][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeftDown:
                if(inputs[15][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeft:
                if(inputs[11][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeftUp:
                if(inputs[6][0] == 0)
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kDuplication:
                freePosition = environment->randomFreePosition(position);
                // 0.5 = 1/2 maxEnergy
                if (inputs[24][0] < 0.5 || freePosition.i == -1)                     // indexation ? ; 300 == min_star_energy - 100
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kPhotosynthesis:
                if (inputs[24][0] == maxEnergy )                     // indexation ? ; 300 == min_star_energy - 100
                {
                    outputs[index][0] = -10;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
                default:
                        return index;
        }
    }

    int Cell::makeChoice(Matrix& inputs)
    {
        const int countOfIteration = this->genotype.getCountOfLayers();
        Matrix temp = genotype::ReLU(genotype.getWeightsMatrixByIndex(0) * inputs + genotype.getBaesMatrixByIndex(0));
        for(int i = 1; i < countOfIteration; i++)
        {
            temp = genotype::ReLU(genotype.getWeightsMatrixByIndex(i) * temp + genotype.getBaesMatrixByIndex(i));
        }

        //Matrix firstLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(1) * inputs + genotype.getBaesMatrixByIndex(1));
        //Matrix secondLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(2) * firstLayer + genotype.getBaesMatrixByIndex(2));
        //Matrix thirdLayer = genotype::ReLU(genotype.getWeightsMatrixByIndex(3) * secondLayer + genotype.getBaesMatrixByIndex(3));
        //Matrix outputs = genotype.getWeightsMatrixByIndex(4) * thirdLayer + genotype.getBaesMatrixByIndex(4);

        //return bestPossibleChoiceIndex(outputs, inputs);
        return bestPossibleChoiceIndex(temp, inputs);
    }

    void increaseEnergy(double &currentEnergy, double maxEnergy, double count)
    {
        currentEnergy += count;
        if (currentEnergy > maxEnergy)
            currentEnergy = maxEnergy;
    }

    void Cell::photosynthesis()
    {
        increaseEnergy(currentEnergy, maxEnergy, kPhotosynthesisAdd);
    }

    void Cell::attack(int action)
    {
        Point currentPosition = position;

        if(action == kAttackUp)
        {
            currentPosition.i--;
        }
        else if(action == kAttackUpRight)
        {
            currentPosition.i--;
            currentPosition.j++;
        }
        else if(action == kAttackRight)
        {
            currentPosition.j++;
        }
        else if(action == kAttackRightDown)
        {
            currentPosition.i++;
            currentPosition.j++;
        }
        else if(action == kAttackDown)
        {
            currentPosition.i++;
        }
        else if(action == kAttackLeftDown)
        {
            currentPosition.i++;
            currentPosition.j--;
        }
        else if(action == kAttackLeft)
        {
            currentPosition.j--;
        }
        else
        {
            currentPosition.i--;
            currentPosition.j--;
        }

        Cell* opponent = environment->getCell(currentPosition); // TODO
        double opponentEnergy = opponent->getCurrentEnergy();
        opponentEnergy -= currentEnergy * kAttackCoefficient;
        currentEnergy -= currentEnergy * kAttackCost;
        opponent->setCurrentEnergy(opponentEnergy);

        aggressiveness += 0.1;
        stepsCount = kSteps;

        if (aggressiveness >= 1)
            aggressiveness = 0.99;

        if (opponentEnergy <= 0)
        {
            opponent->die();                              //!!!!
            increaseEnergy(currentEnergy, maxEnergy, kPrise);
        }
    }

    void Cell::duplicate()
    {
        Point freePosition = environment->randomFreePosition(position);
        currentEnergy = currentEnergy * 0.4;
        this->environment->AddCell(new Cell(*this, freePosition));
        this->genotype.mutate();
    }

    Cell::Cell(Point startingPosition, Environment* environment)
        : Frame(startingPosition, environment)
    {
        genotype = genotype::Genotype(std::vector<int>{20,20,20,20,20});
        aggressiveness = RandomGenerator::generateRandomDoubleNumber(0,1);
        maxEnergy = RandomGenerator::generateRandomIntNumber(kMinEnergy,kMaxEnergy);
        currentEnergy = maxEnergy;
    }

    Cell::Cell(Cell &mother, Point freePosition) : Frame(mother)
    {
        genotype = genotype::Genotype(mother.getGenotype());
        aggressiveness = mother.getAggressiveness();
        currentEnergy = mother.getCurrentEnergy();
        maxEnergy = mother.getMaxEnergy();
        position = freePosition;
    }

    // countOfWeights - Additional vector, which contain countOfWeights in i's layer(from 1 to n-1)
    Cell::Cell(Point startingPosition, std::vector<int> countOfWeights, Environment* environment): Frame(startingPosition, environment)
    {
        genotype = genotype::Genotype(countOfWeights);
        aggressiveness = RandomGenerator::generateRandomDoubleNumber(0,1);
        maxEnergy = RandomGenerator::generateRandomIntNumber(kMinEnergy,kMaxEnergy);
        currentEnergy = maxEnergy;
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

    genotype::Genotype Cell::getGenotype() const
    {
        return this->genotype;
    }

    bool Cell::isAlive() const
    {
        return isAliveStatus;
    }

    int Cell::getStepsCount() const
    {
        return this->stepsCount;
    }

    actions Cell::act() //std::vector<double> inputs
    {
        if (isAliveStatus == 0 || numberOfMovesToDeath == 0) // Remove or delete cell
        {
            die();
            return kCellIsDead;
        }

        numberOfMovesToDeath--;
        std::vector<double> inputs;
        std::vector<bool> vision;
        assert(environment!=nullptr);
        vision = environment->getVisionField(position);

        for(int i = 0; i < vision.size(); i++)
        {
            inputs.push_back(vision[i]);
        }

        inputs.push_back(currentEnergy / maxEnergy);
        inputs.push_back(aggressiveness);
        Matrix mInputs(1, this->genotype.getWeightsMatrixByIndex(0).getX());
        mInputs.addColumn(inputs);

        int indexOfAction = makeChoice(mInputs);

        if (indexOfAction < 0)
        {
            std::cout << "negative action!" << std::endl;
        }

        if (indexOfAction < kPhotosynthesis)                  //  0 - 7 <- 8 directions for moving
        {
            move(indexOfAction);
            return kMoveUp;
        }

        else if (indexOfAction == kPhotosynthesis)
        {
            photosynthesis();
            return kPhotosynthesis;
        }

        else if (indexOfAction == kDuplication)
        {
            duplicate();
            return kDuplication;
        }

        else
        {
            attack(indexOfAction);
            return kAttackUp;
        }
    }
}
