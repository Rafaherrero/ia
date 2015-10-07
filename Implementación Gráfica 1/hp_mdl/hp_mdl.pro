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
    mapa.cpp \
    harry_potter.cpp \
    exceptions.cpp

HEADERS  += ventanaprincipal.h \
    mapa.h \
    harry_potter.h \
    common.h \
    exceptions.h

FORMS    += ventanaprincipal.ui

CONFIG += c++11
