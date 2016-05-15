#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QMimeData>
//#include <QPainter>
//#include <iostream>

/*nos classe d'item*/
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QPainter>
#include <QApplication>

#include <QWidget>
#include "elementwidget.h"

/* ElementWidget: =================================================== */
ElementWidget::ElementWidget(ElementWidget *currentElementWidget, QWidget *parent):
    currentElementWidget(currentElementWidget),
    QWidget(parent),//m_SizeGrip(parent),
    Element(){
    QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );
    QWidget::setAcceptDrops(true);
    //m_SizeGrip.setStyleSheet("image: none");

    //QWidget::setDragEnabled(true);
}

/* ElementWidget: =================================================== */
ElementWidget::ElementWidget(Element* e)
{
    copieElement(*e);

    QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );
    QWidget::setAcceptDrops(true);
}



/* ElementWidget: =================================================== */
ElementWidget::ElementWidget(ElementWidget *currentElementWidget, std::string moduleName, QWidget *parent):
    currentElementWidget(currentElementWidget),
    QWidget(parent),//m_SizeGrip(parent),
    Element(moduleName){
    QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );
    //QWidget::setDragEnabled(true);
    //m_SizeGrip.setStyleSheet("image: none");

    setAcceptDrops(true);
}

/* ElementWidget: =================================================== */
ElementWidget::ElementWidget(ElementWidget *currentElementWidget, std::string moduleName, std::string content, QWidget *parent):
    currentElementWidget(currentElementWidget),
    QWidget(parent),//m_SizeGrip(parent),
    Element(moduleName, content){
    QWidget::setAttribute( Qt::WA_OpaquePaintEvent, true );
    //QWidget::setDragEnabled(true);
    //m_SizeGrip.setStyleSheet("image: none");

    setAcceptDrops(true);
}

/* setCurrentElementWidget: ========================================== */
void ElementWidget::setCurrentElementWidget(ElementWidget *currentEltWidget){
    this->currentElementWidget=currentEltWidget;
}


/* getCurrentElementWidget: =========================================== */
ElementWidget *ElementWidget::getCurrentElementWidget(){
    return this->currentElementWidget;
}




/*
void ElementWidget::mouseReleaseEvent(QMouseEvent *){
    //setCursor(Qt::OpenHandCursor);
    //setStyleSheet("border: 1px solid black;");
}*/

/* mousePressEvent: =================================================== */
void ElementWidget::mousePressEvent(QMouseEvent *event){
    //std::cout<<"Je suis dans le mouse_press_event "<<std::endl;
/*
    if (event->button() == Qt::LeftButton)
            dragStartPosition = event->pos();

     QDrag *drag = new QDrag(this);
     QMimeData *mimeData = new QMimeData;

     mimeData->setText(QString(getId().c_str()));
     drag->setMimeData(mimeData);
*/
     /*Qt::DropAction dropAction = */
     //drag->exec(Qt::CopyAction | Qt::MoveAction);

    //setCursor(Qt::);
    setStyleSheet("border: 2px solid red; border-style:dotted; ");

}


/* mouseMoveEvent: =================================================== */
void ElementWidget::mouseMoveEvent(QMouseEvent *event){
    //std::cout<<"Je suis dans le (ElementWidget) mouse_move_event "<<std::endl;

    //setCursor(Qt::OpenHandCursor);
    //setStyleSheet("border: 1px solid red;");
    std::cout<<"x:"<<event->x()<<"   y:"<< event->y()<<std::endl;
    //this->move(event->x(), event->y());
    //this->move(event->x()-(this->width()/2), event->y()-(this->height()/2));
    //E->QLabel::move(event->pos().x()-(E->width()/2), event->pos().y()-(E->height()/2));

    //On prepare les elements a etre drag and drop.
    QDrag *drag = new QDrag(this);
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    /** debut de ce qui sera drag and drop **/
    //Ici on met ce que nous voulons droper.
    mime->setText(QString(getId().c_str()));
    std::cout<<"ElementWidget:::l'id est : "+getId()<<std::endl;
    /** Fin de ce qui sera drag and drop **/

    drag->exec();
    setCursor(Qt::OpenHandCursor);
}


