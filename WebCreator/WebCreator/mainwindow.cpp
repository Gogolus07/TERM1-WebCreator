//Pour la partie meun:
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QDialog>

//Pour la partie droite:
#include <QTreeWidget>
#include <QDockWidget>
#include <QListWidget>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>


#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>
#include <QToolBox>
#include <QDebug>
#include <QFontComboBox>
#include <QToolButton>

//Pour tous nos includes personnel
#include "mainwindow.h"
//#include "../dragwidget.h"
//#include "pagewidget2.h"

#include "pagescene.h"

const int InsertTextButton = 10;


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
        createToolBox();
        m_site = new Site("NomDuSite", 15);
        m_site->addPage();
        m_pageWeb=m_site->getPage(0);
        m_pageWeb->setNom("premiere page");
        m_scene = new PageScene(*m_pageWeb, m_itemMenu, this);
        //Taille de la page web (devra etre modifiable)
        m_scene->setSceneRect(QRectF(0, 0, 1000, 1000));

        //connect(scene, SIGNAL(itemInserted(DiagramItem*)),         this, SLOT(itemInserted(DiagramItem*)));
        connect(m_scene, SIGNAL(textInserted(QGraphicsTextItem*)), this, SLOT(textInserted(QGraphicsTextItem*)));
        connect(m_scene, SIGNAL(itemSelected(QGraphicsItem*)),     this, SLOT(itemSelected(QGraphicsItem*)));

        QHBoxLayout *layout = new QHBoxLayout;
        panel = new elementPanel(m_scene);

        //layout->addWidget(toolBox); // On ajoute la partie Gauche de la fenetre
        layout->addWidget(panel->getContainer()); // On ajoute la partie Gauche de la fenetre
        m_view = new QGraphicsView(m_scene); // On ajoute la partie centrale de la fenetre

        QTabWidget*onglets = new QTabWidget(this);
        onglets->addTab(m_view, "Premiere page");

        layout->addWidget(onglets);

        QWidget *widget = new QWidget;
        widget->setLayout(layout);

        setCentralWidget(widget); //On met le tout dans la fenetre



        //Partie Gauche
        //panel = new elementPanel();
        //panel->setFixedHeight(300);
        //frameLayout->addWidget(panel->getContainer());

        //QGraphicsView *pageView=new QGraphicsView();


        //QTabWidget*onglets = new QTabWidget(this);
        //onglets->addTab(dw, "Premiere Page");
        //onglets->addTab(p, "Premiere Page");
        //onglets->addTab(pageW1, "Premiere Page");


        //frameLayout->addWidget(onglets);
        //frameLayout->addWidget(dw);
    }
    else
    {
        if(mode == "ouverture")
        {
            frameLayout->insertSpacing(1, 500);
        }
    }


    //setCentralWidget(frame);
}



//! [21]
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    //layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    //layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),0, 1);
    //layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
//! [21]

    //qDebug()<<"Je suis dans createToolBox";

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    //backgroundButtonGroup = new QButtonGroup(this);
    //connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    //QGridLayout *backgroundLayout = new QGridLayout;
    //backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
    //                                                       ":/images/background1.png"), 0, 0);
    //backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
    //                                                       ":/images/background2.png"), 0, 1);
    //backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
    //                                                       ":/images/background3.png"), 1, 0);
    //backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
    //                                                       ":/images/background4.png"), 1, 1);

    //backgroundLayout->setRowStretch(2, 10);
    //backgroundLayout->setColumnStretch(2, 10);

    //QWidget *backgroundWidget = new QWidget;
    //backgroundWidget->setLayout(backgroundLayout);


//! [22]
    //toolBox = new QToolBox;
    //toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    //toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    //toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    //toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}



//! [2]
/*Quand on clique sur un module*/
void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == InsertTextButton) {
        m_scene->setMode(PageScene::InsertText);
    } else {
        //scene->setItemType(DiagramItem::DiagramType(id));
        m_scene->setMode(PageScene::InsertItem);
    }
}
//! [2]


