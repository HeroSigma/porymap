TEMPLATE = app
TARGET = test_am95_importer
QT += testlib core gui widgets
CONFIG += console c++17
SOURCES += unit/main.cpp \
           ../src/importers/Am95Importer.cpp \
           ../src/importers/Am95MapParser.cpp
INCLUDEPATH += ../src ../include ../include/core ../include/lib ../include/ui
CONFIG -= app_bundle
mac: CONFIG -= app_bundle
unix:!mac: CONFIG += testcase
