TEMPLATE = subdirs
config += ordered

SUBDIRS  = \
    infrastructure \
    businessLogic \
    view \
    external \
    tests \
    application

tests.depends += businessLogic view infrastructure
application.depends += tests
