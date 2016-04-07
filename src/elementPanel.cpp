#include "elementPanel.h"

using namespace std;

elementPanel::elementPanel(QWidget *parent) : QWidget(parent)
{
    container = new QToolBox(this, Qt::Widget);
    QList<QFileInfo> *dirList = new QList<QFileInfo>();

    dirReader(*dirList);

    makeCategory(QDir("C:/Users/Emmanuel/git/build-TERM1-WebCreator-Desktop_Qt_5_2_1_MinGW_32bit-Debug/debug/Modules"));

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
    if(QDir("C:/Users/Emmanuel/git/build-TERM1-WebCreator-Desktop_Qt_5_2_1_MinGW_32bit-Debug/debug/Modules").exists())
    {
        if(QDir("C:/Users/Emmanuel/git/build-TERM1-WebCreator-Desktop_Qt_5_2_1_MinGW_32bit-Debug/debug/Modules").isReadable())
        {
            cout<<"JE SUIS PASSE PAR LA"<<endl;
            dirList = QDir("C:/Users/Emmanuel/git/build-TERM1-WebCreator-Desktop_Qt_5_2_1_MinGW_32bit-Debug/debug/Modules").entryInfoList(QDir::NoFilter,QDir::Name); //pas de filtre, classe par ordre alphabetique
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

    layout->addWidget(new QLabel(name));

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

                layout->addLayout(makeElement(*img, name));
            }
        }
    }
    else
        layout->addSpacing(30);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    container->addItem(widget, dir.dirName());
}

QWidget* elementPanel::getContainer()
{
    return container;
}
