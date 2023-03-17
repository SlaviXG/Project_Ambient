#include "Environment.h"

#include <cassert>

#include "frame.h"
#include "cell.h"


namespace environment
{
    // Constructors / Destructors
    Environment::Environment(int WIDTH, int HEIGHT, size_t cellNumber)
        : WIDTH(WIDTH), HEIGHT(HEIGHT)
    {
        frameMatrix.resize(HEIGHT);

        for (auto &row : frameMatrix) {
            row.resize(WIDTH, nullptr);
        }

        this->time = 0.0;

        for (size_t i = 0; i < cellNumber; i++)
        {
            this->AddRandomCell();
        }
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

    // Get:
    double Environment::getTime() const
    {
        return this->time;
    }

    std::vector<bool> Environment::getVisionField(const Point& viewPoint) const
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
    void Environment::AddCell(const Cell& cell)
    {
        cells.push_back(cell);
        frameMatrix[cell.getPosition().i][cell.getPosition().j] = &cells.back();
    }

    Point Environment::randomFreePosition(const Point& point) const 
    {
        assert(checkPositionCorrectness(point));

        constexpr int kAttemptCount = 50; Point randPoint;
        for (size_t i = 0; i < kAttemptCount; i++)
        {
            randPoint.i = RandomGenerator::generateRandomNumber(point.i - 1, point.i + 1);
            randPoint.j = RandomGenerator::generateRandomNumber(point.j - 1, point.j + 1);

            if (checkPositionCorrectness(randPoint) && (randPoint.i != point.i || randPoint.j != point.j))
                if (frameMatrix[randPoint.i][randPoint.j] == nullptr)
                    return randPoint;
        }
        return {-1, -1};
    }

    void Environment::AddRandomCell()
    {
        // TODO:
        //this->AddCell(new Cell({gen.bounded(HEIGHT), gen.bounded(WIDTH)}, this));
    }

}
