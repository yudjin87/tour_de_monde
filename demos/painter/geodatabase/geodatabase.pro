include(../shared.pri)

QT       += script sql

TEMPLATE = lib

TARGET = org.carousel.demos.Geodatabase

DEFINES += GEODATABASE_LIB_IMPORT

DESTDIR = $${DESTDIR}/externalSource

LIBS += -L$${CAROUSEL_BIN} -lCarousel \
                           -lorg.carousel.JsScripting \

LIBS += -L$${DESTDIR} -lorg.carousel.demos.Geometry \

HEADERS += \
    geodatabase_api.h \
    Feature.h \
    FeatureClass.h \
    IWorkspaceFactory.h \
    ShapeFileWorkspaceFactory.h \
    IWorkspace.h \
    IFeatureWorkspace.h \
    ShapeFileFeatureWorkspace.h \
    IDataset.h \
    IGeoDataset.h \
    IFeatureDataset.h \
    ShapeFileFeatureDataset.h \
    IShapeFileReader.h \
    ShapeFileReader.h \
    ShapeType.h \
    IFeatureClass.h \
    IFeature.h \
    IRecord.h \
    GeodatabaseComponent.h \
    IShapeFileWorkspaceFactory.h \
    ISpatialFilter.h \
    SpatialFilter.h \
    GDBScriptExtension.h \
    GeometryFactory.h \
    BinaryReader.h

SOURCES += \
    Feature.cpp \
    FeatureClass.cpp \
    ShapeFileWorkspaceFactory.cpp \
    ShapeFileFeatureWorkspace.cpp \
    ShapeFileFeatureDataset.cpp \
    ShapeFileReader.cpp \
    GeodatabaseComponent.cpp \
    SpatialFilter.cpp \
    GDBScriptExtension.cpp \
    GeometryFactory.cpp \
    BinaryReader.cpp

OTHER_FILES += org.carousel.demos.Geodatabase.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
