#ifndef CELL_H
#define CELL_H

struct Point {int x = 0, y = 0; };

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
