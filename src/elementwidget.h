/**
 * @file elementwidget.h
 * @brief Classe qui met en place le lien entre la partie metier et l'IHM
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 05/12/2016
 * Classe qui herite de Element pour dire que l'objet courent est un Element
 * la classe herite aussi de QWidget pour dire mettre en place le drag and drop.
 */
#ifndef ELEMENTWIDGET_H
#define ELEMENTWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
QT_END_NAMESPACE

#include "metier/include/Element.h"

class ElementWidget: public QWidget , public Element
{
    Q_OBJECT
    public:
        ElementWidget(QWidget *parent = 0);
        ElementWidget(std::string, QWidget *parent = 0);
        ElementWidget(std::string, std::string, QWidget *parent = 0);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        void leaveEvent(QEvent * event)Q_DECL_OVERRIDE;
        void enterEvent(QEvent * event)Q_DECL_OVERRIDE;

        //void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
        void mousePressEvent(QMouseEvent *event)Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;

        void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
        void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
        void dragMoveEvent(QDragMoveEvent *event)   Q_DECL_OVERRIDE;
        void dropEvent(QDropEvent *event)           Q_DECL_OVERRIDE;

    private:
        QPoint dragStartPosition;
};

#endif // ELEMENTWIDGET_H