//! [3]
/*Quand on veut supprimer un module se trouvant sur la page web*/
void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, m_scene->selectedItems()) {
         /*if (item->type() == PageScene::Type)
             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();*/
         m_scene->removeItem(item);
         delete item;
     }
}
//! [3]

//! [4]
void MainWindow::pointerGroupClicked(int)
{
    m_scene->setMode(PageScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
/*Quand on veut envoyer un module devant les autres*/
void MainWindow::bringToFront()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == TextItem::Type*5)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [5]

//! [6]
/*Quand on veut envoyer un module derrière les autres*/
void MainWindow::sendToBack()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == TextItem::Type*5)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [6]

//! [7]
/*Quand on veut cliquer sur la page et afficher un item et non en ajouter a chaque fois que l'on cliquera sur la page*/
/*CAS d'un non text*/
/*void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}*/
//! [7]

//! [8]
/*Quand on veut cliquer sur la page et afficher un item et non en ajouter a chaque fois que l'on cliquera sur la page*/
/*CAS d'un text*/
void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    m_scene->setMode(PageScene::Mode(pointerTypeGroup->checkedId()));
    panel->textInserted(pointerTypeGroup);
}
//! [8]

//! [9]
void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}
//! [9]

//! [10]
void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}
//! [10]

//! [11]
/*Quand on veut faire un zoom*/
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = m_view->matrix();
    m_view->resetMatrix();
    m_view->translate(oldMatrix.dx(), oldMatrix.dy());
    m_view->scale(newScale, newScale);
}
//! [11]

//! [12]
/*Pour changer la couleur du text*/
void MainWindow::textColorChanged()
{
    m_textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/textpointer.png",
                                     qvariant_cast<QColor>(m_textAction->data())));
    textButtonTriggered();
}
//! [12]

//! [13]
/*Pour changer la couleur de la forme*/
/*void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}*/
//! [13]


//! [15]
/*Utile pour le [12]*/
void MainWindow::textButtonTriggered()
{
    m_scene->setTextColor(qvariant_cast<QColor>(m_textAction->data()));
}
//! [15]

//! [16]
/*Utile pour le [13]*/
/*void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}*/
//! [16]

//! [18]
void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(m_boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(m_italicAction->isChecked());
    font.setUnderline(m_underlineAction->isChecked());

    m_scene->setFont(font);
}
//! [18]

//! [19]
/*Quand on met a jour la barre de menu pour dire quel menu a changer quel couleur est selectioné...*/
/*Il me semble*/
void MainWindow::itemSelected(QGraphicsItem *item)
{
    TextItem *textItem = qgraphicsitem_cast<TextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    m_boldAction->setChecked(font.weight() == QFont::Bold);
    m_italicAction->setChecked(font.italic());
    m_underlineAction->setChecked(font.underline());

}
//! [19]


//! [30]
/*Pour creer les menu avec des couleurs*/
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
//! [30]


//! [31]
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}
//! [31]


//! [32]
/*Pour faire des carre de couleur*/
QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [32]














