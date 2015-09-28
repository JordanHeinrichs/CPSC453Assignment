TEMPLATE = app
QT+=widgets testlib

HEADERS += TestGameTickerService.h Mock*.h
SOURCES += main.cpp TestGameTickerService.cpp Mock*.cpp

QMAKE_CXXFLAGS += -Werror

LIBS += -L$$(BUILD_DIR)/.lib -Lgtest/lib -lview -lbusinessLogic -linfrastructure -lgmock -lgtest

POST_TARGETDEPS += \
    $$(BUILD_DIR)/.lib/libbusinessLogic.a
    $$(BUILD_DIR)/.lib/libview.a
    $$(BUILD_DIR)/.lib/infrastructure.a
INCLUDEPATH += .. gtest/include

CONFIG += testcase

DESTDIR = $$(BUILD_DIR)/.tests
OBJECTS_DIR = $$(BUILD_DIR)/.tests/.obj
MOC_DIR = $$(BUILD_DIR)/.tests/.moc
RCC_DIR = $$(BUILD_DIR)/.tests/.rcc
UI_DIR = $$(BUILD_DIR)/.tests/.ui
