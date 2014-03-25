#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T19:33:22
#
#-------------------------------------------------

QT       += core network serialport

QT       -= gui

TARGET = GClient
CONFIG   += console

QMAKE_CXXFLAGS += -std=gnu++11

CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mgrow.cpp

HEADERS += \
    mgrow.h

LIBS += -L$$PWD/../../libGSocket/bin/ -lGSocket

INCLUDEPATH += $$PWD/../../libGSocket/src
DEPENDPATH += $$PWD/../../libGSocket/src
