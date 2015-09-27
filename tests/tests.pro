TEMPLATE = app
QT+=widgets testlib

HEADERS += *.h
SOURCES += *.cpp

QMAKE_CXXFLAGS += -Werror

# CONFIG = testcase

LIBS += -L$$(BUILD_DIR)/.lib -Lgtest/lib -lview -lbusinessLogic -lgmock -lgtest
INCLUDEPATH += .. gtest/include

DESTDIR = $$(BUILD_DIR)/.tests
OBJECTS_DIR = $$(BUILD_DIR)/.tests/.obj
MOC_DIR = $$(BUILD_DIR)/.tests/.moc
RCC_DIR = $$(BUILD_DIR)/.tests/.rcc
UI_DIR = $$(BUILD_DIR)/.tests/.ui
