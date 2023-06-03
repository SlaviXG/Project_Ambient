#ifndef CELLVIEWGARBAGECOLLECTOR_H
#define CELLVIEWGARBAGECOLLECTOR_H

#include <QStack>

#include "EnvironmentScene.h"

namespace controller {
class CellViewGarbageCollector
{
public:
    explicit CellViewGarbageCollector(EnvironmentScene *scene) : scene(scene) {};
    void append(CellView* cellView) { this->cells.append(cellView);}
    void clear() {
        CellView* cellptr;
        while (!cells.isEmpty())
        {
            cellptr = cells.pop();

            if (scene->contains(cellptr))
                scene->removeCell(cellptr);
        }
    }

    virtual ~CellViewGarbageCollector() {
        this->clear();
    }

private:
    QStack<CellView*> cells;
    EnvironmentScene *scene;
};

}
#endif // CELLVIEWGARBAGECOLLECTOR_H