/* paint: =================================================== */
void ElementWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //std::cout<<"Je suis dans le painter "<<std::endl;
    //painter->setPen(Qt::NoPen);
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/* leaveEvent: =================================================== */
void ElementWidget::leaveEvent(QEvent * event){ // Quand la souris quitte le bouton
    //std::cout<<"Je suis dans le leave_event "<<std::endl;

    Q_UNUSED (event);
    setStyleSheet("border: none;");
}

/* enterEvent: =================================================== */
void ElementWidget::enterEvent(QEvent * event){ // Quand la souris entre dans le bouton
    //std::cout<<"Je suis dans le enter_event "<<std::endl;

    Q_UNUSED (event);
    //setCursor(Qt::OpenHandCursor);
    setStyleSheet("border: 2px solid blue; border-style:dotted; ");
}

/* dragEnterEvent: =================================================== */
void ElementWidget::dragEnterEvent(QDragEnterEvent *event){
    //std::cout<<"Je suis dans le drag_enter "<<std::endl;

    if (event->mimeData()->hasHtml())
        event->accept();
    else
        event->ignore();
}

/* dragLeaveEvent: =================================================== */
void ElementWidget::dragLeaveEvent(QDragLeaveEvent *event){
    //std::cout<<"Je suis dans le drag_leave "<<std::endl;

    //QRect updateRect = highlightedRect;
    //highlightedRect = QRect();
    //RectangleItem updateRect = highlightedRect;
    //highlightedRect = new RectangleItem();
    //update(updateRect);
    //update(highlightedRect);
    event->accept();
}

/* dragMoveEvent: =================================================== */
void ElementWidget::dragMoveEvent(QDragMoveEvent *event){
    //std::cout<<"Je suis dans le drag_move "<<std::endl;

    //highlightedRect = new RectangleItem();
    //highlightedRect->setPos(event->pos());
    //RectangleItem updateRect = highlightedRect;//highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasHtml()) {
        //highlightedRect = targetSquare(event->pos());
        //highlightedRect = new RectangleItem();
        //highlightedRect->setPos(event->pos());

        std::cout<<"x:"<<event->pos().x()<<"   y:"<< event->pos().y()<<std::endl;
        this->move(event->pos().x(), event->pos().y());

        event->setDropAction(Qt::MoveAction);
        event->accept();
        //scene->clear();
    } else {
        //highlightedRect = new RectangleItem();
        event->ignore();
    }
    //update(updateRect);
    //update(highlightedRect);
}

/* dropEvent: =================================================== */
void ElementWidget::dropEvent(QDropEvent *event){
    //std::cout<<"Je suis dans le drag_event "<<std::endl;
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

        if(event->mimeData()->text()=="1"){
        //    addElement(Element("p"));
            //QPushButton *b = new QPushButton("soka");
            //b->move(event->pos().x()-200, event->pos().y()-200);
            //scene->addWidget(b);
        }
        else{
        //    addElement(Element("LineEdit"));

            //QLineEdit *t = new QLineEdit("soka");
            //t->move(event->pos().x()-200, event->pos().y()-200);
            //scene->addWidget(t);
        }

        //Variable pour le test
   //     int i=200;
   //     for(Element e: m_childElements){
   //         if(m_elementName=="p")
   //             QLineEdit *t = new QLineEdit(m_elementName);
   //         else
   //             QPushButton *t = new QPushButton(m_elementName);
   //         t->move(event->pos().x()-i, event->pos().y()-i);
   //         scene->addWidget(t);
   //         i+=100;
   //     }

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        //highlightedRect = new RectangleItem();
        event->ignore();
    }
}
/**/
void ElementWidget::resizeEvent(QResizeEvent *event)
{
  //m_SizeGrip.move  (width() - 32, height() - 32);
  //m_SizeGrip.resize(          32,            32);
}
