#ifndef DOMPANEL_H
#define DOMPANEL_H

#include <QWidget>
#include <QDockWidget>

class DOMPanel : public QWidget
{
    Q_OBJECT
public:
    DOMPanel();

    QDockWidget* getDock();

private:
    void createDockDOM();
    QDockWidget* dockDOM;

};

#endif // DOMPANEL_H
