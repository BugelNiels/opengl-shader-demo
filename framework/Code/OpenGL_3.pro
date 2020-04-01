QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_3
TEMPLATE = app

CONFIG += c++14

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mainview.cpp \
    user_input.cpp \
    model.cpp \
    mainview_updates.cpp \
    scene_initialisation.cpp

HEADERS += \
    mainwindow.h \
    mainview.h \
    model.h \
    mesh.h \
    mesh.h \
    scene.h \
    cubemap.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
