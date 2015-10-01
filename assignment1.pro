TEMPLATE = subdirs
config += ordered c++11

SUBDIRS  = \
    infrastructure \
    businessLogic \
    view \
    external \
    tests \
    application

tests.depends += businessLogic view infrastructure
application.depends += tests
