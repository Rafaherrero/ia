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
    mapa_t.cpp \
    exceptions.cpp \
    tabla_t.cpp \
    harryPotter.cpp \
    infolaberinto.cpp
    aleatorio.cpp 

HEADERS  += ventanaprincipal.h \
    mapa_t.h \
    common.h \
    exceptions.h \
    tabla_t.h \
    harryPotter.h \
    infolaberinto.h
    aleatorio.h 


FORMS    += ventanaprincipal.ui \
    infolaberinto.ui

CONFIG += c++11

DISTFILES +=
