#include "Environment.h"

#include <cassert>

#include "frame.h"
#include "cell.h"
#include "GameController.h"

namespace environment
{
    // Constructors / Destructors
    Environment::Environment(int WIDTH, int HEIGHT, controller::CellInteractor *interactor)
        : WIDTH(WIDTH), HEIGHT(HEIGHT), interactor(interactor)
    {
        frameMatrix.resize(HEIGHT);

        for (auto &row : frameMatrix)
        {
            row.resize(WIDTH, nullptr);
        }

        this->time = 0.0;
    }

    Environment::~Environment() {
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
        return dynamic_cast<Cell*>(frameMatrix[point.i][point.j]);
    }

    void Environment::updateCellPosition(Cell* cell, const Point& oldPos)
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
        vec.reserve(25);

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

        // HACK: Optimization
        /*if (cellNumber < 25)
        {
            vec.resize(25);
            foreach(auto cell, cells){
                Point pos = cell->getPosition();
                if (pos.i > viewPoint.i - 3 && pos.i < viewPoint.i + 3 &&
                    pos.j > viewPoint.j - 3 && pos.j < viewPoint.j + 3){
                    // TODO: Do the magic to turn the point into a vector coordinate
                }
            }
        }*/
    }
    Cell* Environment::AddCell(Cell *cell)
    {
        cells.push_back(cell);
        auto pos = cell->getPosition();
        frameMatrix[pos.i][pos.j] = cell;
        if (interactor != nullptr) interactor->addCell(cell->getPosition());

        return cell;
    }

    Cell* Environment::AddCell(const Point& point)
    {
        Cell* cell = new Cell(point, this);
        cells.push_back(cell);
        auto pos = cell->getPosition();
        frameMatrix[pos.i][pos.j] = cell;
        
        return cell;
    }

    void Environment::RemoveCell(Cell *cell)
    {
        if (std::find(cells.begin(), cells.end(), cell) != cells.end())
        {
            auto pos = cell->getPosition();
            frameMatrix[pos.i][pos.j] = nullptr;
            delete cell;
            cells.erase(std::remove(cells.begin(), cells.end(), cell), cells.end());
            if (interactor != nullptr) interactor->removeCell(cell);
        }
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

            if (checkPositionCorrectness(randPoint) && (randPoint.i != point.i || randPoint.j != point.j))
                if (frameMatrix[randPoint.i][randPoint.j] == nullptr)
                    return randPoint;
        }
        return {-1, -1};
    }
}
