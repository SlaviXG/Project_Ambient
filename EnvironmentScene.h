#ifndef ENVIRONMENT_SCENE_H
#define ENVIRONMENT_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>

#include "CellView.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EnvironmentScene; }
QT_END_NAMESPACE

class EnvironmentScene : public QGraphicsScene
{
public:
    EnvironmentScene(QObject *parent = nullptr);
    ~EnvironmentScene();

    inline void addCell(CellView* cell) { cells.append(cell); this->addItem(cell); }
    const QList<CellView*>& getCells() const { return cells; }
    inline void removeCell(CellView* cell) {cells.removeOne(cell);}

private:
    QList<CellView*> cells;
    QVector <QImage> cellColorGradations;

    bool loadColorGradations();
};
#endif // ENVIRONMENT_SCENE_H
