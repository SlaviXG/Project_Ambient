/**
 * @file CellView.h
 * @brief Header file for the CellView class
 */

#ifndef CELL_GRAPHICS_H
#define CELL_GRAPHICS_H

#include <QGraphicsRectItem>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class CellView; }
QT_END_NAMESPACE

/**
 * @class CellView
 * @brief Class representing a cell in the graphic view.
 *
 * The CellView class is responsible for the graphic representation of a cell.
 * It inherits from QObject and QGraphicsPixmapItem.
 */
class CellView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the CellView class.
     * @param x The x-coordinate for the starting position.
     * @param y The y-coordinate for the starting position.
     * @param width The width of the cell.
     * @param height The height of the cell.
     * @param colorGrad The color gradient of the cell.
     * @param parent The parent QGraphicsItem.
     */
    CellView(qreal x, qreal y, qreal width, qreal height, QPixmap* colorGrad, QGraphicsItem *parent = nullptr);

    /**
     * @brief Destructor for the CellView class.
     */
    virtual ~CellView();

    /**
     * @brief Updates the position and color gradient of the cell.
     * @param x The new x-coordinate.
     * @param y The new y-coordinate.
     * @param colorGrad The new color gradient.
     */
    void updateCellView(qreal x, qreal y, QPixmap* colorGrad);

    /**
     * @brief Sets the color gradient of the cell.
     * @param colorGrad The new color gradient.
     */
    void setColorGrad(QPixmap* colorGrad);

    /**
     * @brief Gets the current pixmap of the cell.
     * @return The current pixmap.
     */
    QPixmap getCurrentPixmap();

    /**
     * @brief Updates the highlight box around the cell.
     */
    void updateHighlightBox();

    /**
     * @brief Highlights the cell.
     */
    void highlight();

    /**
     * @brief Removes the highlight from the cell.
     */
    void removeHighlight();

signals:
    void clicked(CellView* cellView);
    void deleted(CellView* cellView);

private:
    // Position in the graphic field:
    qreal pos_x;
    qreal pos_y;
    QGraphicsRectItem* highlightBox;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    friend class CellTracker;
};

#endif // CELL_VIEW_H
