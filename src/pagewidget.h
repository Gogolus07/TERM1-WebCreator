#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "rectangleitem.h"

class CompositeElementWidget;

class PageWidget : public QGraphicsView
{
    Q_OBJECT
    public:
        PageWidget(QWidget *parent = 0);
    protected:
        void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
        void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
        void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
        void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

        //void mousePressEvent  (QMouseEvent *event) Q_DECL_OVERRIDE;
        //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    private:
        //QList<RectangleItem> pieceRects;
        //QList<QPoint> pieceLocations;

        CompositeElementWidget *compoEltWidget;
        QGraphicsScene *scene;
        QGraphicsView *view;
};

#endif // PAGEWIDGET_H
