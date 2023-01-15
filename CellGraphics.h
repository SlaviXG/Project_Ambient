#ifndef CELL_GRAPHICS_H
#define CELL_GRAPHICS_H

#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui { class CellGraphics; }
QT_END_NAMESPACE

class Cell;

class CellGraphics : public QGraphicsRectItem
{
public:
    CellGraphics(QGraphicsItem *parent = nullptr);
    // x, y - starting position
    CellGraphics(qreal x, qreal y, qreal width, qreal height, Cell* cell = nullptr, QGraphicsItem *parent = nullptr);
    ~CellGraphics();

private:
    Cell* cell;
};
#endif // CELL_GRAPHICS_H
