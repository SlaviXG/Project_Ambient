#include "CellGraphics.h"

CellGraphics::CellGraphics(QGraphicsItem *parent)
    :  QGraphicsRectItem(parent)
{
}

CellGraphics::CellGraphics(qreal x, qreal y, qreal width, qreal height, Cell* cell, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    this->cell = cell;
    this->setRect(0, 0, width, height);
}

CellGraphics::~CellGraphics()
{

}
