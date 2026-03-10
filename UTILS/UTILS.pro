TEMPLATE = lib
CONFIG += staticlib
TARGET = Utils

QT += core
CONFIG += c++17

# Определения для xdelta3 (под Windows 64-bit)
DEFINES += SIZEOF_SIZE_T=8 SIZEOF_UNSIGNED_LONG_LONG=8 _WIN32_WINNT=0x0601

# Путь к заголовкам xdelta3
INCLUDEPATH += $$PWD/../include/xdelta3/xdelta3

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
