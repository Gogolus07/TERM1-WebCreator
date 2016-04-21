/**
 * @file label.h
 * @brief Classe qui represente a la fois un Element et un Label
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 13/04/2016
 * Classe qui herite de Element et de QLabel
 */
#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include "../elementwidget.h"

QT_BEGIN_NAMESPACE
class QStyleOptionGraphicsItem;
class QPainter;
class QWidget;
QT_END_NAMESPACE

class Label: public QLabel, virtual public ElementWidget
{

    public:
        Label(QWidget*parent=0);
        Label(std::string, QWidget*parent=0);
        Label(std::string, std::string, QWidget*parent=0);
        //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        //void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
        //void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
        //void dragMoveEvent(QDragMoveEvent *event)   Q_DECL_OVERRIDE;
        //void dropEvent(QDropEvent *event)           Q_DECL_OVERRIDE;

        //void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;
        void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

};

#endif // LABEL_H
