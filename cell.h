#ifndef CELL_H
#define CELL_H

struct Point {int i = 0, j = 0; };

class Cell
{
private:
    Point position;

public:
    Cell();
    Cell(Point startingPosition);

    Point getPosition() const;
};

#endif // CELL_H
