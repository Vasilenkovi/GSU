TEMPLATE = app
TARGET = test_utils
CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../UTILS
INCLUDEPATH += $$PWD/../include/HDiffPatch/libHDiffPatch

SOURCES += test_utils.cpp

LIBS += -L$$PWD/../UTILS/release -lUtils
