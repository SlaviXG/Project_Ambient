#include "Environment.h"

#include <QRandomGenerator>

// Constructors / Destructors
Environment::Environment(int WIDTH,  int HEIGHT, size_t cellNumber)
    : WIDTH(WIDTH), HEIGHT(HEIGHT)
{
    this->frameMatrix = new Frame* [HEIGHT];
    for(int i = 0; i < HEIGHT; i++)
    {
        frameMatrix[i] = new Frame [WIDTH];
    }

    this->time = 0.0;

    for (size_t i = 0; i < cellNumber; i++)
    {
        this->AddRandomCell();
    }
}

Environment::~Environment()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        delete [] this->frameMatrix[i];
    }

    delete [] this->frameMatrix;
}

// Enviroment Actions:
void Environment::tickTime()
{
    this->time += 0.01;
}

bool Environment::isDay() const
{
    return (static_cast<int>(time*100)%2 ? false :true);
}

bool Environment::isNight() const
{
    return (static_cast<int>(time*100)%2 ? true :false);
}

//Set:


//Get:
double Environment::getTime() const
{
    return this->time;
}



std::vector<bool> Environment::getVisionField(Point viewPoint) const
{
    std::vector<bool> vec;

    // Optimization
    /*if (cellNumber < 25)
    {
        vec.resize(25);
        foreach(auto cell, cells){
            Point pos = cell->getPosition();
            if (pos.x > viewPoint.x - 3 && pos.x < viewPoint.x + 3 &&
                pos.y > viewPoint.y - 3 && pos.y < viewPoint.y + 3){
                // TODO: Do the magic to turn the point into a vector coordinate
            }
        }
    }*/

    vec.reserve(25);

    for (int i = viewPoint.x - 2; i <= viewPoint.x + 2; ++i){
        for (int j = viewPoint.y - 2; j <= viewPoint.y + 2; ++j){
            Point checkPoint {i, j};
            if (checkPoint.x < 0 || checkPoint.x >= HEIGHT ||
                checkPoint.y < 0 || checkPoint.y >= WIDTH)
            {
                vec.push_back(false);
            }
            else if (checkPoint.x != viewPoint.x || checkPoint.y != viewPoint.y) // observation cell exception
            {
                vec.push_back(this->frameMatrix[i][j].isCell());
            }
        }
    }

    return vec;
}
void Environment::AddCell(Cell* cell)
{
    cells.insert(cell);
    frameMatrix[cell->getPosition().x][cell->getPosition().y].setCell(cell);
    cellNumber++;
}

void Environment::AddRandomCell()
{
    QRandomGenerator gen;
    this->AddCell(new Cell({gen.bounded(HEIGHT), gen.bounded(WIDTH)}));
}


