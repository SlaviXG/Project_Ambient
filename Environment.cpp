#include "Environment.h"

Environment::Environment(int WIDTH,  int HEIGHT):WIDTH(WIDTH), HEIGHT(HEIGHT)
{
    this->frameMatrix = new Frame* [HEIGHT];

    for(int i = 0; i < HEIGHT; i++)
    {
        frameMatrix[i] = new Frame [WIDTH];
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
