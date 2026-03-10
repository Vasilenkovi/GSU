TEMPLATE = lib
CONFIG += staticlib
TARGET = Utils

QT += core
CONFIG += c++17

DEFINES += SIZEOF_SIZE_T=8 SIZEOF_UNSIGNED_LONG_LONG=8 _WIN32_WINNT=0x0601

linux: DEFINES += _LARGEFILE64_SOURCE _FILE_OFFSET_BITS=64

INCLUDEPATH += $$PWD/../include/xdelta3/xdelta3

!exists($$PWD/../include/xdelta3/xdelta3/xdelta3.c) {
    error("xdelta3.c not found at $$PWD/../include/xdelta3/xdelta3/xdelta3.c")
}

HEADERS += \
    Message.h \
    difffinder.h \
    versionschain.h \
    Commit.h

SOURCES += \
    Commit.cpp \
    difffinder.cpp \
    versionschain.cpp \
    $$PWD/../include/xdelta3/xdelta3/xdelta3.c
