#ifndef MATRIX_H_
#define MATRIX_H_

struct Point
{
    int i = 0, j = 0;

    // Addition operator
    Point operator+(const Point &other) const
    {
        return Point{i + other.i, j + other.j};
    }

    // Subtraction operator
    Point operator-(const Point &other) const
    {
        return Point{i - other.i, j - other.j};
    }

    // Multiplication operator
    Point operator*(int scalar) const
    {
        return Point{i * scalar, j * scalar};
    }

    // Division operator
    Point operator/(int scalar) const
    {
        //Q_ASSERT(scalar != 0);
        return Point{i / scalar, j / scalar};
    }

    // Equality operator
    bool operator==(const Point &other) const
    {
        return (i == other.i) && (j == other.j);
    }

    // Inequality operator
    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }
};

#endif
