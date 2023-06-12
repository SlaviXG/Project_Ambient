#ifndef GAMEINTERACTOR_H_
#define GAMEINTERACTOR_H_

#include <vector>

#include "point.h"
#include "configs/ConfigurationChain.h"

namespace controller
{

    /**
     * @brief GameInteractor interface for interacting with the controller from the view layer.
     */
    class GameInteractor
    {
    public:
        /**
         * @brief Add a cell to a specific point in the game.
         * @param point The point to add the cell.
         */
        virtual void addCell(const Point &point) = 0;
        /**
         * @brief Add a cell to a specific point in the game with specific count of weights.
         * @param point The point to add the cell.
         * @param countOfWeights The count of weights for the cell.
         */
        virtual void addCell(const Point &point, const std::vector<int> &countOfWeights) = 0;

        /// Start the game.
        virtual void start() = 0;

        /// Stop the game.
        virtual void stop() = 0;

        /// Pause the game.
        virtual void pause() = 0;

        /// Resume the game.
        virtual void resume() = 0;

        /// Opens settings window
        virtual void openSettingsWindow() = 0;
    };

}

#endif