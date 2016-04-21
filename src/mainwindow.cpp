#include "mainwindow.h"
#include "rectangleitem.h"
#include "feuillewidget.h"
#include "pagewidget.h"
#include "elementPanel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){

    setupWidgets();

    createAction();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("WebCreator"));
    setUnifiedTitleAndToolBarOnMac(true);
}


MainWindow::~MainWindow(){}


void MainWindow::setupWidgets(){
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    scene = new QGraphicsScene(-50, -50, 70, 400);
    /*RectangleItem *item1 = new RectangleItem;
    item1->setText("1");
    item1->setPos(-15, 0);

    RectangleItem *item2 = new RectangleItem;
    item2->setText("2");
    item2->setPos(-15, 100);

    scene->addItem(item1);
    scene->addItem(item2);

    //Partie Gauche
    view=new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QColor(230, 200, 167));*/

    //Partie Droite
    PageWidget *pageW = new PageWidget();

    //FeuilleWidget *pageW = new FeuilleWidget();

    elementPanel *panel = new elementPanel();

    frameLayout->addWidget(panel->getContainer());


    //frameLayout->addWidget(view);
    frameLayout->addWidget(pageW);


    setCentralWidget(frame);
}


void MainWindow::createToolBars(){
    fileToolBar = addToolBar(tr("Fichier"));
    fileToolBar->addAction(nouveauAct);
    fileToolBar->addAction(ouvrirAct);
    fileToolBar->addAction(sauvegarderAct);

#ifndef QT_NO_CLIPBOARD
    editToolBar = addToolBar(tr("Edition"));
    editToolBar->addAction(couperAct);
    editToolBar->addAction(copierAct);
    editToolBar->addAction(collerAct);
#endif
    compilationToolBar = addToolBar(tr("Compilation"));
    compilationToolBar->addAction(executerAct);

}


