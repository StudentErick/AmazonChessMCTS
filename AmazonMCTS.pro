TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    uct.cpp \
    movegenerator.cpp \
    treenode.cpp \
    gamestate.cpp

HEADERS += \
    utils.h \
    uct.h \
    movegenerator.h \
    treenode.h \
    gamestate.h
