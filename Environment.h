#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_set>
#include <random>

#include "Point.h"
#include "Genotype.h"

// Cell Vision:
/*
        00 01 02 03 04
        05 06 07 08 09
        10 11 😀 12 13
        14 15 16 17 18
        19 20 21 22 23
*/

namespace controller
{
     class CellInteractor;
}
namespace controller
{
     class GameController;
}
namespace genepool
{
     class GenePool;
}

namespace environment
{
     class Frame;
     class Cell; // Cell inherits Frame

    /**
     * @class Environment
     * @brief This class represents the environment in which cells live.
     *
     * The Environment class is responsible for managing the cells and the frames in which they live.
     * It provides methods for adding and removing cells, updating their positions, and performing various
     * other operations related to the environment.
     */
     class Environment
     {
     private:
          const int WIDTH;  ///< The width of the environment.
          const int HEIGHT; ///< The height of the environment.

          // upper limit of population for environment validation ( 2 = 200% of original population)
          const int population_upper_limit = 2;
          // TESTING ZONE
          //  Added for step limitation in order to test out genepools
          const int max_step_count_before_reset = 5000;
          int cur_step_count = 0;

          std::vector<std::vector<Frame *>> frameMatrix;    ///< The matrix representing the environment.
          double time;                                      ///< The current time in the environment.
          std::vector<Cell *> cells;                        ///< The cells in the environment.
          genepool::GenePool *pool;                         ///< The gene pool of the environment.
          controller::CellInteractor *interactor = nullptr; ///< The cell interactor for the environment.

     public:
          /**
           * @brief Constructs an Environment object.
           * @param WIDTH The width of the environment.
           * @param HEIGHT The height of the environment.
           * @param interactor The cell interactor for the environment (Controller interface).
           * @param pool The gene pool of the environment.
           */
          explicit Environment(int WIDTH, int HEIGHT, controller::CellInteractor *interactor = nullptr, genepool::GenePool *pool = nullptr);

          /**
           * @brief Destructs the Environment object.
           */
          virtual ~Environment();

          /**
           * @brief Advances the time in the environment.
           */
          void tickTime();

          /**
           * @brief Checks if it is day in the environment.
           * @return True if it is day, false otherwise.
           */
          bool isDay() const;

          /**
           * @brief Checks if it is night in the environment.
           * @return True if it is night, false otherwise.
           */
          bool isNight() const;

          /**
           * @brief Gets the current time in the environment.
           * @return The current time.
           */
          double getTime() const;

          /**
           * @brief Gets the width of the environment.
           * @return The width of the environment.
           */
          int getWidth() const;

          /**
           * @brief Gets the height of the environment.
           * @return The height of the environment.
           */
          int getHeight() const;

          /**
           * @brief Gets the frame at a specific point in the environment.
           * @param point The point at which to get the frame.
           * @return The frame at the given point.
           */
          Frame *getFrame(const Point &point) const;

          /**
           * @brief Get the Cell object at a specific point.
           * @param point The point at which to get the cell.
           * @return The cell at the given point, or nullptr if no cell exists at that point.
           */
          Cell *getCell(const Point &point) const;

          /**
           * @brief Gets the number of cells in the environment.
           * @return The number of cells in theenvironment.
           */
          size_t getCellNumber() const;

          /**
           * @brief Gets the cells in the environment.
           * @return A vector of cells in the environment.
           */
          std::vector<Cell *> &getCells();

          /**
           * @brief Sets the cell interactor for the environment.
           * @param interactor The cell interactor to set.
           */
          void setCellInteractor(controller::CellInteractor *interactor);

          /**
           * @brief Updates a cell's position in the frameMatrix.
           * @param cell The cell to update.
           * @param oldPos The old position of the cell.
           */
          virtual void updateCellPosition(Cell *cell, const Point &oldPos);

          /**
           * @brief Checks if a point is within the bounds of the environment.
           * @param point The point to check.
           * @return True if the point is within the bounds of the environment, false otherwise.
           */
          bool checkPositionCorrectness(const Point &point) const;

          /**
           * @brief Adds a cell to the environment.
           * @param cell The cell to add.
           * @return The cell that was added.
           */
          virtual Cell *AddCell(Cell *cell);

          /**
           * @brief Adds a cell to the environment at a specific point.
           * @param point The point at which to add the cell.
           * @return The cell that was added.
           */
          virtual Cell *AddCell(const Point &point);

          /**
           * @brief Adds a cell to the environment at a specific point with a specific count of weights.
           * @param point The point at which to add the cell.
           * @param countOfWeights The count of weights for the cell.
           * @return The cell that was added.
           */
          virtual Cell *AddCell(const Point &point, std::vector<int> countOfWeights);

          /**
           * @brief Adds a cell to the environment at a specific point with a specific genotype.
           * @param point The point at which to add the cell.
           * @param genotype The genotype of the cell.
           * @return The cell that was added.
           */
          virtual Cell *AddCell(const Point &point, genotype::Genotype *genotype);

          /**
           * @brief Removes a cell from the map.
           * @param cell The cell to remove.
           */
          virtual void InvalidateCell(Cell *cell);

          /**
           * @brief Removes a cell from the environment.
           * @param cell The cell to remove.
           */
          virtual void RemoveCell(Cell *cell);

          /**
           * @brief Removes all cells from the environment.
           */
          void RemoveAllCells();

          /**
           * @brief Gets the vision field of a cell at a specific point.
           * @param point The point of the cell.
           * @return A vector of booleans representing the vision field of the cell.
           */
          virtual std::vector<bool> getVisionField(const Point &point) const;

          /**
           * @brief Returns a random correct and empty cell coordinate within a radius of one from the given point.
           * @param point The point from which to get a random free position.
           * @return A random free position within a radius of one from the given point.
           */
          virtual Point randomFreePosition(const Point &point) const;

          /**
           * @brief Returns a random free position on the map.
           * @param attemp_count The number of attempts to find a free position.
           * @return A random free position on the map.
           */
          virtual Point getRandomFreePosOnMap(unsigned int attemp_count = 50) const;

          /**
           * @brief Autospawns N cells in the environment.
           * @param N The number of cells to generate.
           */
          virtual void generateCells(int N);

          /**
           * @brief Validates the environment by counting the number of cells.
           */
          virtual void ValidateEnvironment();

          /**
           * @brief Returns a reference to the GenePool.
           * @return A reference to the GenePool.
           */
          genepool::GenePool *getGenePool();

          /**
           * @brief Returns the maximum cell count.
           * @return The maximum cell count.
           */
          unsigned int getMaxCellCount();
     };

     /**
      * @class RandomGenerator
      * @brief A utility class for generating random numbers and points.
      */
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
