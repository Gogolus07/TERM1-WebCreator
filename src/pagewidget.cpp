#include "pagewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QHBoxLayout>
#include <iostream>
#include <QPushButton>
#include <QLineEdit>

#include "items/include/label.h"
#include "metier/include/Body.h"
#include "compositeelementwidget.h"

/* PageWidget: ============================================ */
PageWidget::PageWidget(QWidget *parent):
    QGraphicsView(parent),
    m_compoEltWidget( new CompositeElementWidget()),
    m_scene(new QGraphicsScene(-200, -200, 500, 500)){
    setAcceptDrops(true);
    setMinimumSize(200,200);
    //this->setScene(m_scene = new QGraphicsScene(-200, -200, 500, 500));
    this->setScene(m_scene);

    //m_compoEltWidget = new CompositeElementWidget();
}

/* dragEnterEvent: ========================================== */
void PageWidget::dragEnterEvent(QDragEnterEvent *event){

    //std::cout<<"Je suis dans le (PageWidget) drag_enter "<<std::endl;

    if (event->mimeData()->hasText())
        event->accept();
    else
        event->ignore();
}

/*
void PageWidget::dragLeaveEvent(QDragLeaveEvent *event){
    std::cout<<"Je suis dans le (PageWidget) drag_leave "<<std::endl;
    event->accept();
}
*/

/* ModulesList: ============================================== */
bool ModulesList(QString val){
    return val=="Text" || val=="p" || val=="a" || val=="img";
}

/* dragMoveEvent: ============================================ */
void PageWidget::dragMoveEvent(QDragMoveEvent *event){
    //std::cout<<"Je suis dans le (PageWidget) drag_move_event "<<std::endl;

    if (event->mimeData()->hasText()) {
        //Si on a pas un deplacement d'un item
        if(!ModulesList(event->mimeData()->text())){
            //std::cout<<event->mimeData()->text().toStdString()<<" ------------------- "<<std::endl;
            //ElementWidget *ew = m_compoEltWidget->getElementWidgetById(event->mimeData()->html().toStdString());
            ElementWidget *ew = m_compoEltWidget->getElementWidgetById(event->mimeData()->html().toStdString());
            if(ew != nullptr)
                ew->move(event->pos().x()-200-(ew->width()/2), event->pos().y()-200-(ew->height()/2));
        }
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

/* dropEvent: ================================================ */
void PageWidget::dropEvent(QDropEvent *event){
    //std::cout<<"Je suis dans le (PageWidget) drop_event "<<std::endl;

    if (event->mimeData()->hasText()) {

        //ElementWidget *elt;

        if(event->mimeData()->text()=="1"){
            ElementWidget*E=new ElementWidget();
            //TextEditItem*T=new TextEditItem("text", E);
            m_compoEltWidget->addElementWidget(E);
            m_scene->addWidget(E);
        }
        if(event->mimeData()->text()=="p"){
            ElementWidget*E=new ElementWidget();
            //Label*T=new Label("text", "text\ntest\nMon site Web de Master Info M1 S2", E);
            Label*T=new Label("text", "text", E);
            (void)T;
            QPoint positionLabel(event->pos().x()-(E->width()/2), event->pos().y()-(E->height()/2));
            E->QLabel::move(positionLabel);

            m_compoEltWidget->addElementWidget(E);
            m_scene->addWidget(E);
        }
        //

        /*Partie Gauche*/
        m_view=new QGraphicsView(m_scene);
        setRenderHint(QPainter::Antialiasing);
        m_view->setBackgroundBrush(QColor(event->mimeData()->colorData().toString()));

/*      std::cout<<"Je suis dans le drop "<<std::endl;
        std::cout<<"La couleur est: "<<event->mimeData()->colorData().toString().toStdString()<<std::endl;
        std::cout<<"Le html est: "<<event->mimeData()->html().toStdString()<<std::endl;*/

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }
}






