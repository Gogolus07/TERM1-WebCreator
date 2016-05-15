//Pour la partie meun:
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

//Pour la partie droite:
#include <QTreeWidget>
#include <QDockWidget>
#include <QListWidget>

//Pour tous nos includes personnel
#include "mainwindow.h"


/* MainWindow: =================================================== */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){


    setupWidgets("ouverture");

    createAction();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("WebCreator"));
    setUnifiedTitleAndToolBarOnMac(true);
}


/* ~MainWindow: =================================================== */
MainWindow::~MainWindow(){}

/* setupWidgets: ================================================== */
void MainWindow::setupWidgets(std::string mode){

    frame = new QFrame;
    frameLayout = new QHBoxLayout(frame);


    if(mode == "initialise")
    {
        m_scene = new QGraphicsScene(-50, -50, 70, 400);

        //Partie Gauche
        panel = new elementPanel();
        panel->setFixedHeight(300);
        frameLayout->addWidget(panel->getContainer());

        //Partie Droite
        pageW = new PageWidget();

        frameLayout->addWidget(pageW);
    }
    else
    {
        if(mode == "ouverture")
        {
            frameLayout->insertSpacing(1, 500);
        }
    }


    setCentralWidget(frame);
}

/* createToolBars: ================================================== */
void MainWindow::createToolBars(){
    m_fileToolBar = addToolBar(tr("Fichier"));
    m_fileToolBar->addAction(m_nouveauAct);
    m_fileToolBar->addAction(m_ouvrirAct);
    m_fileToolBar->addAction(m_sauvegarderAct);

#ifndef QT_NO_CLIPBOARD
    m_editToolBar = addToolBar(tr("Edition"));
    m_editToolBar->addAction(m_couperAct);
    m_editToolBar->addAction(m_copierAct);
    m_editToolBar->addAction(m_collerAct);
#endif
    m_compilationToolBar = addToolBar(tr("Compilation"));
    m_compilationToolBar->addAction(m_executerAct);
}

