#include "feuillewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QHBoxLayout>
#include <iostream>
#include <QPushButton>
#include <QLineEdit>

FeuilleWidget::FeuilleWidget(QWidget *parent):
    QGraphicsView(parent){
    setAcceptDrops(true);
    setMinimumSize(200,200);
    this->setScene(scene = new QGraphicsScene(-200, -200, 500, 500));
}

void FeuilleWidget::dragEnterEvent(QDragEnterEvent *event){

    std::cout<<"Je suis dans le drag_enter "<<std::endl;

    if (event->mimeData()->hasHtml())
        event->accept();
    else
        event->ignore();
}

void FeuilleWidget::dragLeaveEvent(QDragLeaveEvent *event){
    std::cout<<"Je suis dans le drag_leave "<<std::endl;

    //QRect updateRect = highlightedRect;
    //highlightedRect = QRect();
    //RectangleItem updateRect = highlightedRect;
    //highlightedRect = new RectangleItem();
    //update(updateRect);
    //update(highlightedRect);
    event->accept();
}

void FeuilleWidget::dragMoveEvent(QDragMoveEvent *event){

    //highlightedRect = new RectangleItem();
    //highlightedRect->setPos(event->pos());
    //RectangleItem updateRect = highlightedRect;//highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasHtml()) {
        //highlightedRect = targetSquare(event->pos());
        //highlightedRect = new RectangleItem();
        //highlightedRect->setPos(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
        scene->clear();
    } else {
        highlightedRect = new RectangleItem();
        event->ignore();
    }

    //update(updateRect);
    //update(highlightedRect);
}

/*
void FeuilleWidget::dropEvent(QDropEvent *event){
    if (event->mimeData()->hasHtml()) {

        //QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        //QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

        //RectangleItem square;
        //square.setPos(event->pos());
        QPoint location;
        location=event->pos();

        pieceLocations.append(location);
        //pieceRects.append(square);

        highlightedRect = new RectangleItem();
        //update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        //if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize())) {
        //    inPlace++;
        //    if (inPlace == 25)
        //        emit puzzleCompleted();
        //}
    } else {
        highlightedRect = new RectangleItem();
        event->ignore();
    }
}*/
void FeuilleWidget::dropEvent(QDropEvent *event){
    if (event->mimeData()->hasHtml()) {
        QPoint location;
        location=event->pos();

        pieceLocations.append(location);
        //pieceRects.append(square);

        //highlightedRect = new RectangleItem();
        //update(square);

        //QFrame *frame = new QFrame;
        //QHBoxLayout *frameLayout = new QHBoxLayout(frame);


        RectangleItem *item = new RectangleItem;
        item->setColor(QColor(event->mimeData()->colorData().toString()));
        item->setPos(event->pos().x()-200, event->pos().y()-200);
        //scene->addItem(item);

        if(event->mimeData()->text()=="1"){
            QPushButton *b = new QPushButton("soka");
            b->move(event->pos().x()-200, event->pos().y()-200);
            scene->addWidget(b);
        }
        else{
            QLineEdit *t = new QLineEdit("soka");
            t->move(event->pos().x()-200, event->pos().y()-200);

            scene->addWidget(t);
        }

        /*Partie Gauche*/
        view=new QGraphicsView(scene);
        setRenderHint(QPainter::Antialiasing);
        view->setBackgroundBrush(QColor(event->mimeData()->colorData().toString()));





        std::cout<<"Je suis dans le drop "<<std::endl;
        std::cout<<"La couleur est: "<<event->mimeData()->colorData().toString().toStdString()<<std::endl;
        std::cout<<"Le html est: "<<event->mimeData()->html().toStdString()<<std::endl;



        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        highlightedRect = new RectangleItem();
        event->ignore();
    }
}
/*
void FeuilleWidget::mousePressEvent(QMouseEvent *event)
{
    //QRect square = targetSquare(event->pos());
    //int found = findPiece(square);

    //if (found == -1)
    //    return;

    //QPoint location = pieceLocations[found];
    //QPixmap pixmap = piecePixmaps[found];
    //pieceLocations.removeAt(found);
    //piecePixmaps.removeAt(found);
    //pieceRects.removeAt(found);

    //if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
    //    inPlace--;

    //update(square);

    //QByteArray itemData;
    //QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    //dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    //mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //drag->setHotSpot(event->pos() - square.topLeft());
    //drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
    //    pieceLocations.insert(found, location);
    //    piecePixmaps.insert(found, pixmap);
    //    pieceRects.insert(found, square);
    //    update(targetSquare(event->pos()));

    //    if (location == QPoint(square.x()/pieceSize(), square.y()/pieceSize()))
    //        inPlace++;
    }
}*/










