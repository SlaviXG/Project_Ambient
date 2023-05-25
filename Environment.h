#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_set>
#include <random>

#include "Point.h"


namespace controller { class CellInteractor; }

namespace environment
{
    class Frame;
    class Cell; // Cell inherits Frame

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
        virtual ~Environment();

        // Enviroment Actions:
        // KISS 🥵😰
        void tickTime();
        bool isDay() const;
        bool isNight() const;
        double getTime() const;
        inline int getWidth() const { return WIDTH; }
        inline int getHeight() const { return HEIGHT; }
        inline Frame* getFrame(const Point& point) const {
            Q_ASSERT(checkPositionCorrectness(point));
            return frameMatrix[point.i][point.j];
        }
        /**
         * @brief Get the Cell object
         * 
         * @param point Position on the map
         * @return Cell or nullptr if the Cell is missing
         */
        Cell* getCell(const Point& point) const;
        inline size_t getCellNumber() const { return cells.size(); }
        inline auto& getCells() { return cells; }

        void setCellInteractor(controller::CellInteractor* interactor);

        /**
         * @brief Updates Cell position in the frameMatrix
         *
         * @param cell Cell to update position
         * @param oldPos Cell's old position on the map
         */
       virtual void updateCellPosition(Cell* cell, const Point& oldPos);

        // Checks if a point has negative or larger coordinates than the map size 
        // On failure returns Point{-1, -1}
        inline bool checkPositionCorrectness(const Point& point) const { 
            return !(point.i < 0 || point.i >= HEIGHT || point.j < 0 || point.j >= WIDTH);
            }

        // Cell Actions:
        virtual Cell* AddCell(Cell* cell); // Call from logic
        virtual Cell* AddCell(const Point& point); // Call from controller
        virtual Cell* AddCell(const Point& point, std::vector<int> countOfWeights);
        /**
         * @brief Removes the cell from the map
         *
         * @param cell
         */
        virtual void InvalidateCell(Cell* cell);

        /**
         * @brief Removes Cell object
         *
         * @param cell
         */
        virtual void RemoveCell(Cell* cell);

        // Cell Vision:
        /*
        00 01 02 03 04
        05 06 07 08 09
        10 11 😀 12 13
        14 15 16 17 18
        19 20 21 22 23
        */
        virtual std::vector<bool> getVisionField(const Point &point) const;

        // Returns a random correct and empty cell coordinate within a radius of one from the given point
        virtual Point randomFreePosition(const Point &point) const;
    };

    class RandomGenerator {
    public:
        static int generateRandomIntNumber(int min, int max) {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            std::uniform_int_distribution<int> idist(min, max);
            return idist(rng);
        }

        static double generateRandomDoubleNumber(double min, double max) {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            std::uniform_real_distribution<double> ddist(min, max);
            return ddist(rng);
        }

        /**
         * @brief generateRandomPoint
         * @param top_left Top left corner of the bounding box
         * @param bottom_right Bottom right corner of the bounding box
         * @return Random point that does not go beyond the bounding box
         */
        static Point generateRandomPoint(const Point& top_left, const Point& bottom_right) {
            static std::random_device rd;
            static std::mt19937 rng(rd());

            std::uniform_int_distribution<int> xdist(top_left.j, bottom_right.j); // x
            std::uniform_int_distribution<int> ydist(top_left.i, bottom_right.i); // y


            return { ydist(rng), xdist(rng) };
        }
    };
}

#endif // ENVIRONMENT_H
