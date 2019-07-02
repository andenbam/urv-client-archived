#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T13:13:28
#
#-------------------------------------------------

#QT       += core gui
#QT       += sql
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = urv-client
TEMPLATE = app

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
        mainwindow.cpp \
    logindialog.cpp \
    sqlworker.cpp \
    messagedropper.cpp \
    workerslistdialog.cpp \
    workerform.cpp \
    workereditdialog.cpp \
    scheduledialog.cpp \
    dayadapter.cpp

HEADERS += \
        mainwindow.h \
    logindialog.h \
    sqlworker.h \
    messagedropper.h \
    workerslistdialog.h \
    workerform.h \
    workereditdialog.h \
    scheduledialog.h \
    dayadapter.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    workerslistdialog.ui \
    workerform.ui \
    workereditdialog.ui \
    scheduledialog.ui \
    dayadapter.ui
