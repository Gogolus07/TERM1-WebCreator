#include <QtWidgets>

#include "rectangleitem.h"

RectangleItem::RectangleItem()
    : color(qrand() % 256, qrand() % 256, qrand() % 256)
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setToolTip(QString("Click and drag this color onto the robot!"));
}

QRectF RectangleItem::boundingRect() const{
    return QRectF(-15.5, -15.5, 34, 34);
}

void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *){
    setCursor(Qt::ClosedHandCursor);
}

void RectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *){
    setCursor(Qt::OpenHandCursor);
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //Ici c'est l'ombre des ronds
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(-12, -12, 30, 30);

    //Ici c'est les ronds
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color));
    painter->drawRect(-15, -15, 30, 30);
}

void RectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //ici on va dire que:
    //Si on a  detecté un mouvement du curseur quand il a commencé a etre cliqué.
    //alors on va commencer le drag and drop, sinon on ne fait pas de drag and drop.
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    //On prepare les elements a etre drag and drop.
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);


    /** debut de ce qui sera drag and drop **/
    //Ici on met ce que nous voulons droper.
    mime->setColorData(color);
    mime->setText(QString("#%1%2%3")
                  .arg(color.red(), 2, 16, QLatin1Char('0'))
                  .arg(color.green(), 2, 16, QLatin1Char('0'))
                  .arg(color.blue(), 2, 16, QLatin1Char('0')));/**/
    QString monhtml="<p>sokaRectItem</p>";
    mime->setHtml(monhtml);
    mime->setText(text);

    QPixmap pixmap(34, 34);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.translate(15, 15);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, 0, 0);
    painter.end();

    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(15, 20));
    /** Fin de ce qui sera drag and drop **/

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void RectangleItem::setColor(QColor c){
    color = c;
}

void RectangleItem::setText(QString s){
    text = s;
}

