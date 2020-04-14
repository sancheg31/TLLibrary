
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
    experimental/ExpandingPack.h \
    experimental/FindOperations.h \
    experimental/literals.hpp \
    experimental/typeIndex.h \
    source/TLAlgorithm.hpp \
    source/TLAlgorithmfwd.hpp \
    source/TLIterator.hpp \
    source/TLIteratorfwd.hpp \
    source/TLNode.hpp \
    source/TLNullType.hpp \
    source/TLPredefinedHeaders.hpp \
    source/TLRequirements.hpp \
    source/TLTraits.hpp \
    source/TLUtility.hpp \
    source/TLfwd.hpp \
    source/type_list.hpp

message(tl-lib project dir: $${PWD})
message(tl-lib output dir: $${DESTDIR})
