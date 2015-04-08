include(../shared.pri)

QT       += widgets
QT       += script

TEMPLATE = lib

TARGET = org.carousel.demos.Carto

DEFINES += CARTO_LIB_IMPORT

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.JsScripting \
                           -lorg.carousel.Interactivity \

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Display \
                      -lorg.carousel.demos.Geodatabase \
                      -lorg.carousel.demos.Geometry


HEADERS += \
    carto_api.h \
    PainterDocument.h \
    PainterDocumentController.h \
    IPainterDocumentController.h \
    IPainterDocument.h \
    AbstractLayer.h \
    FeatureLayer.h \
    Map.h \
    CartoComponent.h \
    IMap.h \
    ILayerVisitor.h \
    CartoScriptExtension.h \
    FeatureLayerDrawingTask.h \
    DefaultNavigationHandler.h \
    commands/AddShapesCommand.h \
    commands/RenameLayerCommand.h \
    commands/ChangeLayerSymbolCommand.h \
    commands/MoveLayerCommand.h \
    commands/RemoveLayerCommand.h

SOURCES += \
    AbstractLayer.cpp \
    FeatureLayer.cpp \
    Map.cpp \
    CartoComponent.cpp \
    PainterDocumentController.cpp \
    PainterDocument.cpp \
    CartoScriptExtension.cpp \
    FeatureLayerDrawingTask.cpp \
    DefaultNavigationHandler.cpp \
    commands/AddShapesCommand.cpp \
    commands/RenameLayerCommand.cpp \
    commands/ChangeLayerSymbolCommand.cpp \
    commands/MoveLayerCommand.cpp \
    commands/RemoveLayerCommand.cpp

OTHER_FILES += org.carousel.demos.Carto.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
