#include "elementPanel.h"
#include "moduleitem.h"

#include <QPushButton>
#include <QScrollBar>

using namespace std;

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
