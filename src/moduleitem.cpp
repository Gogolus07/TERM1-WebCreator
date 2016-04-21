#include "moduleitem.h"
#include <QDragEnterEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
//#include <QWidget>
#include <QApplication>

/* moduleItem: =================================================== */
moduleItem::moduleItem(QWidget *parent) : QPushButton(parent)
{}

/* moduleItem: =================================================== */
moduleItem::moduleItem(QString name, QWidget *parent) : QPushButton(name, parent), m_name(name)
{}

/* mousePressEvent: ============================================== */
void moduleItem::mousePressEvent(QMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    if (event->buttons() == Qt::LeftButton)
        m_dragStartPosition = event->pos();
}

/* mouseReleaseEvent: ============================================= */
void moduleItem::mouseReleaseEvent(QMouseEvent *){
    setCursor(Qt::OpenHandCursor);
}

/* enterEvent: pour survoler l'item ================================ */
void moduleItem::enterEvent( QEvent*event ) {
    Q_UNUSED( event );
    setCursor(Qt::OpenHandCursor);
}

/* mouseMoveEvent: pour le mouvement de l'item ====================== */
void moduleItem::mouseMoveEvent(QMouseEvent *event){

    //On doit verifier si on a bien un clique droit.
    if (!(event->buttons() & Qt::LeftButton))
        return;

    //ici on va dire que:
    //Si on a  detecté un mouvement du curseur quand il a commencé a etre cliqué.
    //alors on va commencer le drag and drop, sinon on ne fait pas de drag and drop.
    if ((event->pos() - m_dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    setCursor(Qt::ClosedHandCursor);

    //On prepare les elements a etre drag and drop.
    QDrag     *drag = new QDrag(this);
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);
    /* debut de ce qui sera dans le drag ===*/
    mime->setText(m_name);
    /* Fin de ce qui sera dans le drag =====*/
    drag->exec();

    //setCursor(Qt::OpenHandCursor);
}
