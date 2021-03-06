# -------------------------------------------------
# Project created by QtCreator 2010-11-09T16:46:39
# -------------------------------------------------
QT += network \
    svg \
    xml
TARGET = nagtray
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    configwindow.cpp \
    editconnection.cpp \
    connection.cpp \
    host.cpp \
    service.cpp \
    labeldelegate.cpp
HEADERS += mainwindow.h \
    configwindow.h \
    editconnection.h \
    connection.h \
    globalconfig.h \
    host.h \
    hostgroup.h \
    service.h \
    servicegroup.h \
    labeldelegate.h
FORMS += mainwindow.ui \
    configwindow.ui \
    editconnection.ui
OTHER_FILES += README
RESOURCES += nagtray.qrc
