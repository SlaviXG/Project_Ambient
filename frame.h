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
        explicit Frame(const Frame& frame) { this->environment = frame.environment; this->position = frame.position; }
        explicit Frame(genotype::Point position, Environment* environment = nullptr)
            : environment(environment), position(position) {};
        virtual ~Frame() {}

        inline genotype::Point getPosition() const { return position; }
        inline virtual void setPosition(genotype::Point newPosition) { position = newPosition; }
        inline Environment* getEnvironment() const { return environment; }
        inline virtual void setEnvironment(Environment* environment) { this->environment = environment; };

    protected:
        Environment* environment;
        genotype::Point position;
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
