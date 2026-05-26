QT += widgets

CONFIG += c++11 utf8_source

TARGET = GymOfflineQt
TEMPLATE = app

msvc: QMAKE_CXXFLAGS += /utf-8

SOURCES += \
    main.cpp \
    datastore.cpp \
    mainwindow.cpp

HEADERS += \
    datastore.h \
    mainwindow.h

DISTFILES +=
