#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T01:57:09
#
#-------------------------------------------------

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
                                        webenginewidgets

TARGET = WebCreator
TEMPLATE = app


SOURCES += \
        metier/src/IdHandler.cpp\
        metier/src/Element.cpp  \
        metier/src/PageWeb.cpp  \
        metier/src/jsoncpp.cpp  \
        metier/src/Module.cpp   \
        metier/src/Html.cpp \
        metier/src/Head.cpp \
        metier/src/Body.cpp \
        metier/src/Site.cpp \
        elementPanel.cpp\
        moduleItem.cpp  \
        mainwindow.cpp  \
        pagescene.cpp   \
        textitem.cpp    \
        main.cpp

HEADERS  += \
        metier/include/IdHandler.h\
        metier/include/Element.h  \
        metier/include/PageWeb.h  \
        metier/include/Module.h   \
        metier/include/Html.h \
        metier/include/Head.h \
        metier/include/Body.h \
        metier/include/Site.h \
        elementPanel.h \
        moduleItem.h   \
        mainwindow.h   \
        pagescene.h    \
        textitem.h



RESOURCES += \
        images/images.qrc
