TEMPLATE = subdirs

SUBDIRS  = \
    businessLogic \
    view \
    external \
    tests \
    application

tests.depends += businessLogic view
application.depends += tests businessLogic view
