#ifndef FRAME_H
#define FRAME_H

#include "Genotype.h" // For Point struct
#include "Environment.h"
 

namespace environment 
{

    class Frame 
    {
    public:
        explicit Frame() {}
        explicit Frame(Point position, Environment* environment = nullptr)
            : environment(environment), position(position) {};
        virtual ~Frame() {}

        inline Point getPosition() const { return position; }
        inline virtual void setPosition(Point newPosition) { position = newPosition; }
        inline Environment* getEnvironment() const { return environment; }
        inline virtual void setEnvironment(Environment* environment) { this->environment = environment; };

    protected:
        Environment* environment;
        Point position;
    };


/*class Frame
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
};*/

}

#endif // FRAME_H
