#include "elementPanel.h"
#include "pagescene.h"
#include "moduleitem.h"

#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollBar>
#include <QToolBox>
#include <QLabel>
#include <QDir>
#include <qDebug>

#include <QToolButton>

using namespace std;
const int InsertTextButton = 10;


elementPanel::elementPanel(PageScene *scene, QWidget *parent) : QWidget(parent)
{
    container = NULL;
    m_scene = scene;
    load();
}



//-------Listage des fichiers



 //cree la liste des dossier et de leur fichiers
void elementPanel::createFileList()
{
    QList<QFileInfo> directories;
    QList<QFileInfo> files;

    directories = listDirectories();

    if(!directories.isEmpty())
    {
        for(int i = 0; i<directories.size(); i++)
        {
            vector<QFileInfo> dirVect;
            dirVect.push_back(directories.at(i));

            files = listFiles(dirVect);

            for(int j = 0; j<files.size(); j++)
                dirVect.push_back(files.at(j));

            fileList.push_back(dirVect);
        }
    }
    else
        cout<<"Vide!"<<endl;
}

QList<QFileInfo> elementPanel::listDirectories() //cree la liste des dossiers
{
    QList<QFileInfo> dirList;

    //ouverture du dossier
    QDir dir = QDir("/Users/s-setsuna-f/GitHub/build-TERM1-WebCreator-Desktop_Qt_5_5_1_clang_64bit-Debug/Modules/");

    if(dir.exists())
    {
        if(dir.isReadable())
            dirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotDot,QDir::Name); //on recupere les dossiers uniquement (sauf le pere), classes par ordre alphabetique
        else
            std::cout<<"Le dossier n'est pas lisible"<<endl;
    }
    else
        std::cout<<"Le dosier n'existe pas"<<endl;

    return dirList;
}

QList<QFileInfo> elementPanel::listFiles(vector<QFileInfo> &dirVect) //cree la liste des fichiers pour le dossier donne
{
    QList<QFileInfo> list;

    list = QDir(dirVect.at(0).absoluteFilePath()).entryInfoList(QDir::Files,QDir::Name);

    return list;
}



//-------Creation du menu


QVBoxLayout* elementPanel::createModule(QFileInfo img, QString name) //renvoie la miniature du module
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    if(img.exists())
    {
        QImage *image = new QImage(img.absoluteFilePath(), "PNG");
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap::fromImage(*image));

        layout->addWidget(label);
    }

    layout->addWidget(new QLabel(name));

    return layout;
}

