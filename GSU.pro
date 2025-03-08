QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    $$PWD\dvcs-ui\sources\mainwindow.cpp \
    $$PWD\repository-keeper\sources\repository.cpp \
    $$PWD\repository-keeper\sources\repositorykeeper.cpp \
    $$PWD\repository-keeper\sources\repositorymanager.cpp

HEADERS += \
    $$PWD\dvcs-ui\headers\mainwindow.h \
    $$PWD\repository-keeper\headers\repository.h \
    $$PWD\repository-keeper\headers\repositorykeeper.h \
    $$PWD\repository-keeper\headers\repositorymanager.h

FORMS += \
    $$PWD\dvcs-ui\forms\mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
