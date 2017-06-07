#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T11:04:58
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += core gui network
QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    chat.cpp

HEADERS  += client.h \
    connection.h \
    chat.h

FORMS    += client.ui \
    chat.ui
