#ifndef CELL_GRAPHICS_H
#define CELL_GRAPHICS_H

#include <QGraphicsRectItem>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class CellView; }
QT_END_NAMESPACE

/**
 * @brief CellView is responsible for Cell's graphic representation.
 **/
class CellView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // x, y - starting position
    CellView(qreal x, qreal y, qreal width, qreal heigh, QPixmap* colorGrad, QGraphicsItem *parent = nullptr);
    virtual~CellView();
    void updateCellView(qreal x, qreal y, QPixmap* colorGrad);
    void setColorGrad(QPixmap* colorGrad);
    QPixmap getCurrentPixmap();

signals:
    void clicked(CellView* cellView);
    void deleted(CellView* cellView);

private:
    //Position in the graphic field:

    qreal pos_x;
    qreal pos_y;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    friend class CellTracker;
};
#endif // CELL_VIEW_H
