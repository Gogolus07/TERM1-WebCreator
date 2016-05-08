#include "compositeelementwidget.h"
#include <TypeInfo>
CompositeElementWidget::CompositeElementWidget(QWidget *parent):
    ElementWidget(parent){

}

CompositeElementWidget::CompositeElementWidget(std::string moduleName, QWidget *parent):
    ElementWidget(moduleName, parent){
}

CompositeElementWidget::CompositeElementWidget(std::string moduleName, std::string content, QWidget *parent):
    ElementWidget(moduleName, content, parent){

}

//Getter
ElementWidget* CompositeElementWidget::getElementWidget(unsigned int i){
    if((unsigned int)m_liste_element_widget.length() > i)
        return m_liste_element_widget[i];
    else
        return nullptr;
}

ElementWidget* CompositeElementWidget::getElementWidgetById(std::string id){

    //ElementWidget*elemntwidget=nullptr;
    for(int i=0; i<m_liste_element_widget.length(); i++)
        if(m_liste_element_widget[i]->getId()==id)
            return m_liste_element_widget[i];
        else
            //si l'element en question est un composite (possede une liste de sous widget)
            if ( typeid(CompositeElementWidget) == typeid(*m_liste_element_widget[i]) ){
                //On parcour recursivement la liste des sous elements.
                return dynamic_cast<CompositeElementWidget*>(m_liste_element_widget[i])->getElementWidgetById(id);
            }
    //si rien n'est trouvé on retourne NULL
    return nullptr;
}


//Setter
void CompositeElementWidget::addElementWidget(ElementWidget* e){
    m_liste_element_widget.push_back(e);
}

//Methodes
void CompositeElementWidget::removeElementWidget(unsigned int i){
    if((unsigned int)m_liste_element_widget.length() > i)
        m_liste_element_widget.erase(m_liste_element_widget.begin()+i);
}


int CompositeElementWidget::size(){
    return m_liste_element_widget.size();
}










