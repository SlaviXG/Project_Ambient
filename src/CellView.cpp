#include "../include/CellView.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>


CellView::CellView(qreal x, qreal y, qreal width, qreal height, QPixmap* colorGrad = nullptr, QGraphicsItem *parent)
: QGraphicsPixmapItem(QPixmap(width, height), parent)
{
    highlightBox = new QGraphicsRectItem(0, 0, width, height, this);
    highlightBox->setPen(QPen(Qt::red)); // Set the color of the bounding box to red
    highlightBox->hide(); // Hide the bounding box initially

    this->updateCellView(x, y, colorGrad);
}

CellView::~CellView()
{
    emit deleted(this);
}

void CellView::updateCellView(qreal x, qreal y, QPixmap *colorGrad)
{
    this->pos_x = x;
    this->pos_y = y;
    this->setColorGrad(colorGrad);
    this->setPos(x, y);

    this->updateHighlightBox();
}

void CellView::updateHighlightBox() {
    if (highlightBox) {
        highlightBox->setRect(this->boundingRect());
    }
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

    // Check if the item is deleted
    if (event->button() == Qt::RightButton)
    {
        emit deleted(this);
    }
    else
    {
        emit clicked(this);
    }
}

void CellView::highlight() 
{
    highlightBox->show();
}

void CellView::removeHighlight() 
{
    highlightBox->hide();
}

