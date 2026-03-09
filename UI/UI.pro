TEMPLATE = app
TARGET = GSU

QT += core widgets
CONFIG += c++17

# Подключаем заголовки всех модулей
INCLUDEPATH += \
    $$PWD/../UTILS \
    $$PWD/../ChangesCatcher \
    $$PWD/../RepositoryManager \
    $$PWD/../DistNet \
    $$PWD/../DistNetBeacon \
    $$PWD/../SyncHead

# Формы
FORMS += mainwindow.ui

# Исходники UI и главный main.cpp (лежит в корне проекта)
SOURCES += \
    mainwindow.cpp \
    $$PWD/../main.cpp

HEADERS += \
    mainwindow.h

# Линковка со статическими библиотеками модулей
LIBS += \
    -L$$OUT_PWD/../UTILS -lUtils \
    -L$$OUT_PWD/../ChangesCatcher -lChangesCatcher \
    -L$$OUT_PWD/../RepositoryManager -lRepositoryManager \
    -L$$OUT_PWD/../DistNet -lDistNet \
    -L$$OUT_PWD/../DistNetBeacon -lDistNetBeacon \
    -L$$OUT_PWD/../SyncHead -lSyncHead