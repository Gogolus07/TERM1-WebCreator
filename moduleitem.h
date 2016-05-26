/**
 * @file moduleitem.h
 * @brief Classe qui construit un bouton qui sera notre item
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 21/04/2016
 * Classe qui herite de QPushButton pour mettre en place le drag and drop
 * du coté des items (partie gauche du logiciel.
 */

#ifndef MODULEITEM_H
#define MODULEITEM_H

#include <QPushButton>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPoint;
QT_END_NAMESPACE

/**
 * @class moduleItem
 * Classe qui represente visuellement un item draggable
 * ici on va utiliser un QPushButton que l'on va redefinir
 * en lui modifiant les methodes liés au mouvement de la souris.
 */
class moduleItem : public QPushButton
{
    Q_OBJECT
    public:
        /**
         *  \brief Constructeur
         *
         *  Constructeur par defaut de la classe moduleItem
         *
         *  \param parent : automatiquement initialisé a zero.
         */
        explicit moduleItem(QWidget *parent = nullptr);

        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe moduleItem
         *
         *  \param parent : automatiquement initialisé a zero.
         *  \param name :   nom a afficher sur le bouton.
         */
        explicit moduleItem(QString name, QWidget *parent = nullptr);

    protected:
        /**
         *  \brief Quand on presse la souris
         *
         *  modification du comportement du logiciel quand on presse la souris.
         *  Si le bouton droit est pressé alors on sauvegarde la position courante.
         */
        void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief Quand on fait un mouvement
         *
         *  modification du comportement du logiciel quand on fait un mouvement.
         *  Si apres avoir ete pressé le mouvement de la souris change alors
         *  on va créé notre attribut de drag et lui donner comme valeur le nom name.
         */
        void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief Quand on est hors de porté de ce widget (de cette classe)
         *
         *  modification du comportement du logiciel.
         *  On change l'apparence du curseur.
         */
        void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

        /**
         *  \brief Quand on est a porté de ce widget (de cette classe)
         *
         *  modification du comportement du logiciel.
         *  On change l'apparence du curseur (on ouvre la main).
         */
        void enterEvent( QEvent*event ) Q_DECL_OVERRIDE;

    private:
        QPoint m_dragStartPosition;   /*!< attribut qui servira a sauvegarder la position du curseur*/
        QString m_name;               /*!< attribut qui contiendra le nom de l'item */
    //signals:

    //public slots:
};

#endif // MODULEITEM_H
