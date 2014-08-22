#-------------------------------------------------
#
# Project created by QtCreator 2014-08-20T21:57:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoOrga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    campos.cpp \
    header.cpp \
    dialog_nuevoarchivo.cpp \
    dialog_abrirarchivos.cpp \
    dialog_nuevoregistro.cpp

HEADERS  += mainwindow.h \
    campos.h \
    header.h \
    dialog_nuevoarchivo.h \
    dialog_abrirarchivos.h \
    dialog_nuevoregistro.h

FORMS    += mainwindow.ui \
    dialog_nuevoarchivo.ui \
    dialog_abrirarchivos.ui \
    dialog_nuevoregistro.ui
