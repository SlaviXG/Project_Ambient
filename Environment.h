#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <frame.h>
#include <cell.h>

#include <QVector2D>
#include <QList>

class Environment
{
private:
    const int WIDTH;
    const int HEIGHT;
    Frame** frameMatrix;
    QList<Cell> cells;
    double time;

public:
    // Constructors / Destructors
    Environment(int WIDTH,  int HEIGHT, int cellNumber = 0);
    virtual ~Environment();

    // Enviroment Actions:
    void tickTime();
    bool isDay();
    bool isNight();
    double getTime();
    QVector<Frame> getVisionField();
};

#endif // ENVIRONMENT_H
