#ifndef ELEMENTPANEL_H
#define ELEMENTPANEL_H

#include <iostream>
#include <QWidget>
#include <QToolBox>
#include <QDir>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QLabel>

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
};

#endif // ELEMENTPANEL_H
