#include "textitem.h"
#include "pagescene.h"
#include <QTextCursor>
#include <QPen>
#include <QDebug>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QDrag>

TextItem::TextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent),
      element("p", "Sans Texte")
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    //element=new Element("p", "sans Texte");
}

Element& TextItem::getElement()
{
    return element;
}


QVariant TextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

void TextItem::focusOutEvent(QFocusEvent *event)
{
    qDebug()<<"Content=="<<this->toPlainText();
    element.setContent(this->toPlainText().toStdString());
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}



void TextItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"DEE";

    if (event->mimeData()) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}



void TextItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()) {
        /*bool ok;
        int val=event->mimeData()->text().toInt(&ok);
        if(ok){
            const QMimeData *mime = event->mimeData();
            QPoint position = event->pos();
            QPoint hotSpot;
            QList<QByteArray> hotSpotPos = mime->data("application/x-hotspot").split(' ');
            if (hotSpotPos.size() == 2) {
                hotSpot.setX(hotSpotPos.first().toInt());
                hotSpot.setY(hotSpotPos.last().toInt());
            }
            if(currentChild != nullptr)
                currentChild->move(position-hotSpot);
        }*/

        qDebug()<<"DME";


        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }
}



void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"MPE";
    QPoint hotSpot = (event->pos().toPoint()) - this->pos().toPoint();

    /*Mise en place du mime*/
    QMimeData *mimeData = new QMimeData();
    mimeData->setData("application/x-hotspot", QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

    /*On ajoute une image*/
    //QPixmap pixmap();
    //this->render(&pixmap);

    /*On met tout dans le drag*/
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    /*On execute le drag*/
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

}
