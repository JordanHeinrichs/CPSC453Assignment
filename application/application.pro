TEMPLATE = app
TARGET = assignment1
QT+=widgets

HEADERS += *.h
SOURCES += *.cpp

LIBS += -L$$(BUILD_DIR)/.lib -lview -lbusinessLogic
INCLUDEPATH += . ..

DESTDIR = $$(BUILD_DIR)/.
OBJECTS_DIR = $$(BUILD_DIR)/.obj
MOC_DIR = $$(BUILD_DIR)/.moc
RCC_DIR = $$(BUILD_DIR)/.rcc
UI_DIR = $$(BUILD_DIR)/.ui
