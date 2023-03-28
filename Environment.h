#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <random>

#include "Tick.h"
#include "Genotype.h" // For Point struct

namespace controller { class CellInteractor; }

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

        controller::CellInteractor* interactor = nullptr;

    public:
        // Constructors / Destructors
        explicit Environment(int WIDTH, int HEIGHT, controller::CellInteractor* interactor = nullptr);
        virtual ~Environment(){};

        // Enviroment Actions:
        // KISS 🥵😰
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
        /**
         * @brief Get the Cell object
         * 
         * @param point Position on the map
         * @return Cell or nullptr if the Cell is missing
         */
        inline Cell* getCell(const Point& point) const {
            return dynamic_cast<Cell*>(frameMatrix[point.i][point.j]);
        }
        inline size_t getCellNumber() const { return cells.size(); }
        inline const std::vector<Cell *>& getCells() const { return cells; } 
        
        void setCellInteractor(controller::CellInteractor* interactor);

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
        void RemoveCell(Cell* cell);

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
        static int generateRandomIntNumber(int min, int max)
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            static std::uniform_int_distribution<int> idist(min, max);
            return idist(rng);
        }

        static double generateRandomDoubleNumber(double min, double max)
        {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            static std::uniform_real_distribution<double> ddist(min, max);
            return ddist(rng);
        }
    };

}

#endif // ENVIRONMENT_H
