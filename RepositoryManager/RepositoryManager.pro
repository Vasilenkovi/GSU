TEMPLATE = lib
CONFIG += staticlib
TARGET = RepositoryManager

QT += core
CONFIG += c++17

# Подключаем заголовки используемых модулей
INCLUDEPATH += $$PWD/../UTILS $$PWD/../ChangesCatcher

HEADERS += \
    Branch.h \
    DVCSManager.h \
    repositorykeeper.h \

SOURCES += \
    Branch.cpp \
    DVCSManager.cpp \
    repositorykeeper.cpp
