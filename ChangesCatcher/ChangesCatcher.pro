TEMPLATE = lib
CONFIG += staticlib
TARGET = ChangesCatcher

QT += core
CONFIG += c++17

INCLUDEPATH += $$PWD/../UTILS

HEADERS += \
    changecatcher.h \

SOURCES += \
    changecatcher.cpp \
