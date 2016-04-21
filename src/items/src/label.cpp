#include "../items/label.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

Label::Label(QWidget* parent):
    ElementWidget(parent),
    QLabel(parent)
{
    parent->setFixedSize(this->QLabel::width(), this->QLabel::height());
}

Label::Label(std::string moduleName, QWidget* parent):
    ElementWidget(moduleName, parent),
    QLabel(moduleName.c_str(), parent)
{
    parent->setFixedSize(this->QLabel::width(), this->QLabel::height());
}


Label::Label(std::string moduleName, std::string content, QWidget* parent):
    ElementWidget(moduleName, content, parent),
    QLabel(content.c_str(), parent)
{
    QLabel::setContentsMargins(2, 2, 0, 0);
}

void Label::mouseMoveEvent(QMouseEvent *event) {
    std::cout<<"Je suis dans le (Label) mouse_move_event "<<std::endl;
}


/*void Label::mouseReleaseEvent(QGraphicsSceneMouseEvent *){
}

void Label::mousePressEvent(QGraphicsSceneMouseEvent *){
    setCursor(Qt::ClosedHandCursor);
}
*/
/*
void Label::dragEnterEvent(QDragEnterEvent *event){
    std::cout<<"Je suis dans le drag_enter "<<std::endl;

    if (event->mimeData()->hasHtml())
        event->accept();
    else
        event->ignore();
}



void Label::dragLeaveEvent(QDragLeaveEvent *event){
    std::cout<<"Je suis dans le drag_leave "<<std::endl;

    event->accept();
}

void Label::dragMoveEvent(QDragMoveEvent *event){

    //highlightedRect = new RectangleItem();
    //highlightedRect->setPos(event->pos());
    //RectangleItem updateRect = highlightedRect;//highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasHtml()) {
        //highlightedRect = targetSquare(event->pos());
        //highlightedRect = new RectangleItem();
        //highlightedRect->setPos(event->pos());
        //event->setDropAction(Qt::MoveAction);
        //event->accept();
        //scene->clear();
    } else {
        //highlightedRect = new RectangleItem();
        //event->ignore();
    }

    //update(updateRect);
    //update(highlightedRect);
}


void Label::dropEvent(QDropEvent *event){
    if (event->mimeData()->hasHtml()) {
        //QPoint location;
        //location=event->pos();

        //pieceLocations.append(location);
        //pieceRects.append(square);

        //highlightedRect = new RectangleItem();
        //update(square);

        //QFrame *frame = new QFrame;
        //QHBoxLayout *frameLayout = new QHBoxLayout(frame);


        //RectangleItem *item = new RectangleItem;
        //item->setColor(QColor(event->mimeData()->colorData().toString()));
        //item->setPos(event->pos().x()-200, event->pos().y()-200);
        //scene->addItem(item);

        //if(event->mimeData()->text()=="1"){
        //    TextEditItem *b = new TextEditItem("text");
        //    //QTextEdit *b = new QTextEdit("soka");
        //    b->move(event->pos().x()-200, event->pos().y()-200);
        //    scene->addWidget(b);
        //}
        //else{
        //    QLineEdit *t = new QLineEdit("soka");
        //    t->move(event->pos().x()-200, event->pos().y()-200);

        //    scene->addWidget(t);
        //}


        //event->setDropAction(Qt::MoveAction);
        //event->accept();

    } else {
        //highlightedRect = new RectangleItem();
        //event->ignore();
    }
}
*/


/*
void Label::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //Ici c'est l'ombre des ronds
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(-12, -12, 30, 30);

    //Ici c'est les ronds
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(QColor(12, 12, 12, 12)));
    painter->drawRect(-15, -15, 30, 30);// * /
}
*/
