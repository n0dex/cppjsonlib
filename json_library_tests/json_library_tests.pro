QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_json_library_tests.cpp \
    ../json_library_source/json_document.cpp \
    ../json_library_source/json_parser.cpp \
    ../json_library_source/json_variant.cpp

HEADERS += \
    ../json_library_source/json_defines.h \
    ../json_library_source/json_document.h \
    ../json_library_source/json_library.h \
    ../json_library_source/json_parser.h \
    ../json_library_source/json_variant.h
