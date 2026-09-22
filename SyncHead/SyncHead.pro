TEMPLATE = lib
CONFIG += staticlib
TARGET = SyncHead

QT += core
CONFIG += c++17

# Заголовки используемых модулей
INCLUDEPATH += \
    $$PWD/../UTILS \
    $$PWD/../RepositoryManager \
    $$PWD/../DistNet \
    $$PWD/../ChangesCatcher

# HEADERS += 
# SOURCES += 