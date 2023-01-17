#ifndef FRAME_H
#define FRAME_H

#include <cell.h>

class Frame
{
private:
    //enum Type {empty, cell, food};
    Cell* cellPtr = nullptr;
public:
    Frame();
};

#endif // FRAME_H
