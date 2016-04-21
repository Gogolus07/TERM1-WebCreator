#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MdiChild;
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
QT_END_NAMESPACE



#include <QSignalMapper>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QStatusBar>
#include <QtWidgets>
#include <stdlib.h>
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtWidgets>
#include <stdlib.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
/*
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

private:
    //Le centre de la page
    void setupWidgets();

    void createMenus();
    void createAction();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *compilationToolBar;

    QMenu *FichierMenu;     // Nouveau; Nouvelle page; Ouvrir; Fermer; Sauvegarder; Sauvegarder comme ...
    QMenu *EditionMenu;     // Annuler; Retablir; Copier; Coller; Supprimer; Tous selectionner; Tous deselectionner
    QMenu *CompilationMenu; // compiler/generer
    QMenu *FenetreMenu;     // Maximiser; minimiser
    QMenu *AideMenu;        // Rechercher; Documentation

    /* Bare de menu pour Fichier */
    QAction *nouveauAct;
    QAction *nouvellePageAct;
    QAction *ouvrirAct;
    QAction *fermerAct;
    QAction *sauvegarderAct;
    QAction *sauvegarder_commeAct;

    /* Bare de menu pour Edition */
    QAction *annulerAct;
    QAction *retablirAct;
    #ifndef QT_NO_CLIPBOARD
    QAction *couperAct;
    QAction *copierAct;
    QAction *collerAct;
    #endif
    QAction *tousSelectionnerAct;
    QAction *tousDeselectionnerAct;

    /* Bare de menu pour Compiler */
    QAction *relancerProjetAct; //relance le projet depuis le JSON
    QAction *refaireJsonAct;
    QAction *executerAct;
    QAction *executerSansDepAct; //executer sans depoiement

    /* Bare de menu pour Fenetre */
    QAction *maximiserAct;
    QAction *minimiserAct;

    /* Bare de menu pour Aide */
    QAction *rechercherAct;
    QAction *documentationAct;

    QMenu *viewMenu;
    QGraphicsView *view;
    QGraphicsScene *scene;


    //Pour les test en haut a droite
    QListWidget *customerList;
    //QListWidget *paragraphsList;
};

#endif // MAINWINDOW_H




