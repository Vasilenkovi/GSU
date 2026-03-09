TEMPLATE = subdirs
CONFIG += ordered

# Список модулей (подпроектов)
SUBDIRS = \
    UTILS \
    ChangesCatcher \
    RepositoryManager \
    DistNet \
    DistNetBeacon \
    SyncHead \
    UI \
    tests

SOURCES = main.cpp

UTILS.depends =
ChangesCatcher.depends = UTILS
RepositoryManager.depends = UTILS
DistNet.depends = UTILS
DistNetBeacon.depends = UTILS DistNet
SyncHead.depends = UTILS RepositoryManager DistNet ChangesCatcher
UI.depends = UTILS ChangesCatcher RepositoryManager DistNet DistNetBeacon SyncHead
