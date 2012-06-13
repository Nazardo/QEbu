#-------------------------------------------------
#
# Project created by QtCreator 2012-04-27T20:55:22
#
#-------------------------------------------------

include(model/model.pri)
include(fileproc/fileproc.pri)
include(ui/ui.pri)

QT       += core gui xml

TARGET = QEbu
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

OTHER_FILES += \
    images/watermark.png \
    images/page3.png \
    images/page2.png \
    images/page1.png \
    images/page0.png \
    images/banner.png \
    images/qebu-icon_256.png \
    images/qebu-icon_128.png \
    images/qebu-icon_64.png \
    images/qebu-icon_32.png \
    images/qebu-icon_16.png \
    icon.rc \
    icon.ico

RESOURCES += \
    qResources.qrc

RC_FILE = icon.rc
