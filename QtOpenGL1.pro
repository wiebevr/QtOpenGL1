######################################################################
# Automatically generated by qmake (2.01a) za okt. 30 14:23:11 2010
######################################################################


TEMPLATE = app
TARGET = QtOpenGL1 
DEPENDPATH += .
INCLUDEPATH += .\
               /usr/include/assimp
LIBS += -lassimp -lm

OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

QT += opengl core gui

# Input
HEADERS += cube.h \ 
           widget.h \
           object.h \
           mesh.h \
           camera.h \
           widget_plane.h \
           display_plane.h \
           object_group.h

SOURCES += main.cpp \
           widget.cpp \
           object.cpp \
           cube.cpp \
           mesh.cpp \
           camera.cpp \
           widget_plane.cpp \
           display_plane.cpp \
           object_group.cpp

RESOURCES += \
    resources.qrc

target.path = /usr/bin
INSTALLS += target
