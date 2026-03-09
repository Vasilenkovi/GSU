TEMPLATE = app
TARGET = test_utils

CONFIG += c++17 console
CONFIG -= app_bundle

# Путь к библиотеке Utils и её заголовкам
INCLUDEPATH += $$PWD/../UTILS
LIBS += -L$$PWD/../UTILS -lUtils -lxdelta3

SOURCES += test_utils.cpp
