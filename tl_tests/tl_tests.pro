
include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

TEMPLATE = app
CONFIG += depend_includepath c++17 console
CONFIG -= qt app_bundle

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -ltl_lib

INCLUDEPATH += source
INCLUDEPATH += ../tl_lib/source

CONFIG -= app_bundle

SOURCES += \
        source/main.cpp

HEADERS += \
    source/tl_test.h \
    source/tl_testers.h
