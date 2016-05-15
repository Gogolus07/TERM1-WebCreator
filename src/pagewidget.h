/**
 * @file pagewidget.h
 * @brief Classe qui construit le centre de notre logiciel
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 28/02/2016
 * Classe qui herite de QGraphicsView pour integrer le tous les Element
 * de notre construction ainsi que pour mettre en place le drag and drop.
 */
#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QGraphicsView>
#include "metier/include/Element.h"

class CompositeElementWidget;
class ElementWidget;

/**
 * @class PageWidget
 * Classe du widget centrale du logiel.
 */
class PageWidget : public QGraphicsView
{
    Q_OBJECT
    public:
        /**
         *  \brief Constructeur
         *
         *  Constructeur par defaut de la classe PageWidget
         *
         *  \param parent : automatiquement initialisé a zero.
         */
        PageWidget(QWidget *parent = nullptr);

        /**
         * @fn loadElements(Element e)
         * @brief Charge les elements recuperes a l ouverture d un fichier
         * @param Element* e {Element recupere dans le code metier a convertir en element graphique}
         */
        void loadElements(Element* e);
    protected:
        /**
         *  \brief Methode qui va nous servir a initialiser le drag.
         *
         *  \param event : evenement qui va nous dire si on entre en etat de drag.
         */
        void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief Methode qui va nous servir a gerer les mouvement d'un widget au centre de notre page.
         *
         *  \param event : evenement qui va nous donner la position du curseur.
         */
        void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief Methode qui va nous servir a creer un nouvel item (widget) et l'afficher sur notre page centrale.
         *
         *  \param event : evenement qui va nous donner la position du curseur ainsi que le type du Widget a instancier.
         */
        void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;


        void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;

        //void mousePressEvent  (QMouseEvent *event) Q_DECL_OVERRIDE;
        //void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    private:
        //QList<RectangleItem> pieceRects;
        //QList<QPoint> pieceLocations;
        unsigned int idElementWidget=0;

        CompositeElementWidget  *m_compoEltWidget;   /*!< attribut qui va contenir des ElementWidget */
        QGraphicsScene          *m_scene;            /*!< attribut qui va contenir tous les widget (ElementWidget) dans le but de les afficher */
        QGraphicsView           *m_view;             /*!< attribut qui va contenir la view de notre page centrale dans laquel nous allons integrer notre scene (m_scene) */

        ElementWidget *currentElementWidget=nullptr;
};

#endif // PAGEWIDGET_H
