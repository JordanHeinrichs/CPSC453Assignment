TEMPLATE = app
QT+=widgets testlib

HEADERS += TestGameTickerService.h Mock*.h
SOURCES += main.cpp TestGameTickerService.cpp Mock*.cpp

QMAKE_CXXFLAGS += -Werror

LIBS += -L$$(BUILD_DIR)/.lib -Lgtest/lib -lview -lbusinessLogic -lgmock -lgtest
INCLUDEPATH += .. gtest/include

CONFIG += testcase release

DESTDIR = $$(BUILD_DIR)/.tests
OBJECTS_DIR = $$(BUILD_DIR)/.tests/.obj
MOC_DIR = $$(BUILD_DIR)/.tests/.moc
RCC_DIR = $$(BUILD_DIR)/.tests/.rcc
UI_DIR = $$(BUILD_DIR)/.tests/.ui
