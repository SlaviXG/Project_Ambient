#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <frame.h>
#include <cell.h>

#include <QSet>

class Environment
{
private:
    const int WIDTH;
    const int HEIGHT;
    Frame** frameMatrix;
    QSet<Cell*> cells;
    double time;
    size_t cellNumber = 0;

public:
    // Constructors / Destructors
    Environment(int WIDTH,  int HEIGHT, size_t cellNumber = 0);
    virtual ~Environment();

    // Enviroment Actions:
    void tickTime();
    bool isDay() const;
    bool isNight() const;
    double getTime() const;

    // Cell Actions:
    void AddCell(Cell* cell);
    void AddRandomCell();

    // Cell Vision:
    /*
    00 01 02 03 04
    05 06 07 08 09
    10 11 😀 12 13
    14 15 16 17 18
    21 22 23 24 25
    */
    QVector<bool> getVisionField(Point point) const;

};

#endif // ENVIRONMENT_H
