TEMPLATE = lib
INCLUDEPATH += ..
QT+=widgets

CONFIG += staticlib c++11 debug

QMAKE_CXXFLAGS += -Werror

DESTDIR = $$(BUILD_DIR)/.lib
OBJECTS_DIR = $$(BUILD_DIR)/.obj
MOC_DIR = $$(BUILD_DIR)/.moc
RCC_DIR = $$(BUILD_DIR)/.rcc
UI_DIR = $$(BUILD_DIR)/.ui
