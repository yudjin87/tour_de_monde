TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystemui_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/ComponentsDialogTest.cpp \
    $$TEST_PROJECT_SOURCES/main_componentsystem_ui_test.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeEnableComponentCommand.cpp

HEADERS += \
    $$TEST_PROJECT_SOURCES/ComponentsDialogTest.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeEnableComponentCommand.h

