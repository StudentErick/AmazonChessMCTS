TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    uct.cpp \
    treenode.cpp

HEADERS += \
    utils.h \
    uct.h \
    treenode.h
