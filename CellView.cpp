#include "CellView.h"


CellView::CellView(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    this->setRect(x, y, width, height);
}

CellView::~CellView()
{

}
