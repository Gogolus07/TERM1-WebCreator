#include "../include/image.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

/* Image: =================================================== */
Image::Image(ElementWidget *currentElementWidget, QWidget* parent):
    ElementWidget(currentElementWidget, parent),
    QImage(""){
    parent->setFixedSize(this->QImage::width(), this->QImage::height());
    //QLabel::adjustSize();
}

/* Image: =================================================== */
Image::Image(ElementWidget *currentElementWidget, std::string moduleName, QWidget* parent):
    ElementWidget(currentElementWidget, moduleName, parent),
    QImage(moduleName.c_str()){
    parent->setFixedSize(this->QImage::width(), this->QImage::height());
    //QLabel::adjustSize();
}

/* Image: =================================================== */
Image::Image(ElementWidget *currentElementWidget, std::string moduleName, std::string content, QWidget* parent):
    ElementWidget(currentElementWidget, moduleName, content, parent),
    QImage(content.c_str()){
    //QImage::setContentsMargins(2, 2, 0, 0);
   //QLabel::adjustSize();
}

