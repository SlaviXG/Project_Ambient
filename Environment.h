#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <set>
#include <list>
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

        std::list<Cell> cells;
        double time;

    public:
        // Constructors / Destructors
        explicit Environment(int WIDTH, int HEIGHT, std::size_t cellNumber = 0);
        virtual ~Environment(){};

        // Enviroment Actions:
        void tickTime();
        bool isDay() const;
        bool isNight() const;
        double getTime() const;
        inline int getWidth() { return WIDTH; }
        inline int getHeight() { return HEIGHT; }

        // Checks if a point has negative or larger coordinates than the map size 
        // On failure returns Point{-1, -1}
        inline bool checkPositionCorrectness(const Point& point) const { 
            return !(point.i < 0 || point.i >= HEIGHT || point.j < 0 || point.j >= WIDTH); 
            }
        inline size_t getCellNumber() const { return cells.size(); }

        // Cell Actions:
        void AddCell(const Cell &cell);
        void AddRandomCell(); // TODO

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
        static int generateRandomNumber(int min, int max)
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            static std::uniform_int_distribution<int> dist(min, max);
            return dist(rng);
        }
    };

}

#endif // ENVIRONMENT_H
