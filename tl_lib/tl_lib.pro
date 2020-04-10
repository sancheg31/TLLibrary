
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
    experimental/NullType.h \
    experimental/TypeList.h \
    experimental/TypeListTraits.h \
    experimental/TypeTraits.h \
    experimental/literals.h \
    source/tl_node.h \
    source/tl_nulltype.h \
    source/tl_traits.h \
    source/tl_utilities.h \
    source/type_list.h

message(tl-lib project dir: $${PWD})
message(tl-lib output dir: $${DESTDIR})
