TEMPLATE = app
TARGET = assignment1
QT+=widgets

HEADERS += *.h
SOURCES += *.cpp

QMAKE_CXXFLAGS += -Werror

LIBS += -L$$(BUILD_DIR)/.lib -lview -lbusinessLogic -linfrastructure
POST_TARGETDEPS += \
    $$(BUILD_DIR)/.lib/libbusinessLogic.a
    $$(BUILD_DIR)/.lib/libview.a
    $$(BUILD_DIR)/.lib/infrastructure.a
INCLUDEPATH += ..

DESTDIR = $$(BUILD_DIR)/
OBJECTS_DIR = $$(BUILD_DIR)/.obj
MOC_DIR = $$(BUILD_DIR)/.moc
RCC_DIR = $$(BUILD_DIR)/.rcc
UI_DIR = $$(BUILD_DIR)/.ui
