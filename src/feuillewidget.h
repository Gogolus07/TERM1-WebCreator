#ifndef FEUILLEWIDGET_H
#define FEUILLEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "rectangleitem.h"

class FeuilleWidget : public QGraphicsView
{
    Q_OBJECT
public:
    FeuilleWidget(QWidget *parent = 0);
protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    //void mousePressEvent  (QMouseEvent *event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
/*
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QRect highlightedRect;
    size_t tailleElement;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;*/
private:
    QList<RectangleItem> pieceRects;
    QList<QPoint> pieceLocations;
    RectangleItem *highlightedRect;

    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // FEUILLEWIDGET_H
