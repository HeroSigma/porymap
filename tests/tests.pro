TEMPLATE = app
TARGET = test_am95_importer
QT += testlib core gui
CONFIG += console c++17
SOURCES += unit/test_am95_importer.cpp \
           ../src/importers/Am95Importer.cpp
INCLUDEPATH += ../src ../include
CONFIG -= app_bundle
mac: CONFIG -= app_bundle
unix:!mac: CONFIG += testcase
