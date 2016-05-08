#ifndef ELEMENTPANEL_H
#define ELEMENTPANEL_H

class QHBoxLayout;
class QVBoxLayout;
class QToolBox;
class QDir;


#include <QFileInfo>
#include <QWidget>


class elementPanel : public QWidget
{
    Q_OBJECT
public:
    explicit elementPanel(QWidget *parent = 0);

    void createFileList();
    QList<QFileInfo> listDirectories();
    QList<QFileInfo> listFiles(std::vector<QFileInfo> &dirVect);

    //QVBoxLayout* makeElement(const QFileInfo &img, QString name);
    QVBoxLayout* createModule(QFileInfo img, QString name);
    void createModulesList();

    void load();
    QWidget* getContainer();
    std::vector<std::vector<std::string> > getFilesList();
    void printFileList();

private:
    QToolBox *container;
    std::vector<std::vector<QFileInfo> > fileList;

signals:

public slots:
    void loadModules();
};


/*

class elementPanel : public QWidget
{
    Q_OBJECT
public:
    explicit elementPanel(QWidget *parent = 0);
    QList<QFileInfo> fileReader(QDir &dir);
    void dirReader(QList<QFileInfo> &dirList);
    QVBoxLayout* makeElement(const QFileInfo &img, QString name);
    void makeCategory(QDir dir);
    QWidget* getContainer();

private:
    QToolBox *container;

signals:

public slots:
};*/

#endif // ELEMENTPANEL_H
