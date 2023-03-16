#include "Environment.h"

#include <cassert>

namespace environment
{
    // Constructors / Destructors
    Environment::Environment(int WIDTH, int HEIGHT, size_t cellNumber)
        : WIDTH(WIDTH), HEIGHT(HEIGHT)
    {
        frameMatrix.resize(HEIGHT);

        for (auto &row : frameMatrix) {
            row.resize(WIDTH);
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

    std::vector<bool> Environment::getVisionField(Point viewPoint) const
    {
        assert(viewPoint.i >= 0 && viewPoint.i <= HEIGHT &&
               viewPoint.j >= 0 && viewPoint.j <= WIDTH);

        std::vector<bool> vec;
        vec.reserve(25);

        for (int i = viewPoint.i - 2; i <= viewPoint.i + 2; ++i)
        {
            for (int j = viewPoint.j - 2; j <= viewPoint.j + 2; ++j)
            {
                Point checkPoint{i, j};
                if (checkPoint.i < 0 || checkPoint.i >= HEIGHT ||
                    checkPoint.j < 0 || checkPoint.j >= WIDTH)
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

        // Optimization
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
        cells.insert(cell);
        frameMatrix[cell.getPosition().i][cell.getPosition().j].setCell(cell);
    }

    void Environment::AddRandomCell()
    {
        // TODO
        //this->AddCell(new Cell({gen.bounded(HEIGHT), gen.bounded(WIDTH)}, this));
    }

}