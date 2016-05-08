#include "elementPanel.h"
#include "moduleitem.h"

#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollBar>
#include <QToolBox>
#include <QLabel>
#include <QDir>

using namespace std;


elementPanel::elementPanel(QWidget *parent) : QWidget(parent)
{
    container = NULL;
    load();
}



//-------Listage des fichiers



void elementPanel::createFileList() //cree la liste des dossier et de leur fichiers
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

void elementPanel::createModulesList() //pour le dossier donne, cree un onglet et y ajoute les modules trouves
{
    for(size_t i = 0; i<fileList.size(); i++)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

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
                moduleItem *b = new moduleItem(name);
                b->setStyleSheet("background-color: white;");
                layout->addWidget(b);
                //layout->addLayout(createModule(img, name));
            }
        }
        layout->addStretch();//pour enlever les espaces

        QWidget *widget = new QWidget();
        widget->setLayout(layout);

        if(i == 0)
            container->addItem(widget, QString("Modules"));
        else
            container->addItem(widget, fileList[i][0].baseName());
    }
}



//-------Accessoires

void elementPanel::load()
{
    if(container != NULL)
        delete container;

    container = new QToolBox(this, Qt::Widget);
    fileList = vector<vector<QFileInfo> >();

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


    /*cout<<"test vector<vector<string>>"<<endl;
    for(size_t i = 0; i<directories.size(); i++)
    {
        cout<<directories[i][0]<<endl;

        for(size_t j = 1; j<directories[i].size(); j++)
        {
           cout<<"     "<<directories[i][j]<<endl;
        }
        cout<<endl;
    }*/

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



/*
elementPanel::elementPanel(QWidget *parent) : QWidget(parent)
{
    container = new QToolBox(this, Qt::Widget);
    QList<QFileInfo> *dirList = new QList<QFileInfo>();

    dirReader(*dirList);

    makeCategory(QDir("/Users/s-setsuna-f/GitHub/TERM1-WebCreator/Modules"));

    if(!dirList->isEmpty())
    {
        for(int i = 0; i<dirList->size(); i++)
        {
            makeCategory(dirList->at(i).absoluteDir());
        }
    }
    else
        std::cout<<"Liste NULL"<<endl;

    delete dirList;
}

void elementPanel::dirReader(QList<QFileInfo> &dirList) //recupere la liste des sous dossiers uniquement
{
    //ouverture du dossier
    if(QDir("/Users/s-setsuna-f/GitHub/TERM1-WebCreator/Modules").exists())
    {
        if(QDir("/Users/s-setsuna-f/GitHub/TERM1-WebCreator/Modules").isReadable())
        {
            cout<<"JE SUIS PASSE PAR LA"<<endl;
            dirList = QDir("/Users/s-setsuna-f/GitHub/TERM1-WebCreator/Modules").entryInfoList(QDir::NoFilter,QDir::Name); //pas de filtre, classe par ordre alphabetique
        }
        else
            std::cerr<<"Le dossier n'est pas lisible"<<endl;
    }
    else
        std::cerr<<"Le dosier n'existe pas"<<endl;
}

QList<QFileInfo> elementPanel::fileReader(QDir &dir) //renvoie la liste des fichiers pour le dossier donne
{
    QList<QFileInfo> list;

    if(dir.isReadable())
        list = dir.entryInfoList(QDir::Files, QDir::Name);

    return list;
}

QVBoxLayout* elementPanel::makeElement(const QFileInfo &img, QString name) //renvoie la miniature du module
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    if(&img != NULL)
    {
        QImage *image = new QImage(img.absoluteFilePath(), "PNG");
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap::fromImage(*image));

        layout->addWidget(label);
    }

    //layout->addWidget(new QLabel(name));
    //QPushButton *b = new QPushButton(name);
    moduleItem *b = new moduleItem(name);

    layout->addWidget(b);
    layout->addStretch();//pour enlever les espaces

    return layout;
}

void elementPanel::makeCategory(QDir dir) //pour le dossier donne, cree un onglet et y ajoute les modules trouves
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QList<QFileInfo> fileList = fileReader(dir);

    if(!fileList.isEmpty())
    {
        QString name;
        const QFileInfo *img;

        std::cout<<"Pas vide"<<endl;

        for(int i = 0; i<fileList.size(); i++)
        {
            std::cout<<fileList.at(i).path().toStdString()<<endl;

            if(fileList.at(i).suffix() == "json")
            {
                name = fileList.at(i).baseName();
                img = NULL;

                if((i + 1 < fileList.size()) && fileList.at(i + 1).suffix() == "png")
                {
                    i++;
                    img = &(fileList.at(i));
                }
                moduleItem *b = new moduleItem(name);
                b->setStyleSheet("background-color: white;");
                layout->addWidget(b);
                //layout->addLayout(makeElement(*img, name));
            }
        }
    }
    else
        layout->addSpacing(30);

    layout->addStretch();//pour enlever les espaces

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    container->addItem(widget, dir.dirName());
}

QWidget* elementPanel::getContainer()
{
    return container;
}
*/
