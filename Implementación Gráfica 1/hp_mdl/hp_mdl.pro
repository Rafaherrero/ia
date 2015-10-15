#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T23:42:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hp_mdl
TEMPLATE = app


SOURCES += main.cpp\
        ventanaprincipal.cpp \
    harry_potter.cpp \
    exceptions.cpp \
    tabla_t.cpp \
    aleatorio.cpp \
    mapa_t.cpp

HEADERS  += ventanaprincipal.h \
    harry_potter.h \
    common.h \
    exceptions.h \
    tabla_t.h \
    aleatorio.h \
    mapa_t.h

FORMS    += ventanaprincipal.ui

CONFIG += c++11
