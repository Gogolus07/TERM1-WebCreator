/**
 * @file elementwidget.h
 * @brief Classe qui met en place le lien entre la partie metier et l'IHM
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 05/12/2016
 * Classe qui herite de Element pour dire que l'objet courent est un Element
 * la classe herite aussi de QWidget pour mettre en place le drag and drop.
 */


#ifndef ELEMENTWIDGET_H
#define ELEMENTWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "metier/include/Element.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
QT_END_NAMESPACE

/**
 * @class PageWidget
 * Classe mere qui va contenir heriter de la classe QWidget pour
 * le drag and drop et de Element pour dire que c'est un element.
 */
class ElementWidget: public QWidget , public Element
{
    Q_OBJECT
    public:
        /**
         *  \brief Constructeur
         *
         *  Constructeur par defaut de la classe ElementWidget
         *
         *  \param parent : automatiquement initialisé a zero.
         */
        ElementWidget(QWidget *parent = nullptr);

        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe ElementWidget
         *
         *  \param parent : automatiquement initialisé a zero.
         *  \param moduleName : nom du module utilisé.
         */
        ElementWidget(std::string moduleName, QWidget *parent = nullptr);

        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe ElementWidget
         *
         *  \param parent : automatiquement initialisé a zero.
         *  \param moduleName : nom du module utilisé.
         *  \param content : contenu a integrer dans le module.
         */
        ElementWidget(std::string moduleName, std::string content, QWidget *parent = nullptr);

        /**
         *  \brief redefinition de l'apparence du widget
         *
         *  \param painter : .
         *  \param option : .
         *  \param widget : .
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    protected:
        /**
         *  \brief redefinition de leaveEvent
         *         la redefinition va nous permetre de faire des actions quand on quittera la porté du widget.
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void leaveEvent(QEvent * event)Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de enterEvent
         *         la redefinition va nous permetre de faire des actions quand on entre dans le widget.
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void enterEvent(QEvent * event)Q_DECL_OVERRIDE;

        //void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de mousePressEvent
         *         la redefinition va nous permetre d'initialiser le drag.
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void mousePressEvent(QMouseEvent *event)Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de mouseMoveEvent
         *         la redefinition va nous permetre d'initialiser le drag avec l'identifiant du de l'Element this (lui meme).
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de dragEnterEvent
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de dragLeaveEvent
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de dragMoveEvent
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void dragMoveEvent(QDragMoveEvent *event)   Q_DECL_OVERRIDE;

        /**
         *  \brief redefinition de dropEvent
         *
         *  \param event : event va nous permetre d'avoir des informations sur la souris.
         */
        void dropEvent(QDropEvent *event)           Q_DECL_OVERRIDE;

    private:
        QPoint dragStartPosition;   /*!< attribut qui va contenir la position du curseur lors d'un clique */
};

#endif // ELEMENTWIDGET_H
