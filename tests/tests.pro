TEMPLATE = app
TARGET = test_utils
CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../UTILS
INCLUDEPATH += $$PWD/../include/xdelta3/xdelta3

DEFINES += SIZEOF_SIZE_T=8 SIZEOF_UNSIGNED_LONG_LONG=8 _WIN32_WINNT=0x0601

SOURCES += test_utils.cpp

LIBS += -L$$PWD/../UTILS -lUtils
