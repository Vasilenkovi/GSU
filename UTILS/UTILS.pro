TEMPLATE = lib
CONFIG += staticlib
TARGET = Utils

QT += core
CONFIG += c++17


HEADERS += \
    Message.h \
    difffinder.h \
    versionschain.h \
    Commit.h \
    dirUtils.h

SOURCES += \
    Commit.cpp \
    difffinder.cpp \
    versionschain.cpp \
    dirUtils.cpp

# HDiffPatch library sources
INCLUDEPATH += \
    $$PWD/../include/HDiffPatch \
    $$PWD/../include/HDiffPatch/libHDiffPatch \
    $$PWD/../include/HDiffPatch/libParallel

# libHDiffPatch sources
SOURCES += \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/diff.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/match_block.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/bytes_rle.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/compress_detect.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort64.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/limit_mem_diff/adler_roll.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/limit_mem_diff/digest_matcher.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/limit_mem_diff/stream_serialize.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/match_inplace.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HDiff/private_diff/suffix_string.cpp \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/patch.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/hpatch_mt/hpatch_mt.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/hpatch_mt/_hcache_old_mt.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/hpatch_mt/_hinput_mt.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/hpatch_mt/_houtput_mt.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatch/hpatch_mt/_hpatch_mt.c \
    $$PWD/../include/HDiffPatch/libHDiffPatch/HPatchLite/hpatch_lite.c \
    $$PWD/../include/HDiffPatch/libParallel/parallel_channel.cpp \
    $$PWD/../include/HDiffPatch/libParallel/parallel_import_c.c