void elementPanel::buttonGroupClicked(int id)
{
    //qDebug()<<"Je suis dans buttonGroupClicked="<<id;
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

void elementPanel::createModulesList() //pour le dossier donne, cree un onglet et y ajoute les modules trouves
{
    int x=0;
    int y=0;

    for(size_t i = 0; i<fileList.size(); i++)
    {
        //QVBoxLayout *layout = new QVBoxLayout(this);
        QGridLayout *layout = new QGridLayout;

        for(size_t j = 1; j<fileList[i].size(); j++)
        {
            QFileInfo img;
            QString name;
            if(fileList[i][j].suffix() == "json")
            {
                name = fileList[i][j].baseName();
                img = QFileInfo();

                if(((size_t)(j+1) < fileList[i].size()) && fileList[i][j+1].suffix() == "png")
                {
                    j++;
                    img = fileList[i][j];
                }

                /*-----------*/
                buttonGroup = new QButtonGroup(this);
                buttonGroup->setExclusive(false);
                connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonGroupClicked(int)));

                QToolButton *textButton = new QToolButton;
                textButton->setCheckable(true);
                if(name=="p"){
                    buttonGroup->addButton(textButton, InsertTextButton);
                    textButton->setIcon(QIcon(QPixmap(":/p.png")));
                }else if(name=="a"){
                    buttonGroup->addButton(textButton, InsertTextButton+1);
                    textButton->setIcon(QIcon(QPixmap(":/a.png")));
                }else if(name=="h"){
                    buttonGroup->addButton(textButton, InsertTextButton+2);
                    textButton->setIcon(QIcon(QPixmap(":/h.png")));
                }else if(name=="img"){
                    buttonGroup->addButton(textButton, InsertTextButton+3);
                    textButton->setIcon(QIcon(QPixmap(":/img.png")));
                }else if(name=="video"){
                    buttonGroup->addButton(textButton, InsertTextButton+4);
                    textButton->setIcon(QIcon(QPixmap(":/video.png")));
                }else if(name=="musique"){
                    buttonGroup->addButton(textButton, InsertTextButton+5);
                    textButton->setIcon(QIcon(QPixmap(":/musique.png")));
                }else if(name=="rond"){
                    buttonGroup->addButton(textButton, InsertTextButton+6);
                    textButton->setIcon(QIcon(QPixmap(":/rond.png")));
                }else if(name=="rectangle"){
                    buttonGroup->addButton(textButton, InsertTextButton+7);
                    textButton->setIcon(QIcon(QPixmap(":/rectangle.png")));
                }else if(name=="trait"){
                    buttonGroup->addButton(textButton, InsertTextButton+8);
                    textButton->setIcon(QIcon(QPixmap(":/trait.png")));
                }else{
                    buttonGroup->addButton(textButton, InsertTextButton+9);
                    textButton->setIcon(QIcon(QPixmap(":/custom.png")));
                }
                textButton->setIconSize(QSize(50, 50));
                QGridLayout *textLayout = new QGridLayout;
                textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
                textLayout->addWidget(new QLabel(tr(name.toStdString().c_str())), 1, 0, Qt::AlignCenter);
                QWidget *textWidget = new QWidget;
                textWidget->setLayout(textLayout);
                layout->addWidget(textWidget, x, y);

                layout->setRowStretch(3, 10);
                layout->setColumnStretch(2, 10);

                y=(y==1)?0:1;
                x+=(y==1)?0:1;

                //moduleItem *b = new moduleItem(name);
                //b->setStyleSheet("background-color: white;");
                //layout->addWidget(b);
                //layout->addLayout(createModule(img, name));
            }
        }
        //layout->addStretch();//pour enlever les espaces
        QWidget *itemWidget = new QWidget;
        itemWidget->setLayout(layout);
        x=0; y=0;

        //QWidget *widget = new QWidget();
        //widget->setLayout(layout);

        if(i == 0)
            container->addItem(itemWidget, QString("Modules"));
        else
            container->addItem(itemWidget, fileList[i][0].baseName());
    }
}


void elementPanel::textInserted(QButtonGroup *pointerTypeGroup)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    m_scene->setMode(PageScene::Mode(pointerTypeGroup->checkedId()));
}


//-------Accessoires

void elementPanel::load()
{
    if(container != NULL)
        delete container;

    container = new QToolBox(this, Qt::Widget);
    fileList = vector<vector<QFileInfo> >();

    container->setFixedWidth(202);

    createFileList();
    createModulesList();
}

QWidget* elementPanel::getContainer()
{
    return container;
}

vector<vector<string> > elementPanel::getFilesList() //renvoie l'equivalent de fileList en std::string
{
    vector<vector<string> > directories;

    for(size_t i = 0; i<fileList.size(); i++)
    {
        vector<string> files;

        for(size_t j = 0; j<fileList[i].size(); j++)
        {
            files.push_back(fileList[i][j].absoluteFilePath().toStdString());
        }

        directories.push_back(files);
    }


    return directories;
}

void elementPanel::printFileList(){
    cout<<endl;
    for(size_t i = 0; i<fileList.size(); i++)
    {
        cout<<"Dossier("<<fileList[i].size()-1<<" fichiers): "<<endl;
        cout<<fileList[i][0].absoluteFilePath().toStdString()<<endl;

        for(size_t j = 1; j<fileList[i].size(); j++)
        {
            cout<<"     "<<fileList[i][j].baseName().toStdString()<<"."<<fileList[i][j].suffix().toStdString()<<endl;
        }
        cout<<endl;
    }
    cout<<endl;
}



//------Signaux

void elementPanel::loadModules()
{
    load();
}
