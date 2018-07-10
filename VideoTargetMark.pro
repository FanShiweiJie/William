#-------------------------------------------------
#
# Project created by QtCreator 2018-07-09T14:07:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/build/bin

CONFIG += c++11

TARGET = VideoTargetMarkTool
TEMPLATE = app

DEFINES -= UNICODE

INCLUDEPATH += \
    opencv3/include \
    driver/inc \
    qtermwidget

SOURCES += main.cpp\
    displaywidget.cpp \
    ui_utils.cpp \
    widgetvideotargetmark.cpp \
    videoinput.cpp \
    targetmark.cpp \

HEADERS  += displaywidget.h \
    ui_utils.h \
    widgetvideotargetmark.h \
    videoinput.h \
    targetmark.h \
    version.h

FORMS    += videotargetmark.ui

LIBS += -L$$PWD/driver/lib -lmingwcyapi
LIBS += \
    -L$$PWD/opencv3/lib \
    -lopencv_core300.dll \
    -lopencv_imgproc300.dll \
    -lopencv_video300.dll \
    -lopencv_videoio300.dll \
    -lopencv_highgui300.dll \
    -lopencv_objdetect300.dll \
    -lws2_32 \
    -lvfw32 \
    -lsetupapi
LIBS += -lwsock32

# version.h
FOO = $$system($$PWD/gen_version.sh $$PWD/version.h)
