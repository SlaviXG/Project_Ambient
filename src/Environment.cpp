#include "../include/Environment.h"

#include "../include/frame.h"
#include "../include/cell.h"
#include "../include/GameController.h"
#include "../include/genepool.h"

namespace environment
{
    int kEnvironmentWidth = 1000;
    int kEnvironmentHeight = 1000;

    int kMaxEnergy = 2000;
    int kMinEnergy = 1600;

    int kSteps = 5;                 //
    int kMoveCost = 5;              // count of energy, that cell will loose after move
    int kPhotosynthesisAdd = 25;    // count of energy, that cell will recieve after Photosynthes
    float kAttackCoefficient = 0.5; // opponent energy -= currentEnergy * kAC + minDamage
    float kAttackCost = 0.01;       // 1/10 * currentEnergy
    int kDuplicationCost = 1200;
    int kPrise = 500;        // + energy after killing
    int kMovesToDeath = 800; // every cell can make at max 250 actions
    int kMinDamage = 1000;
    int kDelay = 10;

    // Constructors / Destructors
    Environment::Environment(int WIDTH, int HEIGHT, controller::CellInteractor *interactor, genepool::GenePool *pool)
        : WIDTH(WIDTH), HEIGHT(HEIGHT), interactor(interactor)
    {
        frameMatrix.resize(HEIGHT);

        for (auto &row : frameMatrix)
        {
            row.resize(WIDTH, nullptr);
        }
        this->pool = pool;
        this->time = 0.0;
    }

    Environment::~Environment()
    {
        for (auto line : frameMatrix)
            for (auto frame : line)
                delete frame;
    }

    // Enviroment Actions:
    void Environment::tickTime()
    {
        this->time += 0.01;
    }

    bool Environment::isDay() const
    {
        return (static_cast<int>(time * 100) % 2 ? false : true);
    }

    bool Environment::isNight() const
    {
        return (static_cast<int>(time * 100) % 2 ? true : false);
    }

    // Set:
    void Environment::setCellInteractor(controller::CellInteractor *interactor)
    {
        this->interactor = interactor;
    }

    // Get:
    double Environment::getTime() const
    {
        return this->time;
    }

    int Environment::getWidth() const
    {
        return WIDTH;
    }

    int Environment::getHeight() const
    {
        return HEIGHT;
    }

    Frame *Environment::getFrame(const Point &point) const
    {
        Q_ASSERT(checkPositionCorrectness(point));
        return frameMatrix[point.i][point.j];
    }

    std::vector<Cell *> &Environment::getCells()
    {
        return cells;
    }

    bool Environment::checkPositionCorrectness(const Point &point) const
    {
        return !(point.i < 0 || point.i >= HEIGHT || point.j < 0 || point.j >= WIDTH);
    }

    genepool::GenePool *Environment::getGenePool()
    {
        return pool;
    }

    size_t Environment::getCellNumber() const
    {
        return cells.size();
    }

    unsigned int Environment::getMaxCellCount()
    {
        return this->pool->get_pool_maxsize();
    }

    Cell *Environment::getCell(const Point &point) const
    {
        Q_ASSERT(checkPositionCorrectness(point));
        Frame *frame = frameMatrix[point.i][point.j];
        return dynamic_cast<Cell *>(frame);
    }

    void Environment::updateCellPosition(Cell *cell, const Point &oldPos)
    {
        Q_ASSERT(checkPositionCorrectness(oldPos));
        Q_ASSERT(checkPositionCorrectness(cell->getPosition()));

        frameMatrix[oldPos.i][oldPos.j] = nullptr;
        auto newPos = cell->getPosition();
        frameMatrix[newPos.i][newPos.j] = cell;
    }

    std::vector<bool> Environment::getVisionField(const Point &viewPoint) const
    {
        Q_ASSERT(checkPositionCorrectness(viewPoint));

        std::vector<bool> vec;
        // vec.reserve(25);

        for (int i = viewPoint.i - 2; i <= viewPoint.i + 2; ++i)
        {
            for (int j = viewPoint.j - 2; j <= viewPoint.j + 2; ++j)
            {
                Point checkPoint{i, j};
                if (!checkPositionCorrectness(checkPoint))
                {
                    vec.push_back(false);
                }
                else if (checkPoint.i != viewPoint.i || checkPoint.j != viewPoint.j) // observation cell exception
                {
                    vec.push_back(this->frameMatrix[i][j] != nullptr);
                }
            }
        }

        return vec;
    }

