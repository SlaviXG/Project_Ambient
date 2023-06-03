#ifndef CELLVIEWGARBAGECOLLECTOR_H
#define CELLVIEWGARBAGECOLLECTOR_H

#include <QStack>

#include "EnvironmentScene.h"

namespace controller {

/**
 * @class CellViewGarbageCollector
 * @brief A class responsible for collecting and removing unused CellView objects.
 */
class CellViewGarbageCollector
{
public:
    /**
     * @brief Constructs a CellViewGarbageCollector object with a given EnvironmentScene instance.
     * @param scene The EnvironmentScene instance.
     */
    explicit CellViewGarbageCollector(EnvironmentScene *scene) : scene(scene) {};

    /**
     * @brief Appends a CellView object to the garbage collector.
     * @param cellView The CellView object to be appended.
     */
    void append(CellView* cellView) { this->cells.append(cellView);}

    /**
     * @brief Clears the garbage collector, removing all CellView objects from the scene.
     */
    void clear() {
        CellView* cellptr;
        while (!cells.isEmpty())
        {
            cellptr = cells.pop();

            if (scene->contains(cellptr))
                scene->removeCell(cellptr);
        }
    }

    /**
     * @brief Destroys the CellViewGarbageCollector object, clearing the garbage collector.
     */
    virtual ~CellViewGarbageCollector() {
        this->clear();
    }

private:
    QStack<CellView*> cells; ///< A stack to store the CellView objects.
    EnvironmentScene *scene; ///< Pointer to the EnvironmentScene instance.
};

} // namespace controller

#endif // CELLVIEWGARBAGECOLLECTOR_H