void MainWindow::createAction(){
    /*----------------------------------*/
    /* Partie Fichier de la bar de menu */
    nouveauAct = new QAction(QIcon(":/new.png"),tr("&Nouveau projet"), this);
    nouveauAct->setShortcuts(QKeySequence::New);
    nouveauAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    nouvellePageAct = new QAction(tr("Nouve&lle pages"), this);
    nouvellePageAct->setStatusTip(tr("Cree une nouvelle page web"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    ouvrirAct = new QAction(QIcon(":/open.png"),tr("&Ouvrir..."), this);
    ouvrirAct->setShortcuts(QKeySequence::Open);
    ouvrirAct->setStatusTip(tr("Ouvrir un fichier existant"));
    //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    sauvegarderAct = new QAction(QIcon(":/save.png"), tr("&Sauvegarder"), this);
    sauvegarderAct->setShortcuts(QKeySequence::Save);
    sauvegarderAct->setStatusTip(tr("Enregistrer sur le disque"));
    //connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    sauvegarder_commeAct = new QAction(tr("Sauvegarder &Comme..."), this);
    sauvegarder_commeAct->setShortcuts(QKeySequence::SaveAs);
    sauvegarder_commeAct->setStatusTip(tr("Sauvegarder avec un nouveau nom"));
    //connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    fermerAct = new QAction(tr("Fermer"), this);
    fermerAct->setShortcuts(QKeySequence::Quit);
    fermerAct->setStatusTip(tr("Fermer l'application"));
    //connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    /*---------------------------*/
    /* Bare de menu pour Edition */
    retablirAct = new QAction(tr("Suivant"), this);
    retablirAct->setShortcuts(QKeySequence::NextChild);
    retablirAct->setStatusTip(tr("Move the focus to the next window"));
    //connect(nextAct, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));

    annulerAct = new QAction(tr("Précédemment"), this);
    annulerAct->setShortcuts(QKeySequence::PreviousChild);
    annulerAct->setStatusTip(tr("Move the focus to the previous " "window"));
    //connect(previousAct, SIGNAL(triggered()), mdiArea, SLOT(activatePreviousSubWindow()));

#ifndef QT_NO_CLIPBOARD
    couperAct = new QAction(QIcon(":/cut.png"), tr("&Couper"), this);
    couperAct->setShortcuts(QKeySequence::Cut);
    couperAct->setStatusTip(tr("Cut the current selection's contents to the "  "clipboard"));
    //connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copierAct = new QAction(QIcon(":/copy.png"), tr("Co&pier"), this);
    copierAct->setShortcuts(QKeySequence::Copy);
    copierAct->setStatusTip(tr("Copy the current selection's contents to the "  "clipboard"));
    //connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    collerAct = new QAction(QIcon(":/paste.png"), tr("Co&ller"), this);
    collerAct->setShortcuts(QKeySequence::Paste);
    collerAct->setStatusTip(tr("Paste the clipboard's contents into the current "  "selection"));
    //connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
#endif
    tousSelectionnerAct = new QAction(tr("Tous selectionner"), this);
    tousSelectionnerAct->setStatusTip(tr("Selectionner toute la page"));
    //connect(closeAct, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));

    tousDeselectionnerAct = new QAction(tr("Tous deselectionner"), this);
    tousDeselectionnerAct->setStatusTip(tr("tous deselectionner toute la page"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*-------------------------------*/
    /* Bare de menu pour Compilation */
    refaireJsonAct = new QAction(tr("Compiler"), this);
    refaireJsonAct->setStatusTip(tr("creer le JSON depuis le projet"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    relancerProjetAct = new QAction(tr("Relancer projet"), this);
    relancerProjetAct->setStatusTip(tr("Relancer le projet depuis le JSON"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    executerAct = new QAction(QIcon(":/icon_play.png"), tr("Executer"), this);
    executerAct ->setStatusTip(tr("Executer le projet et lancer un editeur web"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    executerSansDepAct = new QAction(tr("Executer sans deploiement"), this);
    executerSansDepAct ->setStatusTip(tr("Executer le projet sans lancer un editeur web"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*---------------------------*/
    /* Bare de menu pour Fenetre */
    maximiserAct = new QAction(tr("Maximiser"), this);
    maximiserAct ->setStatusTip(tr("Maximiser la fenetre"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    minimiserAct = new QAction(tr("Minimiser"), this);
    minimiserAct ->setStatusTip(tr("reduire la taille de la fenetre"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*------------------------*/
    /* Bare de menu pour Aide */
    rechercherAct = new QAction(tr("Rechercher"), this);
    rechercherAct ->setStatusTip(tr("rechercher par mot cle"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    documentationAct = new QAction(tr("Documentation"), this);
    documentationAct ->setStatusTip(tr("Documentation de WebCreator"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));
}


void MainWindow::createMenus(){
    FichierMenu = menuBar()->addMenu(tr("&Fichier"));
    FichierMenu->addAction(nouveauAct);
    FichierMenu->addAction(nouvellePageAct);
    FichierMenu->addAction(ouvrirAct);
    FichierMenu->addAction(fermerAct);
    FichierMenu->addSeparator();
    FichierMenu->addAction(sauvegarderAct);
    FichierMenu->addAction(sauvegarder_commeAct);

    EditionMenu = menuBar()->addMenu(tr("&Edition"));
    EditionMenu->addAction(annulerAct);
    EditionMenu->addAction(retablirAct);
    EditionMenu->addSeparator();
    #ifndef QT_NO_CLIPBOARD
    EditionMenu->addAction(couperAct);
    EditionMenu->addAction(copierAct);
    EditionMenu->addAction(collerAct);
    #endif
    EditionMenu->addSeparator();
    EditionMenu->addAction(tousSelectionnerAct);
    EditionMenu->addAction(tousDeselectionnerAct);

    CompilationMenu = menuBar()->addMenu(tr("&Compilation"));
    CompilationMenu->addAction(refaireJsonAct);
    CompilationMenu->addAction(relancerProjetAct);
    CompilationMenu->addSeparator();
    CompilationMenu->addAction(executerAct);
    CompilationMenu->addAction(executerSansDepAct);

    FenetreMenu = menuBar()->addMenu(tr("&Fenêtre"));
    FenetreMenu->addAction(maximiserAct);
    FenetreMenu->addAction(minimiserAct);

    AideMenu = menuBar()->addMenu(tr("&Aide"));
    AideMenu->addAction(rechercherAct);
    AideMenu->addAction(documentationAct);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("CSS"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);

    customerList->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("DOM"), this);

    QStringList html;    html    << tr("html")    << tr("");
    QStringList head;    head    << tr("head")    << tr("");
    QStringList meta1;   meta1   << tr("meta")    << tr("http-equiv\"Content-Type\" content=\"text/html; charset=utf-8\"");
    QStringList script1; script1 << tr("script")  << tr("type=\"text/javascript\" src=\"/scripts/extras.js\"");
    QStringList body;    body    << tr("Body")    << tr("id=\"id_body\"");
    QStringList header;  header  << tr("header")  << tr("");
    QStringList footer;  footer  << tr("footer")  << tr("");
    QStringList section; section << tr("section") << tr("");

    QTreeWidget *t=new QTreeWidget(dock);
    t->setColumnCount(2);

    QTreeWidgetItem *item_html = new QTreeWidgetItem(html);
    QTreeWidgetItem *item_head = new QTreeWidgetItem(head);
    QTreeWidgetItem *item_body = new QTreeWidgetItem(body);

    item_html->addChild(item_head);
    item_html->addChild(item_body);

    item_head->addChild(new QTreeWidgetItem(meta1));
    item_head->addChild(new QTreeWidgetItem(script1));
    item_body->addChild(new QTreeWidgetItem(header));
    item_body->addChild(new QTreeWidgetItem(section));
    item_body->addChild(new QTreeWidgetItem(footer));

    t->addTopLevelItem(item_html);

    dock->setWidget(t);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}