    Cell *Environment::AddCell(Cell *cell)
    {
        // Check whether the cell already exists
        Q_ASSERT(std::find(cells.begin(), cells.end(), cell) == cells.end());
        Q_ASSERT(checkPositionCorrectness(cell->getPosition()));

        cells.push_back(cell);
        auto pos = cell->getPosition();
        frameMatrix[pos.i][pos.j] = cell;
        if (interactor != nullptr)
            interactor->addCell(cell);

        return cell;
    }

    Cell *Environment::AddCell(const Point &point)
    {
        Q_ASSERT(checkPositionCorrectness(point));
        Q_ASSERT(frameMatrix[point.i][point.j] == nullptr);

        Cell *cell = new Cell(point, this);
        cells.push_back(cell);
        frameMatrix[point.i][point.j] = cell;

        return cell;
    }

    // New method
    Cell *Environment::AddCell(const Point &point, std::vector<int> countOfWeights)
    {
        Q_ASSERT(checkPositionCorrectness(point));
        Q_ASSERT(frameMatrix[point.i][point.j] == nullptr);

        Cell *cell = new Cell(point, countOfWeights, this);
        cells.push_back(cell);
        frameMatrix[point.i][point.j] = cell;

        return cell;
    }

    Cell *Environment::AddCell(const Point &point, genotype::Genotype *genotype)
    {
        Cell *cell = new Cell(point, genotype, this);
        cells.push_back(cell);
        frameMatrix[point.i][point.j] = cell;

        return cell;
    }

    void Environment::InvalidateCell(Cell *cell)
    {
        auto pos = cell->getPosition();

        Q_ASSERT(checkPositionCorrectness(pos));
        Q_ASSERT(this->getCell(pos) == cell);

        frameMatrix[pos.i][pos.j] = nullptr;
        if (pool)
        {
            pool->AddToPool(cell);
        }
    }

    void Environment::RemoveCell(Cell *cell)
    {
        // Q_ASSERT(frameMatrix[cell->getPosition().i][cell->getPosition().j] == nullptr);

#ifdef QT_DEBUG
        if (frameMatrix[cell->getPosition().i][cell->getPosition().j] != nullptr)
        {
            for (const auto &row : this->frameMatrix)
                for (const auto &frame : row)
                    Q_ASSERT(frame != cell);
        }
#endif

        // if (frameMatrix[cell->getPosition().i][cell->getPosition().j] != nullptr)
        //  this->InvalidateCell(cell);
        Q_ASSERT(std::find(cells.begin(), cells.end(), cell) != cells.end());

        cells.erase(std::remove(cells.begin(), cells.end(), cell), cells.end());

        if (interactor != nullptr)
            interactor->removeCell(cell);

        delete cell;
    }

    void Environment::RemoveAllCells()
    {
        for (unsigned int i = 0; i < cells.size(); i++)
        {
            if (cells[i]->isAlive())
            {
                cells[i]->die();
            }
        }
    }

    Point Environment::randomFreePosition(const Point &point) const
    {
        Q_ASSERT(checkPositionCorrectness(point));

        constexpr int kAttemptCount = 50;
        Point randPoint;
        for (size_t i = 0; i < kAttemptCount; i++)
        {
            randPoint.i = RandomGenerator::generateRandomIntNumber(point.i - 1, point.i + 1);
            randPoint.j = RandomGenerator::generateRandomIntNumber(point.j - 1, point.j + 1);
            /*bool switcher = RandomGenerator::generateRandomIntNumber(0, 1);
            if(switcher){
                randPoint.i = point.i - 1;
            }
            else{
                randPoint.i = point.i + 1;
            }
            switcher = RandomGenerator::generateRandomIntNumber(0, 1);
            std::cout << switcher << std::endl;
            if(switcher){
                randPoint.j = point.j - 1;
            }
            else{
                randPoint.j = point.j + 1;
            }*/
            if (checkPositionCorrectness(randPoint) && (randPoint.i != point.i || randPoint.j != point.j))
                if (frameMatrix[randPoint.i][randPoint.j] == nullptr)
                    return randPoint;
        }
        return {-1, -1};
    }

