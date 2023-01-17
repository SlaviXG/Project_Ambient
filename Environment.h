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

public:
    // Constructors / Destructors
    Environment(int WIDTH,  int HEIGHT);
    virtual ~Environment();

};

#endif // ENVIRONMENT_H
