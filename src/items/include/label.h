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

QT_BEGIN_NAMESPACE
class QStyleOptionGraphicsItem;
class QPainter;
class QWidget;
QT_END_NAMESPACE


/**
 * @class Label
 *
 * Classe mere qui va contenir un heritage de QLabel dans le but d'afficher
 * du text et de ElementWidget pour lui donner les faculté du drag and drop
 * et d'Element.
 */
class Label: public QLabel, virtual public ElementWidget{

    public:
        /**
         *  \brief Constructeur
         *
         *  Constructeur par defaut de la classe Label
         *
         *  \param parent : automatiquement initialisé a zero.
         */
        Label(ElementWidget *currentElementWidget, QWidget*parent=0);

        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe Label
         *
         *  \param parent : automatiquement initialisé a zero.
         *  \param moduleName : nom du module utilisé.
         */
        Label(ElementWidget *currentElementWidget, std::string moduleName, QWidget*parent=0);

        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe ElementWidget
         *
         *  \param parent : automatiquement initialisé a zero.
         *  \param moduleName : nom du module utilisé.
         *  \param content : contenu a integrer dans le module.
         */
        Label(ElementWidget *currentElementWidget, std::string moduleName, std::string content, QWidget*parent=0);
        //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        //void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
        //void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
        //void dragMoveEvent(QDragMoveEvent *event)   Q_DECL_OVERRIDE;
        //void dropEvent(QDropEvent *event)           Q_DECL_OVERRIDE;

        //void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
        //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;
        //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

};

#endif // LABEL_H