    Point Environment::getRandomFreePosOnMap(unsigned int attemp_count) const
    {
        Point rand_point;
        for (unsigned int i = 0; i < attemp_count; i++)
        {
            rand_point.i = RandomGenerator::generateRandomIntNumber(0, this->getWidth() - 1);
            rand_point.j = RandomGenerator::generateRandomIntNumber(0, this->getHeight() - 1);
            if (checkPositionCorrectness(rand_point) && !frameMatrix[rand_point.i][rand_point.j])
            {
                return rand_point;
            }
        }
        return {-1, -1};
    }

    void Environment::generateCells(int N /*, controller::GameController *cont*/)
    {
        for (int i = 0; i < N; i++)
        {
            Point point = this->getRandomFreePosOnMap();
            if (point.i != -1)
            {
                if (pool && pool->get_pool_cursize() != 0 && i < pool->get_pool_cursize())
                {
                    genotype::Genotype *gen = pool->getGenotype(i);
                    gen->mutate((double)i / N);
                    interactor->addCell(point, gen);
                }
                else
                {
                    interactor->addCell(point);
                }
            }
            else
            {
                continue;
            }
        }
    }

    void Environment::ValidateEnvironment()
    {

        // FOR TESTING
        if (cur_step_count >= max_step_count_before_reset)
        {

            // DEBUG
            pool->print();

            RemoveAllCells();
            generateCells(pool->get_pool_maxsize());
            pool->clear_pool();
            cur_step_count = 0;
        }

        unsigned int cell_num = getCellNumber();
        if (!cell_num || cell_num >= population_upper_limit * pool->get_pool_maxsize())
        {
            // Repopulate

            // DEBUG
            pool->print();

            RemoveAllCells();
            generateCells(pool->get_pool_maxsize());
            pool->clear_pool();
            cur_step_count = 0;
        }
        cur_step_count++;
    }

    void Environment::loadConfiguration(Configuration &config)
    {
        kEnvironmentWidth = config.get<int>("kEnvironmentWidth", kEnvironmentWidth);
        WIDTH = kEnvironmentWidth;
        kEnvironmentHeight = config.get<int>("kEnvironmentHeight", kEnvironmentHeight);
        HEIGHT = kEnvironmentHeight;

        frameMatrix.resize(HEIGHT);
        for (auto &row : frameMatrix)
        {
            row.resize(WIDTH, nullptr);
        }

        kMaxEnergy = config.get<int>("kMaxEnergy", kMaxEnergy);
        kMinEnergy = config.get<int>("kMinEnergy", kMinEnergy);

        kSteps = config.get<int>("kSteps", kSteps);
        kMoveCost = config.get<int>("kMoveCost", kMoveCost);
        kPhotosynthesisAdd = config.get<int>("kPhotosynthesisAdd", kPhotosynthesisAdd);
        kAttackCoefficient = config.get<float>("kAttackCoefficient", kAttackCoefficient);
        kAttackCost = config.get<float>("kAttackCost", kAttackCost);
        kDuplicationCost = config.get<int>("kDuplicationCost", kDuplicationCost);
        kPrise = config.get<int>("kPrise", kPrise);
        kMovesToDeath = config.get<int>("kMovesToDeath", kMovesToDeath);
        kMinDamage = config.get<int>("kMinDamage", kMinDamage);
        kDelay = config.get<int>("kDelay", kDelay);
    }

    void Environment::saveConfiguration(Configuration &config) const
    {
        config.set<int>("kEnvironmentWidth", kEnvironmentWidth);
        config.set<int>("kEnvironmentHeight", kEnvironmentHeight);

        config.set<int>("kMaxEnergy", kMaxEnergy);
        config.set<int>("kMinEnergy", kMinEnergy);

        config.set<int>("kSteps", kSteps);
        config.set<int>("kMoveCost", kMoveCost);
        config.set<int>("kPhotosynthesisAdd", kPhotosynthesisAdd);
        config.set<float>("kAttackCoefficient", kAttackCoefficient);
        config.set<float>("kAttackCost", kAttackCost);
        config.set<int>("kDuplicationCost", kDuplicationCost);
        config.set<int>("kPrise", kPrise);
        config.set<int>("kMovesToDeath", kMovesToDeath);
        config.set<int>("kMinDamage", kMinDamage);
        config.set<int>("kDelay", kDelay);
    }
}
