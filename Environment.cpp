#include "Environment.h"

// Constructors / Destructors
Environment::Environment(int WIDTH,  int HEIGHT, int cellNumber) : WIDTH(WIDTH), HEIGHT(HEIGHT)
{
    this->frameMatrix = new Frame* [HEIGHT];

    for(int i = 0; i < HEIGHT; i++)
    {
        frameMatrix[i] = new Frame [WIDTH];
    }

    this->time = 0.0;

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



QVector<bool> Environment::getVisionField(Point point) const
{
    QVector<bool> vec; vec.reserve(25);

    for (int i = point.x - 2; i <= point.x + 2; i++){
        for (int j = point.y - 2; j <= point.y + 2; j++){
            Point checkPoint {i, j};
            if (checkPoint.x < 0 || checkPoint.x >= HEIGHT ||
                checkPoint.y < 0 || checkPoint.y >= WIDTH)
            {
                vec.append(false);
            }
            else if (checkPoint.x != point.x || checkPoint.y != point.y) // observation cell exception
            {
                vec.append(this->frameMatrix[i][j].isCell());
            }
        }
    }

    return vec;
}
void Environment::AddCell(Cell* cell)
{
    cells.append(cell);
    frameMatrix[cell->getPosition().x][cell->getPosition().y].setCell(cell);
}

