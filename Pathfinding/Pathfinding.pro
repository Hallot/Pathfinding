TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    AStar.cpp \
    Space3d.cpp \
    Node.cpp \
    Path.cpp \
    OrderedHash.cpp \
    AStarQuick.cpp \
    SMAStar.cpp \
    Utils.cpp

HEADERS += \
    AStar.h \
    Space3d.h \
    Node.h \
    Path.h \
    OrderedHash.h \
    AStarQuick.h \
    SMAStar.h \
    Utils.h

