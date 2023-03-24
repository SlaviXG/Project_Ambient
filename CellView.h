#ifndef CELL_GRAPHICS_H
#define CELL_GRAPHICS_H

#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui { class CellView; }
QT_END_NAMESPACE

/**
 * The class CellView is responsible
 * for Cell's graphic representation.
 **/

class CellView : public QGraphicsRectItem
{
public:
    // x, y - starting position
    CellView(qreal x, qreal y, qreal width, qreal heigh, QGraphicsItem *parent = nullptr);
    virtual~CellView();

private:
    //Position in the graphic field:

    qreal pos_x;
    qreal pos_y;
};
#endif // CELL_VIEW_H
