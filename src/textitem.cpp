#include "textitem.h"
#include "pagescene.h"
#include <QTextCursor>
#include <QPen>
#include <QDebug>

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
