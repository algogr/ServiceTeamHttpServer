QT -= gui
QT += sql network

CONFIG += c++11 console network

CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(../libs/QtWebApp/QtWebApp/httpserver/httpserver.pri)

SOURCES += main.cpp \
    listdatacontroller.cpp \
    requestmapper.cpp \
    datacollection.cpp \
    confirm.cpp \
    originatorlist.cpp \
    breakdownlist.cpp \
    timer.cpp \
    doclist.cpp \
    docsconfirm.cpp


OTHER_FILES += settings.ini

HEADERS += \
    listdatacontroller.h \
    requestmapper.h \
    datacollection.h \
    confirm.h \
    originatorlist.h \
    breakdownlist.h \
    timer.h \
    doclist.h \
    docsconfirm.h

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS =
}

DISTFILES += \
    sthsmodel.qmodel
