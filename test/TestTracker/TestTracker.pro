#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T22:09:52
#
#-------------------------------------------------

QT       += core gui serialport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestTracker
TEMPLATE = app

CONFIG +=c++11

DESTDIR =../../bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h

FORMS += \
        MainWindow.ui
### DATA PROVIDER
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/DataProvider/release/ -lDataProvider
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/DataProvider/debug/ -lDataProvider
else:unix:!macx: LIBS += -L$$OUT_PWD/../../lib/static/DataProvider/ -lDataProvider

INCLUDEPATH += $$PWD/../../lib/static/DataProvider
DEPENDPATH += $$PWD/../../lib/static/DataProvider

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/DataProvider/release/libDataProvider.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/DataProvider/debug/libDataProvider.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/DataProvider/release/DataProvider.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/DataProvider/debug/DataProvider.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/DataProvider/libDataProvider.a
### CONVERTER
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/Converter/release/ -lConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/Converter/debug/ -lConverter
else:unix:!macx: LIBS += -L$$OUT_PWD/../../lib/static/Converter/ -lConverter

INCLUDEPATH += $$PWD/../../lib/static/Converter
DEPENDPATH += $$PWD/../../lib/static/Converter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Converter/release/libConverter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Converter/debug/libConverter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Converter/release/Converter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Converter/debug/Converter.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/Converter/libConverter.a
###

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/TrackerPacket/release/ -lTrackerPacket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/TrackerPacket/debug/ -lTrackerPacket
else:unix:!macx: LIBS += -L$$OUT_PWD/../../lib/static/TrackerPacket/ -lTrackerPacket

INCLUDEPATH += $$PWD/../../lib/static/TrackerPacket
DEPENDPATH += $$PWD/../../lib/static/TrackerPacket

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/TrackerPacket/release/libTrackerPacket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/TrackerPacket/debug/libTrackerPacket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/TrackerPacket/release/TrackerPacket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/TrackerPacket/debug/TrackerPacket.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/TrackerPacket/libTrackerPacket.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/AHRS/release/ -lAHRS
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/AHRS/debug/ -lAHRS
else:unix:!macx: LIBS += -L$$OUT_PWD/../../lib/static/AHRS/ -lAHRS

INCLUDEPATH += $$PWD/../../lib/static/AHRS
DEPENDPATH += $$PWD/../../lib/static/AHRS

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/AHRS/release/libAHRS.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/AHRS/debug/libAHRS.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/AHRS/release/AHRS.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/AHRS/debug/AHRS.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/AHRS/libAHRS.a
