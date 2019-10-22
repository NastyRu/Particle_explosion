#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T07:57:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += sdk_no_version_check

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    base_builder.cpp \
    base_draw.cpp \
    camera.cpp \
    commands.cpp \
    draw.cpp \
    exceptions.cpp \
    facade.cpp \
    file_loader.cpp \
    file_save.cpp \
    iterators.cpp \
    managers.cpp \
    matrix.cpp \
    model.cpp \
    model_builder.cpp \
    objects.cpp \
    positions.cpp \
    scene_container.cpp \
    points.cpp \
    particles.cpp

HEADERS += \
        mainwindow.h \
    base_builder.h \
    base_draw.h \
    commands.h \
    draw.h \
    draw.h \
    exceptions.h \
    facade.h \
    file_loader.h \
    file_save.h \
    iterators.h \
    managers.h \
    matrix.h \
    model.h \
    model_builder.h \
    objects.h \
    positions.h \
    scene_container.h \
    points.h \
    particles.h \
    camera.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
