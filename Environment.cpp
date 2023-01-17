#include "Environment.h"

// Constructors / Destructors
Environment::Environment(int WIDTH,  int HEIGHT, int cellNumber):WIDTH(WIDTH), HEIGHT(HEIGHT)
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
    time += 0.01;
}

bool Environment::isDay()
{
    return (static_cast<int>(time*100)%2 ? false :true);
}

bool Environment::isNight()
{
    return (static_cast<int>(time*100)%2 ? true :false);
}

QVector<Frame> Environment::getVisionField()
{

}

//Set:


//Get:
double Environment::getTime()
{
    return this->time;
}
