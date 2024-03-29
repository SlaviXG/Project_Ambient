#ifndef FRAME_H
#define FRAME_H

#include "point.h"
#include "Environment.h"
#include "point.h"
 

namespace environment 
{

    class Frame 
    {
    public:
        explicit Frame() {}
        explicit Frame(const Frame& frame) { this->environment = frame.environment; this->position = frame.position; }
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
}

#endif // FRAME_H
