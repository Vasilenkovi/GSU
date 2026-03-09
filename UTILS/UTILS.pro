TEMPLATE = lib
CONFIG += staticlib
TARGET = Utils

QT += core
CONFIG += c++17

HEADERS += \
    Message.h \
    difffinder.h \
    versionschain.h \
    Commit.h

SOURCES += \
    Commit.cpp \
    difffinder.cpp \
    versionschain.cpp

LIBS += -lxdelta3
