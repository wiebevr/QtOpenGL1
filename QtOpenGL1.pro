######################################################################
# Automatically generated by qmake (2.01a) za okt. 30 14:23:11 2010
######################################################################

TEMPLATE = app
TARGET = QtOpenGL1 
DEPENDPATH += .
INCLUDEPATH += .\
               /usr/include/assimp \
               /usr/include
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

QT += opengl core gui

# Input
HEADERS += cube.h \ 
           widget.h \
           object.h \
           mesh.h \
           camera.h

SOURCES += main.cpp \
           widget.cpp \
           object.cpp \
           cube.cpp \
           mesh.h \
           camera.cpp

RESOURCES += \
    resources.qrc