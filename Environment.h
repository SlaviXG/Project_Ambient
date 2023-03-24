#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <random>

#include "Tick.h"
#include "Genotype.h" // For Point struct


namespace environment
{
    class Frame;
    class Cell;

    class Environment
    {
    private:
        const int WIDTH;
        const int HEIGHT;

        std::vector<std::vector<Frame *>> frameMatrix;
        double time;    
        std::vector<Cell *> cells;

    public:
        // Constructors / Destructors
        explicit Environment(int WIDTH, int HEIGHT);
        virtual ~Environment(){};

        // Enviroment Actions:
        void tickTime();
        bool isDay() const;
        bool isNight() const;
        double getTime() const;
        inline int getWidth() const { return WIDTH; }
        inline int getHeight() const { return HEIGHT; }
        inline Frame* getFrame(const Point& point) const {
            assert(checkPositionCorrectness(point));
            return frameMatrix[point.i][point.j];
        }
        inline size_t getCellNumber() const { return cells.size(); }
        inline const std::vector<Cell *>& getCells() const { return cells; } 

        // Updates frameMatrix with the data in the vector "cells"
        // Difficulty: WIDTH * HEIGHT
        void updateMap();

        // Checks if a point has negative or larger coordinates than the map size 
        // On failure returns Point{-1, -1}
        inline bool checkPositionCorrectness(const Point& point) const { 
            return !(point.i < 0 || point.i >= HEIGHT || point.j < 0 || point.j >= WIDTH); 
            }

        // Cell Actions:
        void AddCell(Cell* cell);

        // Cell Vision:
        /*
        00 01 02 03 04
        05 06 07 08 09
        10 11 😀 12 13
        14 15 16 17 18
        19 20 21 22 23
        */
        std::vector<bool> getVisionField(const Point &point) const;

        // Returns a random correct and empty cell coordinate within a radius of one from the given point
        Point randomFreePosition(const Point &point) const;
    };

    class RandomGenerator
    {
    public:
        static int generateRandomNumber(double min, double max)
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            static std::uniform_real_distribution<double> dist(min, max);
            return dist(rng);
        }
    };

}

#endif // ENVIRONMENT_H
