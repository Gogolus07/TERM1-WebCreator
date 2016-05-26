#include "pagescene.h"

#include <QGraphicsSceneMouseEvent>
#include <QTextCursor>
#include "metier/include/Body.h"
#include "metier/include/Html.h"
#include <QDebug>

PageScene::PageScene(PageWeb &pageWeb, QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    m_ItemMenu  = itemMenu;
    m_Mode      = MoveItem;
    m_ItemType  = Step;
    m_textItem  = 0;
    m_TextColor = Qt::black;
    m_pageweb   = pageWeb;

    html = pageWeb.getRoot();
    html->getHead()->setTitle("Le projet");
    body = html->getBody();
    /*Element e1("Elmt1");
    Element e2("Elmt2");
    body->addElement(e1);
    body->addElement(e2);
    qDebug()<<"Le body: "<<body->toString().c_str();*/
}

void PageScene::setTextColor(const QColor &color)
{
    m_TextColor = color;
    if (isItemChange(TextItem::Type)) {
        TextItem *item = qgraphicsitem_cast<TextItem *>(selectedItems().first());
        item->setDefaultTextColor(m_TextColor);
        //item->getElement().setStyle("color", blue);
    }
}

void PageScene::setFont(const QFont &font)
{
    m_Font = font;

    if (isItemChange(TextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<TextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item->setFont(m_Font);
        qDebug()<<"FONT"<<font.toString();
    }
}

void PageScene::setMode(Mode mode)
{
    m_Mode = mode;
}

void PageScene::setItemType(DiagramType type)
{
    m_ItemType = type;
}

void PageScene::editorLostFocus(TextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);
    //integrationElementToBody();
    std::map<std::string, std::string> varItem=item->getElement().getAllStyle();
    QString style_str="";




    /*
         qDebug()<<"STYLE="<<item->getElement().getStyle("font-family").c_str();


      if(varItem.empty()==false){
        std::map<std::string, std::string>::key_compare mycomp = varItem.key_comp();

        std::string highest = varItem.rbegin()->first;     // key value of last element

        qDebug()<<"DANS LES ELF";
        std::map<std::string, std::string>::iterator it = varItem.begin();
        do {
            std::string sf =it->first;
            std::string ss =it->second;
            style_str.append(sf.c_str());
            style_str.append(":");
            style_str.append(sf.c_str());
            style_str.append(";");

            std::cout << style_str.toStdString() << '\n';
        }while ( mycomp((*it++).first, highest) );

    }*/



    //QFont f;
    //f.setStyleName("Helvetica");
    //item->setFont(f);



    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
        for(int j=body->nbElement(); j>=0; j--)
            body->removeElement(j);
        QVector<Element*> eltsBis;
        size_t size = elts.size();
        for(size_t i=size; i>=0; i--){

            if(elts.at(i)->getId() == item->getElement().getId()){
                //On supprime tout le body
                //elts.remove(i);
                elts.pop_back();

            }else{
                eltsBis.push_back(elts.at(i));
                elts.pop_back();
            }
        }
        elts=eltsBis;
        integrationElementToBody();
        /*for(size_t i=0; i<elts.size(); i++){
            if(elts.at(i)->getId() == item->getElement().getId()){
                //On supprime tout le body
                elts.remove(i);
            }
        }*/
    }
    else
        integrationElementToBody();

}



void PageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (m_Mode) {
        case InsertText:
            m_textItem = new TextItem();
            m_textItem->setFont(m_Font);
            m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_textItem->setZValue(1000.0);
            connect(m_textItem, SIGNAL(lostFocus(TextItem*)),
                    this, SLOT(editorLostFocus(TextItem*)));
            connect(m_textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(m_textItem);
            m_textItem->setDefaultTextColor(m_TextColor);
            m_textItem->setPos(mouseEvent->scenePos());
            emit textInserted(m_textItem);
            elts.append(&(m_textItem->getElement()));
            //qDebug()<<"Le body: \n"<<elts.at(0)->toString().c_str();
            //qDebug()<<"Le body: \n"<<body->toString().c_str();

            //for(int i=0; i<elts.size(); i++)
            //    qDebug()<<elts.at(i)->getContent().c_str();


    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   if (m_Mode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}


void PageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool PageScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}


void PageScene::integrationElementToBody(){

    //On supprime tout le body
    for(int i=body->nbElement(); i>=0; i--)
        body->removeElement(i);

    //On met a jour le body
    foreach (Element *e, elts) {
        if(e!=NULL)
            body->addElement(*e);
    }
}



