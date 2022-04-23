QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithms.cpp \
    application.cpp \
    exceptions.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    menudijkstra.cpp \
    menuordonnancement.cpp \
    menupruferdecode.cpp \
    menusaisie.cpp \
    noeud.cpp \
    test.cpp \
    vue.cpp \
    widgetedge.cpp \
    widgetgraph.cpp \
    widgetgraphbis.cpp \
    widgetnode.cpp

HEADERS += \
    algorithms.h \
    application.h \
    exceptions.h \
    graph.h \
    mainwindow.h \
    menudijkstra.h \
    menuordonnancement.h \
    menupruferdecode.h \
    menusaisie.h \
    noeud.h \
    test.h \
    vue.h \
    widgetedge.h \
    widgetgraph.h \
    widgetgraphbis.h \
    widgetnode.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
