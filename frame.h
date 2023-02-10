#ifndef FRAME_H
#define FRAME_H

#include "cell.h"

class Frame
{
private:
    //enum Type {empty, cell, food};

    Cell* cellPtr = nullptr;
public:
    Frame();
    Frame(Cell* cell);

    bool isCell();
    void setCell(Cell* cell);
    Cell* getCell();

    void makeEmpty();
};

#endif // FRAME_H