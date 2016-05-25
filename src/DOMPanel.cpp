#include "DOMPanel.h"
#include <QTreeWidget>

DOMPanel::DOMPanel()
{
    createDockDOM();
}

QDockWidget* DOMPanel::getDock()
{
    return dockDOM;
}

void DOMPanel::createDockDOM()
{
    dockDOM = new QDockWidget(tr("DOM"), this);

    QStringList html;    html    << tr("html")    << tr("");
    QStringList head;    head    << tr("head")    << tr("");
    QStringList meta1;   meta1   << tr("meta")    << tr("http-equiv\"Content-Type\" content=\"text/html; charset=utf-8\"");
    QStringList script1; script1 << tr("script")  << tr("type=\"text/javascript\" src=\"/scripts/extras.js\"");
    QStringList body;    body    << tr("Body")    << tr("id=\"id_body\"");
    QStringList header;  header  << tr("header")  << tr("");
    QStringList footer;  footer  << tr("footer")  << tr("");
    QStringList section; section << tr("section") << tr("");

    QTreeWidget *t=new QTreeWidget(dockDOM);
    t->setColumnCount(2);

    QTreeWidgetItem *item_html = new QTreeWidgetItem(html);
    QTreeWidgetItem *item_head = new QTreeWidgetItem(head);
    QTreeWidgetItem *item_body = new QTreeWidgetItem(body);

    item_html->addChild(item_head);
    item_html->addChild(item_body);

    item_head->addChild(new QTreeWidgetItem(meta1));
    item_head->addChild(new QTreeWidgetItem(script1));
    item_body->addChild(new QTreeWidgetItem(header));
    item_body->addChild(new QTreeWidgetItem(section));
    item_body->addChild(new QTreeWidgetItem(footer));

    t->addTopLevelItem(item_html);

    dockDOM->setWidget(t);
}
