#include "Environment.h"

#include <cassert>

#include "frame.h"
#include "cell.h"
#include "GameController.h"
#include "genepool.h"

namespace environment
{
    // Constructors / Destructors
    Environment::Environment(int WIDTH, int HEIGHT, controller::CellInteractor *interactor, genepool::GenePool* pool)
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

    Cell* Environment::getCell(const Point& point) const {
        assert(checkPositionCorrectness(point));
        Frame* frame = frameMatrix[point.i][point.j];
        return dynamic_cast<Cell*>(frame);
    }

    void Environment::updateCellPosition(Cell *cell, const Point &oldPos)
    {
        assert(checkPositionCorrectness(oldPos));
        assert(checkPositionCorrectness(cell->getPosition()));
        frameMatrix[oldPos.i][oldPos.j] = nullptr;
        auto newPos = cell->getPosition();
        frameMatrix[newPos.i][newPos.j] = cell;
    }

    std::vector<bool> Environment::getVisionField(const Point &viewPoint) const
    {
        assert(checkPositionCorrectness(viewPoint));

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
        assert(std::find(cells.begin(), cells.end(), cell) == cells.end());
        assert(checkPositionCorrectness(cell->getPosition()));

        cells.push_back(cell);
        auto pos = cell->getPosition();
        frameMatrix[pos.i][pos.j] = cell;
        if (interactor != nullptr)
            interactor->addCell(cell);

        return cell;
    }

    Cell *Environment::AddCell(const Point &point)
    {
        assert(checkPositionCorrectness(point));
        assert(frameMatrix[point.i][point.j] == nullptr);

        Cell *cell = new Cell(point, this);
        cells.push_back(cell);
        frameMatrix[point.i][point.j] = cell;

        return cell;
    }

    // New method
    Cell *Environment::AddCell(const Point &point, std::vector<int> countOfWeights)
    {
        assert(checkPositionCorrectness(point));
        assert(frameMatrix[point.i][point.j] == nullptr);

        Cell *cell = new Cell(point,countOfWeights, this);
        cells.push_back(cell);
        frameMatrix[point.i][point.j] = cell;

        return cell;
    }

    void Environment::InvalidateCell(Cell *cell)
    {
        auto pos = cell->getPosition();

        assert(checkPositionCorrectness(pos));
        assert(this->getCell(pos) == cell);
        if(pool){
            pool->AddToPool(cell);
        }
        frameMatrix[pos.i][pos.j] = nullptr;
    }

    void Environment::RemoveCell(Cell* cell)
    {
        // FIX: Why?

        //assert(frameMatrix[cell->getPosition().i][cell->getPosition().j] == nullptr);
        //if (frameMatrix[cell->getPosition().i][cell->getPosition().j] != nullptr)
            // this->InvalidateCell(cell);
        assert(std::find(cells.begin(), cells.end(), cell) != cells.end());

        cells.erase(std::remove(cells.begin(), cells.end(), cell), cells.end());

        if (interactor != nullptr)
            interactor->removeCell(cell);

        delete cell;
    }

    Point Environment::randomFreePosition(const Point &point) const
    {
        assert(checkPositionCorrectness(point));

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
        for(unsigned int i = 0; i < attemp_count; i++){
           rand_point.i = RandomGenerator::generateRandomIntNumber(0, this->getWidth()-1);
           rand_point.j = RandomGenerator::generateRandomIntNumber(0, this->getHeight()-1);
           if(checkPositionCorrectness(rand_point) && !frameMatrix[rand_point.i][rand_point.j]){
                return rand_point;
           }
        }
        return {-1, -1};
    }

    void Environment::generateCells(int N, controller::GameController *cont)
    {
        for(int i = 0; i < N ; i++){
            Point point = this->getRandomFreePosOnMap();
            if(point.i != -1){
                cont->addCell(point);
            }
            else{
                continue;
            }
        }
    }

}
