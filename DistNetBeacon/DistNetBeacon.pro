TEMPLATE = lib
CONFIG += staticlib
TARGET = DistNetBeacon

QT += core network
CONFIG += c++17

# Возможно, потребуются заголовки DistNet
INCLUDEPATH += $$PWD/../DistNet

# HEADERS += 
# SOURCES += 