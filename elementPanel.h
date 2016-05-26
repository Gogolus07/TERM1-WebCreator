#ifndef ELEMENTPANEL_H
#define ELEMENTPANEL_H

class PageScene;
class QHBoxLayout;
class QVBoxLayout;
class QToolBox;
class QDir;
class QGraphicsTextItem;

#include <QButtonGroup>
#include <QFileInfo>
#include <QWidget>


/**
 * @class elementPanel
 * Classe de gestion des Modules. Cree une liste des modules disponibles et les rend utilisables dans un projet.
 */
class elementPanel : public QWidget
{
    Q_OBJECT
public:

    /**
     * @fn elementPanel(QWidget *parent = 0)
     * @brief Constructeur
     * @param QWidget *parent {parent Qt, n'a generalement pas à être renseigne}
     */
    explicit elementPanel(PageScene *scene, QWidget *parent = 0);

    /**
     * @fn createFileList()
     * @brief Cree la liste des sous dossiers et fichiers presents dans le dossier Modules
     */
    void createFileList();

    /**
     * @fn listDirectories()
     * @brief Cree la liste des sous-dossiers du dossier Modules
     * @return QList<QFileInfo> {La liste des sous-dossier du dossier Modules}
     */
    QList<QFileInfo> listDirectories();

    /**
     * @fn listFiles()
     * @brief Cree la liste des fichiers pour le dossier specifie
     * @param std::vector<QFileInfo> &dirVect {Sous vecteur de fileList (correspondant a un dossier) dont on veut recuperer la lite des fichiers}
     * @return QList<QFileInfo> {Liste des fichiers du dossier specifie}
     */
    QList<QFileInfo> listFiles(std::vector<QFileInfo> &dirVect);

    /**
     * @fn createModule()
     * @brief Cree la miniature du module a afficher
     * @param QFileInfo img {Image du module (si disponible)}
     * @param QString name {Nom du module a afficher}
     * @return QVBoxLayout*  {Layout contenant l'image du module et son nom}
     */
    QVBoxLayout* createModule(QFileInfo img, QString name);

    /**
     * @fn createModulesList();
     * @brief Cree la liste des miniatures des modules charges
     */
    void createModulesList();


    /**
     * @fn load()
     * @brief Recherche les modules disponibles et cree leur miniatures. Methode principale de la classe.
     */
    void load();

    /**
     * @fn getContainer()
     * @brief Renvoie le conteneur Qt pour afficher la liste des modules
     * @return QWidget {Conteneur Qt de la liste des modules}
     */
    QWidget* getContainer();

    /**
     * @fn getFilesList()
     * @brief Renvoie la liste des dossiers et fichier du dossier Modules sous forme de std::string
     * @return std::vector<std::vector<std::string> > {Liste des fichiers sous forme de std::string. Chaque sous-vecteur correspond a un dossier (contenu en [0]) suivi de ses fichiers.}
     */
    std::vector<std::vector<std::string> > getFilesList();

    /**
     * @fn printFileList();
     * @brief Affiche la liste des dossiers et fichier du dossier Modules sur la sortie standard. Fonction de test.
     */
    void printFileList();


    void textInserted(QButtonGroup *pointerTypeGroup);

private:
    QToolBox *container; /*!< Conteneur Qt des modules. Objet à afficher*/
    std::vector<std::vector<QFileInfo> > fileList; /*!< Liste des sous-dossiers et fichiers du dossier Modules. Chaque sous vecteur correspond a un sous-dossier (contenu en [0]) suivi des fichiers. Le dossier Modules correspond a fileList[0][0]*/
    QButtonGroup *buttonGroup;
    PageScene *m_scene;

signals:

public slots:

    /**
     * @fn loadModules()
     * @brief [SLOT] Fait appel a load()
     */
    void loadModules();

    void buttonGroupClicked(int id);

};

#endif // ELEMENTPANEL_H
