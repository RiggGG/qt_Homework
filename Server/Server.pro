#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T09:54:59
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network
QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp

HEADERS  += server.h

FORMS    += server.ui
