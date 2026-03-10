TEMPLATE = lib
CONFIG += staticlib
TARGET = Utils

QT += core
CONFIG += c++17

# Путь к заголовкам xdelta3
INCLUDEPATH += $$PWD/../third_party/xdelta3

HEADERS += \
    Message.h \
    difffinder.h \
    versionschain.h \
    Commit.h

SOURCES += \
    Commit.cpp \
    difffinder.cpp \
    versionschain.cpp \
    $$PWD/../third_party/xdelta3/xdelta3.c
