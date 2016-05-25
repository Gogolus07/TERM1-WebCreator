#ifndef CSSPANEL_H
#define CSSPANEL_H

#include "metier/include/Element.h"
#include <QPushButton>
#include <QDockWidget>

class CssPanel: public QWidget
{
    Q_OBJECT
public:
    CssPanel();

    QDockWidget* getDock();

    void createDockElement(Element e);
    void createDockCSS();
    void setConnections();

    QDockWidget* dockCSS = nullptr;
    QPushButton *fontButton;/*!< Boutton pour changer le style du texte */
    QPushButton *colorButtonTexte;/*!< Boutton pour changer la couleur du texte */
    QPushButton *colorButtonFond;/*!< Boutton pour changer la couleur du fond */
    int r,g,b;

public slots:

    void setColorTexte();
    void setColorFond();
    void setFont();
};

#endif // CSSPANEL_H