/* createToolBars: ================================================== */
void MainWindow::createToolBars(){
    m_fileToolBar = addToolBar(tr("Fichier"));
    m_fileToolBar->addAction(m_nouveauAct);
    m_fileToolBar->addAction(m_ouvrirAct);
    m_fileToolBar->addAction(m_sauvegarderAct);

    m_itemToolBar = addToolBar(tr("Edition"));
    m_itemToolBar->addAction(m_deleteAction);
    m_itemToolBar->addAction(m_toFrontAction);
    m_itemToolBar->addAction(m_sendBackAction);

#ifndef QT_NO_CLIPBOARD
    m_editToolBar = addToolBar(tr("Edition"));
    m_editToolBar->addAction(m_couperAct);
    m_editToolBar->addAction(m_copierAct);
    m_editToolBar->addAction(m_collerAct);
#endif
    m_compilationToolBar = addToolBar(tr("Compilation"));
    m_compilationToolBar->addAction(m_executerAct);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 60; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    m_textToolBar = addToolBar(tr("Font"));
    m_textToolBar->addWidget(fontCombo);
    m_textToolBar->addWidget(fontSizeCombo);
    m_textToolBar->addAction(m_boldAction);
    m_textToolBar->addAction(m_italicAction);
    m_textToolBar->addAction(m_underlineAction);

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%")<<tr("200%")<<tr("250%")<<tr("300%")<<tr("350%")<<tr("400%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(sceneScaleChanged(QString)));

    m_toolsToolBar = addToolBar(tr("Outils"));
    m_toolsToolBar->addWidget(sceneScaleCombo);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(PageScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(PageScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));



    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);

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
    connect(m_executerAct, SIGNAL(triggered()), this, SLOT(compilerLeSite()));

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

    /*----------------*/
    /*Pour le contenue*/
    m_toFrontAction = new QAction(QIcon(":/bringtofront.png"), tr("Bring to &Front"), this);
    m_toFrontAction->setShortcut(tr("Ctrl+F"));
    m_toFrontAction->setStatusTip(tr("Bring item to front"));
    //connect(m_toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));

    m_sendBackAction = new QAction(QIcon(":/sendtoback.png"), tr("Send to &Back"), this);
    m_sendBackAction->setShortcut(tr("Ctrl+B"));
    m_sendBackAction->setStatusTip(tr("Send item to back"));
    //connect(m_sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    m_deleteAction = new QAction(QIcon(":/delete.png"), tr("&Delete"), this);
    m_deleteAction->setShortcut(tr("Delete"));
    m_deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    m_textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

    m_boldAction = new QAction(tr("Bold"), this);
    m_boldAction->setCheckable(true);
    QPixmap pixmap(":/bold.png");
    m_boldAction->setIcon(QIcon(pixmap));
    m_boldAction->setShortcut(tr("Ctrl+B"));
    //connect(m_boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    m_italicAction = new QAction(QIcon(":/italic.png"), tr("Italic"), this);
    m_italicAction->setCheckable(true);
    m_italicAction->setShortcut(tr("Ctrl+I"));
    //connect(m_italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    m_underlineAction = new QAction(QIcon(":/underline.png"), tr("Underline"), this);
    m_underlineAction->setCheckable(true);
    m_underlineAction->setShortcut(tr("Ctrl+U"));
    connect(m_underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));
}

void MainWindow::compilerLeSite(){
    qDebug()<<m_pageWeb->getRoot()->getBody()->toString().c_str();
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
    m_editionMenu->addAction(m_deleteAction);
    m_editionMenu->addSeparator();
    m_editionMenu->addAction(m_tousSelectionnerAct);
    m_editionMenu->addAction(m_tousDeselectionnerAct);
    m_editionMenu->addSeparator();
    m_editionMenu->addAction(m_toFrontAction);
    m_editionMenu->addAction(m_sendBackAction);

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

   /* m_customerLists->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    */
    m_customerLists->addItems(QStringList()<<"");

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
    //site = new Site(projectName.toStdString(), 1);
    //web=site->getPage(0);
    //pageW = new PageWidget(web);

    if(ok)
    {
        setupWidgets("initialise");

        projectName = "Projet: " + projectName;
        setWindowTitle(projectName);
    }
}

void MainWindow::ouvrir()
{
    //QString fichier = QFileDialog::getOpenFileName(this);
    //site->charger(fichier.toStdString());
}

void MainWindow::enregistrer()
{
    /*if(site == nullptr)
        QMessageBox::information(this, "Attention", "Vous devez avoir un projet en cours pour sauvegarder!");
    else
    {
        if(saveDir == "")
            enregistrerSous();
        else
            site->sauvegarde(saveDir.toStdString());
    }*/
}

void MainWindow::enregistrerSous()
{
    /*if(site == nullptr)
        QMessageBox::information(this, "Attention", "Vous devez avoir un projet en cours pour sauvegarder!");
    else
    {
        saveDir = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "JSON (*.json)");
        enregistrer();
    }*/
}


