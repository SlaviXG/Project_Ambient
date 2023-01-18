#include "cell.h"

Cell::Cell()
{

}

Cell::Cell(Point startingPosition)
{
    this->position = startingPosition;
}

Point Cell::getPosition() const
{
    return position;
}
