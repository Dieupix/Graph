TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../Graph/graph.cpp \
        ../Graph/noeud.cpp \
        graphTest.cpp \
        main.cpp

HEADERS += \
	../Graph/graph.h \
	../Graph/noeud.h \
	doctest.h
