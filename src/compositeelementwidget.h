#ifndef COMPOSITEELEMENTWIDGET_H
#define COMPOSITEELEMENTWIDGET_H

#include "elementwidget.h"


class CompositeElementWidget: public ElementWidget
{
public:
    CompositeElementWidget(QWidget *parent = 0);
    CompositeElementWidget(std::string, QWidget *parent = 0);
    CompositeElementWidget(std::string, std::string, QWidget *parent = 0);

    //Getter
    ElementWidget* getElementWidget(unsigned int i);
    ElementWidget* getElementWidgetById(std::string id);

    //Setter
    void addElementWidget(ElementWidget* e);

    //Methodes
    void removeElementWidget(unsigned int i);
    int size();
    //void move(int x, int y){}
    //void move(const QPoint){}
private:
    QVector<ElementWidget*> m_liste_element_widget;
    //ElementWidget *currentElementWidget;
};

#endif // COMPOSITEELEMENTWIDGET_H
