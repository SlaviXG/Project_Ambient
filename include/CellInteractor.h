#ifndef CELLINTERACTOR_H_
#define CELLINTERACTOR_H_

#include "point.h"
#include "cell.h"

namespace controller
{

    /**
     * @brief CellInteractor interface for interacting with the controller from the logic layer.
     */
    class CellInteractor
    {
    public:
        /**
         * @brief Add a cell to the controller and view layer.
         * @param cell The cell to add.
         */
        virtual void addCell(environment::Cell *cell) = 0;
        /**
         * @brief Remove a cell from the the controller and view layers
         * @param cell The cell to remove.
         */
        virtual void removeCell(environment::Cell *cell) = 0;
        /**
         * @brief Add a cell to a specific point in the controller and view layer.
         * @param point The point to add the cell.
         */
        virtual void addCell(const Point &point) = 0;
        /**
         * @brief Add a cell with a specific genotype to a specific point in the controller and view layer.
         * @param point The point to add the cell.
         * @param genotype The genotype of the cell.
         */
        virtual void addCell(const Point &point, genotype::Genotype *genotype) = 0;
    };
}

#endif