/**
 * @file mainwindows.h
 * @brief Classe IHM du logiciel final
 * @author {Sofien BENHARCHACHE, Emmanuel GUIRAUD}
 * @version 0.1
 * @date 05/12/2016
 * Classe regroupant les differentes parties IHM et metier.
 * Cette classe va construire la fenetre principal du logiciel.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QGraphicsView;
class QGraphicsScene;
class QListWidget;
QT_END_NAMESPACE

/**
 * @class MainWindow
 * Classe principale contenant tous ce qu'il faut pour concevoir/realiser un projet.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         *  \brief Constructeur
         *
         *  Constructeur de la classe MainWindow
         *
         *  \param parent : automatiquement initialisé a zero.
         */
        MainWindow(QWidget *parent = 0);

        /**
         *  \brief Destructeur
         *
         *  Destructeur de la classe MainWindow
         */
        ~MainWindow();

    private:
        /**
         *  \brief Le centre du logiciel
         *
         *  Creation du centre du logiciel
         */
        void setupWidgets();

        /**
         *  \brief Le Menu
         *
         *  Creation du menu du logiciel
         */
        void createMenus();

        /**
         *  \brief Les Actions
         *
         *  Initialisation de toutes les actions possibles
         */
        void createAction();

        /**
         *  \brief La barre d'outils
         *
         *  Creation de la barre d'outils du logiciel
         */
        void createToolBars();

        /**
         *  \brief Statut d logiciel
         *
         *  Initialise le statut du logiciel
         */
        void createStatusBar();

        /**
         *  \brief Dock sur le CSS et le DOM
         *
         *  Cree et initialise le dock avec le CSS et le DOM
         */
        void createDockWindows();


        //Les attributs
        QToolBar *m_fileToolBar;        /*!< toolbar contenant les actions realisables sur des fichier (charger, sauver, ...) */
        QToolBar *m_editToolBar;        /*!< toolbar contenant les actions realisables sur la memoire tempon (copier, coller, ...)  */
        QToolBar *m_compilationToolBar; /*!< toolbar contenant les actions realisables sur la compilation/execution du projet  */

        QMenu *m_fichierMenu;     /*!< menu contenant les actions realisables sur des fichier (Nouveau; Nouvelle page; Ouvrir; Fermer; Sauvegarder; Sauvegarder comme ...) */
        QMenu *m_editionMenu;     /*!< menu contenant les actions realisables sur la memoire tempon (Annuler; Retablir; Copier; Coller; Supprimer; Tous selectionner; Tous deselectionner)  */
        QMenu *m_compilationMenu; /*!< menu contenant les actions realisables sur la compilation/execution du projet */
        QMenu *m_fenetreMenu;     /*!< menu contenant les actions realisables sur la fenetre principale (Maximiser; minimiser) */
        QMenu *m_aideMenu;        /*!< menu contenant les aides possible pour l'utilisateur (Rechercher; Documentation) */

        /* Bare de menu pour Fichier */
        QAction *m_nouveauAct;          /*!< action realisable pour creer un nouveau projet */
        QAction *m_nouvellePageAct;     /*!< action realisable pour creer une nouvelle page web */
        QAction *m_ouvrirAct;           /*!< action realisable pour ouvrir un nouveau projet  */
        QAction *m_fermerAct;           /*!< action realisable pour fermer le logiciel */
        QAction *m_sauvegarderAct;      /*!< action realisable pour sauvegarder le projet */
        QAction *m_sauvegarder_commeAct;/*!< action realisable pour sauvegarder le projet dans un autre nom et/ou dossier */

        /* Bare de menu pour Edition */
        QAction *m_annulerAct;  /*!< actions realisable pour revenir en arriere dans les actions realisé */
        QAction *m_retablirAct; /*!< actions realisable pour aller en avant dans les action realisé (annuler le m_annulerAct)*/
        #ifndef QT_NO_CLIPBOARD
        QAction *m_couperAct;   /*!< actions realisable pour couper l'element et le placer dans le buffer (memoire vive) */
        QAction *m_copierAct;   /*!< actions realisable pour copier l'element et le placer dans le buffer (memoire vive) */
        QAction *m_collerAct;   /*!< actions realisable pour placer l'element copié ou collé dans la page web */
        #endif
        QAction *m_tousSelectionnerAct;  /*!< actions realisable pour selectionner toute la page web */
        QAction *m_tousDeselectionnerAct;/*!< actions realisable pour deselectionner toute la page web */

        /* Bare de menu pour Compiler */
        QAction *m_relancerProjetAct;   /*!< action realisable pour relancer le projet depuis le JSON */
        QAction *m_refaireJsonAct;      /*!< action realisable pour refaire le JSON  */
        QAction *m_executerAct;         /*!< action realisable pour executer et lancer le site web  */
        QAction *m_executerSansDepAct;  /*!< action realisable pour executer sans depoiement du site web  */

        /* Bare de menu pour Fenetre */
        QAction *m_maximiserAct;    /*!< action realisable pour agrandir la taille du logiciel */
        QAction *m_minimiserAct;    /*!< action realisable pour diminuer la taille du logiciel */

        /* Bare de menu pour Aide */
        QAction *m_rechercherAct;   /*!< action realisable pour lancer une recherche d'aide sur un mot cle*/
        QAction *m_documentationAct;/*!< action realisable pour afficher la focumentation */

        QMenu *m_viewMenu;      /*!< attribut qui servira a l'affichage du menu */
        QGraphicsView *m_view;
        QGraphicsScene *m_scene;

        //Pour les test en haut a droite
        QListWidget *m_customerLists;
        //QListWidget *paragraphsList;
};

#endif // MAINWINDOW_H




/*private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
#ifndef QT_NO_CLIPBOARD
    void cut();
    void copy();
    void paste();
#endif
*/


