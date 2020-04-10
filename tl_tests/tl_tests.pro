
include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

TEMPLATE = app

CONFIG += depend_includepath c++17 console
CONFIG += qt
CONFIG -= app_bundle

QT += testlib

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -ltl_lib

INCLUDEPATH += source
INCLUDEPATH += experimental
INCLUDEPATH += ../tl_lib

CONFIG -= app_bundle

SOURCES += \
        source/TLTestSuite.cpp \
        source/main.cpp

HEADERS += \
    experimental/TypeListTraitsTest.hpp \
    source/TLPredefinedTesters.hpp \
    source/TLTest.hpp \
    source/TLTestCase.hpp \
    source/TLTestSuite.hpp \
    source/TLTypeWrappers.hpp