/* createAction: ================================================== */
void MainWindow::createAction(){
    /*----------------------------------*/
    /* Partie Fichier de la bar de menu */
    m_nouveauAct = new QAction(QIcon(":/new.png"),tr("&Nouveau projet"), this);
    m_nouveauAct->setShortcuts(QKeySequence::New);
    m_nouveauAct->setStatusTip(tr("Create a new file"));
    connect(m_nouveauAct, SIGNAL(triggered()), this, SLOT(nouveau()));

    m_nouvellePageAct = new QAction(tr("Nouve&lle pages"), this);
    m_nouvellePageAct->setStatusTip(tr("Cree une nouvelle page web"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    m_ouvrirAct = new QAction(QIcon(":/open.png"),tr("&Ouvrir..."), this);
    m_ouvrirAct->setShortcuts(QKeySequence::Open);
    m_ouvrirAct->setStatusTip(tr("Ouvrir un fichier existant"));
    connect(m_ouvrirAct, SIGNAL(triggered()), this, SLOT(ouvrir()));

    m_sauvegarderAct = new QAction(QIcon(":/save.png"), tr("&Sauvegarder"), this);
    m_sauvegarderAct->setShortcuts(QKeySequence::Save);
    m_sauvegarderAct->setStatusTip(tr("Enregistrer sur le disque"));
    connect(m_sauvegarderAct, SIGNAL(triggered()), this, SLOT(enregistrer()));

    m_sauvegarder_commeAct = new QAction(tr("Sauvegarder &Sous..."), this);
    m_sauvegarder_commeAct->setShortcuts(QKeySequence::SaveAs);
    m_sauvegarder_commeAct->setStatusTip(tr("Sauvegarder avec un nouveau nom"));
    connect(m_sauvegarder_commeAct, SIGNAL(triggered()), this, SLOT(enregistrerSous()));

    m_fermerAct = new QAction(tr("Fermer"), this);
    m_fermerAct->setShortcuts(QKeySequence::Quit);
    m_fermerAct->setStatusTip(tr("Fermer l'application"));
    //connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    m_chargerModulesAct = new QAction(tr("Recharger modules"), this);
    m_chargerModulesAct->setStatusTip(tr("Recharge la liste des modules disponibles"));
    connect(m_chargerModulesAct, SIGNAL(triggered(bool)), this,SLOT(loadModules()));

    /*---------------------------*/
    /* Bare de menu pour Edition */
    m_retablirAct = new QAction(tr("Suivant"), this);
    m_retablirAct->setShortcuts(QKeySequence::NextChild);
    m_retablirAct->setStatusTip(tr("Move the focus to the next window"));
    //connect(nextAct, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));

    m_annulerAct = new QAction(tr("Précédemment"), this);
    m_annulerAct->setShortcuts(QKeySequence::PreviousChild);
    m_annulerAct->setStatusTip(tr("Move the focus to the previous " "window"));
    //connect(previousAct, SIGNAL(triggered()), mdiArea, SLOT(activatePreviousSubWindow()));

#ifndef QT_NO_CLIPBOARD
    m_couperAct = new QAction(QIcon(":/cut.png"), tr("&Couper"), this);
    m_couperAct->setShortcuts(QKeySequence::Cut);
    m_couperAct->setStatusTip(tr("Cut the current selection's contents to the "  "clipboard"));
    //connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    m_copierAct = new QAction(QIcon(":/copy.png"), tr("Co&pier"), this);
    m_copierAct->setShortcuts(QKeySequence::Copy);
    m_copierAct->setStatusTip(tr("Copy the current selection's contents to the "  "clipboard"));
    //connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    m_collerAct = new QAction(QIcon(":/paste.png"), tr("Co&ller"), this);
    m_collerAct->setShortcuts(QKeySequence::Paste);
    m_collerAct->setStatusTip(tr("Paste the clipboard's contents into the current "  "selection"));
    //connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
#endif
    m_tousSelectionnerAct = new QAction(tr("Tous selectionner"), this);
    m_tousSelectionnerAct->setStatusTip(tr("Selectionner toute la page"));
    //connect(closeAct, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));

    m_tousDeselectionnerAct = new QAction(tr("Tous deselectionner"), this);
    m_tousDeselectionnerAct->setStatusTip(tr("tous deselectionner toute la page"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*-------------------------------*/
    /* Bare de menu pour Compilation */
    m_refaireJsonAct = new QAction(tr("Compiler"), this);
    m_refaireJsonAct->setStatusTip(tr("creer le JSON depuis le projet"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    m_relancerProjetAct = new QAction(tr("Relancer projet"), this);
    m_relancerProjetAct->setStatusTip(tr("Relancer le projet depuis le JSON"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    m_executerAct = new QAction(QIcon(":/icon_play.png"), tr("Executer"), this);
    m_executerAct ->setStatusTip(tr("Executer le projet et lancer un editeur web"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    m_executerSansDepAct = new QAction(tr("Executer sans deploiement"), this);
    m_executerSansDepAct ->setStatusTip(tr("Executer le projet sans lancer un editeur web"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*---------------------------*/
    /* Bare de menu pour Fenetre */
    m_maximiserAct = new QAction(tr("Maximiser"), this);
    m_maximiserAct ->setStatusTip(tr("Maximiser la fenetre"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    m_minimiserAct = new QAction(tr("Minimiser"), this);
    m_minimiserAct ->setStatusTip(tr("reduire la taille de la fenetre"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    /*------------------------*/
    /* Bare de menu pour Aide */
    m_rechercherAct = new QAction(tr("Rechercher"), this);
    m_rechercherAct ->setStatusTip(tr("rechercher par mot cle"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    m_documentationAct = new QAction(tr("Documentation"), this);
    m_documentationAct ->setStatusTip(tr("Documentation de WebCreator"));
    //connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));
}

/* createMenus: ================================================== */
void MainWindow::createMenus(){
    m_fichierMenu = menuBar()->addMenu(tr("&Fichier"));
    m_fichierMenu->addAction(m_nouveauAct);
    m_fichierMenu->addAction(m_nouvellePageAct);
    m_fichierMenu->addAction(m_ouvrirAct);
    m_fichierMenu->addAction(m_fermerAct);
    m_fichierMenu->addAction(m_chargerModulesAct);
    m_fichierMenu->addSeparator();
    m_fichierMenu->addAction(m_sauvegarderAct);
    m_fichierMenu->addAction(m_sauvegarder_commeAct);

    m_editionMenu = menuBar()->addMenu(tr("&Edition"));
    m_editionMenu->addAction(m_annulerAct);
    m_editionMenu->addAction(m_retablirAct);
    m_editionMenu->addSeparator();
    #ifndef QT_NO_CLIPBOARD
    m_editionMenu->addAction(m_couperAct);
    m_editionMenu->addAction(m_copierAct);
    m_editionMenu->addAction(m_collerAct);
    #endif
    m_editionMenu->addSeparator();
    m_editionMenu->addAction(m_tousSelectionnerAct);
    m_editionMenu->addAction(m_tousDeselectionnerAct);

    m_compilationMenu = menuBar()->addMenu(tr("&Compilation"));
    m_compilationMenu->addAction(m_refaireJsonAct);
    m_compilationMenu->addAction(m_relancerProjetAct);
    m_compilationMenu->addSeparator();
    m_compilationMenu->addAction(m_executerAct);
    m_compilationMenu->addAction(m_executerSansDepAct);

    m_fenetreMenu = menuBar()->addMenu(tr("&Fenêtre"));
    m_fenetreMenu->addAction(m_maximiserAct);
    m_fenetreMenu->addAction(m_minimiserAct);

    m_aideMenu = menuBar()->addMenu(tr("&Aide"));
    m_aideMenu->addAction(m_rechercherAct);
    m_aideMenu->addAction(m_documentationAct);
}

/* createStatusBar: ================================================== */
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

/* createDockWindows: ================================================= */
void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("CSS"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_customerLists = new QListWidget(dock);

    m_customerLists->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(m_customerLists);

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


//------SLOTS


void MainWindow::loadModules()
{
    panel->load();
    frameLayout->insertWidget(0, panel->getContainer(),0);
}

void MainWindow::nouveau()
{
    bool ok = false;
    QString projectName = QInputDialog::getText(this,"Nouveau","Entrez le nom du nouveau projet", QLineEdit::Normal, QString(), &ok);
    site = new Site(projectName.toStdString(), 1);

    if(ok)
    {
        setupWidgets("initialise");

        projectName = "Projet: " + projectName;
        setWindowTitle(projectName);
    }
}

void MainWindow::ouvrir()
{
    QString fichier = QFileDialog::getOpenFileName(this);
    site->charger(fichier.toStdString());

    //pageW->loadElements(site->getPage(0)->getRoot()->getBody());
}

void MainWindow::enregistrer()
{
    if(site == nullptr)
        QMessageBox::information(this, "Attention", "Vous devez avoir un projet en cours pour sauvegarder!");
    else
    {
        if(saveDir == "")
            enregistrerSous();
        else
            site->sauvegarde(saveDir.toStdString());
    }
}

void MainWindow::enregistrerSous()
{
    if(site == nullptr)
        QMessageBox::information(this, "Attention", "Vous devez avoir un projet en cours pour sauvegarder!");
    else
    {
        saveDir = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "JSON (*.json)");
        enregistrer();
    }
}


