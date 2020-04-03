

TEMPLATE = subdirs

SUBDIRS += tl_lib
SUBDIRS += tl_tests

tl_tests.depends = tl_lib

message(project dir: $${PWD})

