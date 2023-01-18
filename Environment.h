#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <frame.h>
#include <cell.h>

#include <QList>

class Environment
{
private:
    const int WIDTH;
    const int HEIGHT;
    Frame** frameMatrix;
    QList<Cell*> cells;
    double time;

public:
    // Constructors / Destructors
    Environment(int WIDTH,  int HEIGHT, int cellNumber = 0);
    virtual ~Environment();

    // Enviroment Actions:
    void tickTime();
    bool isDay() const;
    bool isNight() const;
    double getTime() const;
};

#endif // ENVIRONMENT_H
