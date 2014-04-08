
SOURCES += \
    main.cpp \
    OurWindow.cpp \
    Server.cpp

RESOURCES     = application.qrc


QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    OurWindow.h \
    QWsServer.h \
    QWsSocket.h \
    Server.h \
    QTlsServer.h







OTHER_FILES += \
    vocanod.rc

RC_FILE = vocanod.rc

win32: LIBS += -L$$PWD/QtWebsockets/ -lQtWebsocket

INCLUDEPATH += $$PWD/QtWebsockets
DEPENDPATH += $$PWD/QtWebsockets
