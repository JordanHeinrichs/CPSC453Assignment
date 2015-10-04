TEMPLATE = app
QT+=widgets testlib

HEADERS += Test*.h Mock*.h
SOURCES += main.cpp Test*.cpp Mock*.cpp

QMAKE_CXXFLAGS += -Werror

LIBS += -L$$(BUILD_DIR)/.lib -Lgtest/lib -lview -lbusinessLogic -linfrastructure -lgmock -lgtest

POST_TARGETDEPS += \
    $$(BUILD_DIR)/.lib/libbusinessLogic.a
    $$(BUILD_DIR)/.lib/libview.a
    $$(BUILD_DIR)/.lib/infrastructure.a
INCLUDEPATH += .. gtest/include

CONFIG += testcase c++11

DESTDIR = $$(BUILD_DIR)/.tests
OBJECTS_DIR = $$(BUILD_DIR)/.tests/.obj
MOC_DIR = $$(BUILD_DIR)/.tests/.moc
RCC_DIR = $$(BUILD_DIR)/.tests/.rcc
UI_DIR = $$(BUILD_DIR)/.tests/.ui

target.path = $$(BUILD_DIR)/.tests/testsDir
INSTALLS += target
