
include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

TARGET = tl_lib
TEMPLATE = lib

CONFIG += staticlib c++17
CONFIG -= gui app_bundle

DEFINES += TYPE_LIST_LIBRARY

INCLUDEPATH += source

SOURCES +=

HEADERS += \
    experimental/TypeList.h \
    experimental/TypeListTraits.h \
    experimental/literals.h \
    source/tl_fwd.h \
    source/tl_utilities.h \
    source/type_list.h \
    source/type_list_impl.h

message(tl-lib project dir: $${PWD})
message(tl-lib output dir: $${DESTDIR})
