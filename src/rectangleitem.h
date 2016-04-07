#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QGraphicsItem>

class RectangleItem : public QGraphicsItem
{
public:
    RectangleItem();
    void setColor(QColor c);
    void setText(QString c);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //RectangleItem& operator=(const RectangleItem& other) Q_DECL_OVERRIDE;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QColor color;
    QString text;
};

/*RectangleItem& RectangleItem::operator=(const RectangleItem& other) {
    if (this != &other) {
        this->color=other.color;
    }
    return *this;
}*/

#endif // RECTANGLEITEM_H


/****************************************************************************
****************************************************************************/
