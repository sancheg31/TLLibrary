
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
INCLUDEPATH += experimental

SOURCES +=

HEADERS += \
    experimental/NullType.h \
    experimental/TypeList.h \
    experimental/TypeListTraits.h \
    experimental/TypeTraits.h \
    experimental/literals.h \
    source/TLNode.h \
    source/TLNulltype.h \
    source/TLTraits.h \
    source/TLUtilities.h \
    source/type_list.h

message(tl-lib project dir: $${PWD})
message(tl-lib output dir: $${DESTDIR})
