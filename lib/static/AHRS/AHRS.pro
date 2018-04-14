#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T09:02:10
#
#-------------------------------------------------

QT       += gui

TARGET = AHRS
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += ahrs.cpp \
    stm32.cpp \
    floataverage.cpp \
    kalmanfilter.cpp \
    madgwickfilter.cpp

HEADERS += ahrs.h \
    factoraccmag.h \
    stm32.h \
    floataverage.h \
    kalmanfilter.h \
    madgwickfilter.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TrackerPacket/release/ -lTrackerPacket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TrackerPacket/debug/ -lTrackerPacket
else:unix: LIBS += -L$$OUT_PWD/../TrackerPacket/ -lTrackerPacket

INCLUDEPATH += $$PWD/../TrackerPacket
DEPENDPATH += $$PWD/../TrackerPacket

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TrackerPacket/release/libTrackerPacket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TrackerPacket/debug/libTrackerPacket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TrackerPacket/release/TrackerPacket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../TrackerPacket/debug/TrackerPacket.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../TrackerPacket/libTrackerPacket.a
