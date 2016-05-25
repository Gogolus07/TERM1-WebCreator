#include "cssPanel.h"
#include <QObject>
#include <QColorDialog>
#include <QFontDialog>
#include <QPalette>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QString>


CssPanel::CssPanel()
{
    createDockCSS();
}


QDockWidget* CssPanel::getDock()
{
    return dockCSS;
}


void CssPanel::createDockElement(Element e)
{
    dockCSS = new QDockWidget(tr("CSS de l'objet selectione"));

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 200);

    QLabel *background = new QLabel("Couleur de fond");
    std::string style = e.getStyle("background-color");
    if(style!="")
    {
        std::string res="background-color: "+style;
        background->setStyleSheet(res.c_str());
    }
    QLabel *color = new QLabel("Couleur de texte");
    style = e.getStyle("color");
    if(style!="")
    {
        std::string res="color: "+style;
        color->setStyleSheet(res.c_str());
    }
    QLabel *font = new QLabel("Police utilisee");
    style = e.getStyle("font-family");
    if(style!="")
    {
        std::string res="font-family: "+style;
        font->setStyleSheet(res.c_str());

    }
    QLabel *fontsize = new QLabel("Taille de la police");
    style = e.getStyle("font-size");
    if(style!="")
    {
        std::string res="font-size: "+style;
        fontsize->setStyleSheet(res.c_str());

    }
    layout->addWidget(background);
    layout->addWidget(color);
    layout->addWidget(font);
    layout->addWidget(fontsize);
    if(e.getStyle("font-weight")=="bold")
    {
        QLabel *bold = new QLabel("Texte gras");
        bold->setStyleSheet("font-weight: bold;");
        layout->addWidget(bold);
    }
    if(e.getStyle("font-style")=="italic")
    {
        QLabel *italic = new QLabel("Texte italique");
        italic->setStyleSheet("font-style: italic;");
        layout->addWidget(italic);
    }
    style=e.getStyle("text-decoration");
    if(style=="underline")
    {
        QLabel *ligne = new QLabel("Texte sous ligne");
        ligne->setStyleSheet("text-decoration: underline;");
        layout->addWidget(ligne);
    } else {
        if(style=="line-through")
        {
            QLabel *ligne = new QLabel("Texte barre");
            ligne->setStyleSheet("text-decoration: line-through;");
            layout->addWidget(ligne);
        }
    }

    dockCSS->setWidget(page);
    //addDockWidget(Qt::RightDockWidgetArea, dock);
}

void CssPanel::createDockCSS()
{
    dockCSS = new QDockWidget(tr("CSS"));
    dockCSS->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 200);

    colorButtonTexte = new QPushButton(tr("Changer la couleur du texte"));
    //connect(colorButtonTexte, SIGNAL(clicked()), this, SLOT(setColorTexte()));

    colorButtonFond = new QPushButton(tr("Changer la couleur du fond"));
    //connect(colorButtonFond, SIGNAL(clicked()), this, SLOT(setColorFond()));

    fontButton = new QPushButton(tr("Changer le style du texte"));
    //connect(fontButton, SIGNAL(clicked()), this, SLOT(setFont()));

    layout->addWidget(colorButtonTexte);
    layout->addWidget(colorButtonFond);
    layout->addWidget(fontButton);
    dockCSS->setWidget(page);
    //addDockWidget(Qt::RightDockWidgetArea, dock);
}

void CssPanel::setConnections()
{
    connect(colorButtonFond, SIGNAL(clicked()), this, SLOT(setColorFond()));
    connect(colorButtonTexte, SIGNAL(clicked()), this, SLOT(setColorTexte()));
    connect(fontButton, SIGNAL(clicked()), this, SLOT(setFont()));
}

//---- SLOTS


void CssPanel::setColorTexte()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green);
    if (color.isValid()) {
        color.getRgb(&r,&g,&b);
        QPalette Pal(palette());
        /*std::string coul="color: rgb(";
        coul+=std::to_string(r)+", "+std::to_string(g)+", "+std::to_string(b)+");";
        std::cout<<coul<<std::endl;*/
        Pal.setColor(QPalette::Button, color.rgb());
        colorButtonTexte->setAutoFillBackground(true);
        colorButtonTexte->setPalette(Pal);
    }
}

void CssPanel::setColorFond()
{
    QColor color;
    color = QColorDialog::getColor(Qt::green);
    if (color.isValid()) {
        color.getRgb(&r,&g,&b);
        QPalette Pal(palette());
        /*std::string coul="background-color: rgb(";
        coul+=std::to_string(r)+", "+std::to_string(g)+", "+std::to_string(b)+");";
        std::cout<<coul<<std::endl;*/
        Pal.setColor(QPalette::Button, color.rgb());
        colorButtonFond->setAutoFillBackground(true);
        colorButtonFond->setPalette(Pal);
    }
}

void CssPanel::setFont()
{
    QFont font;
    font = QFontDialog::getFont(0);
    std::cout<<font.toString().toStdString()<<std::endl;
    std::string style="";
    if(font.bold())
    {
        style+="font-weight: bold;\n";
    }
    if(font.italic())
    {
        style+="font-style: italic;\n";
    }
    if(font.strikeOut())
    {
        style+="text-decoration: line-through;\n";
    }
    if(font.underline())
    {
        style+="text-decoration: underline;\n";
    }
    style+="font-family: "+font.family().toStdString()+";\n";
    style+="font-size: "+std::to_string(font.pointSize())+"pt;";
    std::cout<<style<<std::endl;
}
