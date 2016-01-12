TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core

QMAKE_CFLAGS_RELEASE += -O2

SOURCES += main.cpp \
    AStar.cpp \
    Space3d.cpp \
    Node.cpp \
    Path.cpp \
    OrderedHash.cpp \
    AStarQuick.cpp

HEADERS += \
    AStar.h \
    Space3d.h \
    Node.h \
    Path.h \
    OrderedHash.h \
    AStarQuick.h

