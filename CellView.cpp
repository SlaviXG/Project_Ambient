#include "CellView.h"


CellView::CellView(qreal x, qreal y, qreal width, qreal height, QPixmap* colorGrad = nullptr, QGraphicsItem *parent)
: QGraphicsPixmapItem(QPixmap(width, height), parent)
{
    this->updateCellView(x, y, colorGrad);
}

CellView::~CellView()
{

}

void CellView::updateCellView(qreal x, qreal y, QPixmap *colorGrad)
{
    this->pos_x = x;
    this->pos_y = y;
    this->setColorGrad(colorGrad);
    this->setPos(x, y);
}

void CellView::setColorGrad(QPixmap *colorGrad)
{
    this->setPixmap(*colorGrad);
}

QPixmap CellView::getCurrentPixmap()
{
    return this->pixmap();
}

void CellView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() <<"Cell clicked: " << pos_x << ' ' << pos_y;
    QGraphicsPixmapItem::mousePressEvent(event);
}
