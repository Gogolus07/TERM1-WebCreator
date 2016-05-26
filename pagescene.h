#ifndef PAGESCENE_H
#define PAGESCENE_H

#include "textitem.h"
#include "metier/include/PageWeb.h"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

//! [0]
class PageScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    enum DiagramType { Step, Conditional, StartEnd, Io };

    explicit PageScene   (PageWeb &pageWeb, QMenu *itemMenu, QObject *parent = 0);
    QFont   font         () const { return m_Font; }
    QColor  textColor    () const { return m_TextColor; }
    void    setTextColor (const QColor &color);
    void    setFont      (const QFont &font);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramType type);
    void editorLostFocus(TextItem *item);

signals:
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    bool isItemChange(int type);

    DiagramType m_ItemType;
    QMenu *m_ItemMenu;
    Mode m_Mode;
    bool leftButtonDown;
    QFont m_Font;
    TextItem *m_textItem;
    QColor m_TextColor;

    PageWeb m_pageweb;
    Html* html;
    Body* body;
    QVector<Element*> elts;
    void integrationElementToBody();

};
//! [0]




#endif // PAGESCENE_H
