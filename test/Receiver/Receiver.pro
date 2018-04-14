QT += serialport xml

HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                logo.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp

QT           += widgets

TARGET = Receiver
# install
DESTDIR = ../../bin

INSTALLS += target

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
