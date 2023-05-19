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
            this->totalScore -= 100;
            die();
            return;
        }
    }


    void Cell::evaluateAction(int action)
    {
        if(action <= 7)     // move
        {
            this->totalScore++;
        }

        else if(action == actions::kPhotosynthesis)
        {
            this->totalScore += 2;
        }

        else if(action <= 16) // attack
        {
            this->totalScore += 20;
        }
        else if(action == actions::kDuplication)
        {
            this->totalScore += 100;
        }
    }

    int foo(double value1, double value2, double value3)
    {
        assert(value1 >= 0);
        assert(value2 >= 0);
        assert(value3 >= 0);

        double sum = value1 + value2 + value3;
        double r = RandomGenerator::generateRandomDoubleNumber(0,sum);

        if(r <= value3)
            return 3;
        else if(r <= (value3 + value2))
            return 2;
        else
            return 1;

    }

    int Cell::bestPossibleChoiceIndex(Matrix& outputs, Matrix& inputs)
    {
        Point cellPosition = position;
        //double maxValue = outputs[0][0];
        //int index = 0;
        int indexP1 = -1;
        int indexP2 = -1;
        int indexP3 = -1;

        double valueP1 = -100000;           // priority 1
        double valueP2 = -100000;           // priority 2
        double valueP3 = -100000;

        Point freePosition = environment->randomFreePosition(position);
        for (int i = 0; i < outputs.getY(); i++)
        {
            if(valueP3 < outputs[i][0])
            {
               valueP3 = outputs[i][0];
               indexP3 = i;
            }
            if(valueP2 < valueP3)
            {
                double temp = valueP3;
                int tempIndex = indexP3;
                valueP3 = valueP2;
                indexP3 = indexP2;
                valueP2 = temp;
                indexP2 = tempIndex;
            }
            if(valueP1 < valueP2)
            {
                double temp = valueP2;
                int tempIndex = indexP2;
                valueP2 = valueP1;
                indexP2 = indexP1;
                valueP1 = temp;
                indexP1 = tempIndex;
            }
        }
        int index = 0;

        switch(foo(valueP1, valueP2, valueP3)){
            case 1:
                index = indexP1;
                break;
            case 2:
                index = indexP2;
                break;
            case 3:
                index = indexP3;
                break;
        }
       // for (int i = 1; i < outputs.getY(); i++) {
       //     if (maxValue < outputs[i][0]) {
       //         index = i;
       //         maxValue = outputs[i][0];
       //     }
       // }

        switch (index)
        {
            case kMoveUp:
                if (cellPosition.i == 0 || inputs[7][0] == 1) {
                    outputs[kMoveUp][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveUpRight:
                if (cellPosition.i == 0 || cellPosition.j == (environment->getWidth() - 1) || inputs[8][0] == 1)
                {
                    outputs[kMoveUpRight][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveRight:
                if (cellPosition.j == (environment->getWidth() - 1) || inputs[12][0] == 1) {
                    outputs[kMoveRight][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveRightDown:
                if (cellPosition.i == (environment->getHeight() - 1) || cellPosition.j == (environment->getWidth() - 1) || inputs[17][0] == 1) {
                    outputs[kMoveRightDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveDown:
                if (cellPosition.i == (environment->getHeight() - 1) || inputs[16][0] == 1) {
                    outputs[kMoveDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeftDown:
                if (cellPosition.i == (environment->getHeight() - 1) || cellPosition.j == 0 || inputs[15][0] == 1) {
                    outputs[kMoveLeftDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeft:
                if (cellPosition.j == 0 || inputs[11][0] == 1) {
                    outputs[kMoveLeft][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kMoveLeftUp:
                if (cellPosition.i == 0 || cellPosition.j == 0 || inputs[6][0] == 1) {
                    outputs[kMoveLeftUp][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackUp:
                if(inputs[7][0] == 0)
                {
                    outputs[kAttackUp][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackUpRight:
                if(inputs[8][0] == 0)
                {
                    outputs[kAttackUpRight][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackRight:
                if(inputs[12][0] == 0)
                {
                    outputs[kAttackRight][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackRightDown:
                if(inputs[17][0] == 0)
                {
                    outputs[kAttackRightDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackDown:
                if(inputs[16][0] == 0)
                {
                    outputs[kAttackDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeftDown:
                if(inputs[15][0] == 0)
                {
                    outputs[kAttackLeftDown][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeft:
                if(inputs[11][0] == 0)
                {
                    outputs[kAttackLeft][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kAttackLeftUp:
                if(inputs[6][0] == 0)
                {
                    outputs[kAttackLeftUp][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kDuplication:
                //freePosition = environment->randomFreePosition(position);

                if (inputs[24][0] < 0.9 || freePosition.i == -1)
                {
                    outputs[kDuplication][0] = -1000000;
                    return bestPossibleChoiceIndex(outputs, inputs);
                }
                return index;
            case kPhotosynthesis:
                if (inputs[24][0] >= 0.99 )                     // can Photosynthesis if energy is low than 99 procent
                {
                    outputs[kPhotosynthesis][0] = -1000000;
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
        stepsCount--;

        if(stepsCount == 0)
        {
            if(aggressiveness >= 0.05)
                aggressiveness -= 0.05;
            stepsCount = kSteps;
        }
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

        Cell* opponent = environment->getCell(currentPosition);
        double opponentEnergy = opponent->getCurrentEnergy();
        opponentEnergy -= (currentEnergy * kAttackCoefficient + minDamage);
        currentEnergy -= currentEnergy * kAttackCost;
        opponent->setCurrentEnergy(opponentEnergy);

        aggressiveness += 0.05;
        stepsCount = kSteps;

        if (aggressiveness >= 1)
            aggressiveness = 0.99;

        if (opponentEnergy <= 0)
        {
            opponent->currentEnergy -= 40;          //&&&&&&&&&&&
            opponent->die();
            increaseEnergy(currentEnergy, maxEnergy, kPrise);
        }
    }

    void Cell::duplicate()
    {
        Point freePosition = environment->randomFreePosition(position);
        currentEnergy = (currentEnergy - kDuplicationCost) * 0.5;
        this->environment->AddCell(new Cell(*this, freePosition));
    }

    Cell::Cell(Point startingPosition, Environment* environment)
        : Frame(startingPosition, environment)
    {
        genotype = genotype::Genotype(std::vector<int>{10,10});
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

    // Constructor for next-generation cell (genotype pulled from GenePool)
    Cell::Cell(Point startingPosition, genotype::Genotype *genotype, Environment* environment) : Frame(startingPosition, environment)
    {
        this->genotype = *genotype;
        aggressiveness = RandomGenerator::generateRandomDoubleNumber(0,1);
        maxEnergy = RandomGenerator::generateRandomIntNumber(kMinEnergy,kMaxEnergy);
        currentEnergy = maxEnergy;
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
    int Cell::getTotalScore() const
    {
        return this->totalScore;
    }
    actions Cell::act() //std::vector<double> inputs
    {

        if (numberOfMovesToDeath == 0) // Remove or delete cell
        {
            this->totalScore -= 20;
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

        evaluateAction(indexOfAction);

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
