#-------------------------------------------------
#
# Project created by QtCreator 2024-10-14T20:09:20
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalendarCountdownApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    login.cpp \
        mainwindow.cpp \
    event.cpp \
    eventdialog.cpp \
    notifier.cpp \
    countdownwindow.cpp \
    showevents.cpp \
    sqlitestorage.cpp \
    weatherfetcher.cpp \
    weekcalendar.cpp \
    yearcalendar.cpp

HEADERS  += mainwindow.h \
    event.h \
    eventdialog.h \
    login.h \
    notifier.h \
    countdownwindow.h \
    showevents.h \
    sqlitestorage.h \
    weatherfetcher.h \
    weekcalendar.h \
    yearcalendar.h

FORMS    += mainwindow.ui \
    eventdialog.ui \
    countdownwindow.ui \
    login.ui \
    showevents.ui \
    weekcalendar.ui \
    yearcalendar.ui

DISTFILES += \
    EventdialogForm.ui.qml \
    Eventdialog.qml

RESOURCES += \
    resource.qrc
