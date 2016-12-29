TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    datamanager.cpp \
    dataserver.cpp \
    activity.cpp \
    jsonparser.cpp \
    activityparser.cpp

HEADERS += \
    datamanager.h \
    dataserver.h \
    activity.h \
    jsonparser.h \
    activityparser.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
