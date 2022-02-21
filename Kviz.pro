#-------------------------------------------------
#
# Project created by QtCreator 2020-07-15T15:54:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kviz
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

CONFIG += c++11

SOURCES += \
    dodajkviz.cpp \
    dodajpitanje.cpp \
    dodajuser.cpp \
    kvizpregled.cpp \
    loginedit.cpp \
        main.cpp \
        kvizlogin.cpp \
    f_student.cpp \
    f_admin.cpp \
    kviz.cpp \
    izborkv.cpp \
    pitanjeedit.cpp \
    useredit.cpp \
    kvizedit.cpp \
    userpredmet.cpp

HEADERS += \
    dodajkviz.h \
    dodajpitanje.h \
    dodajuser.h \
        kvizlogin.h \
    f_student.h \
    f_admin.h \
    kviz.h \
    izborkv.h \
    kvizpregled.h \
    loginedit.h \
    pitanjeedit.h \
    useredit.h \
    kvizedit.h \
    userpredmet.h

FORMS += \
    dodajkviz.ui \
    dodajpitanje.ui \
    dodajuser.ui \
        kvizlogin.ui \
    f_student.ui \
    f_admin.ui \
    kviz.ui \
    izborkv.ui \
    kvizpregled.ui \
    loginedit.ui \
    pitanjeedit.ui \
    useredit.ui \
    kvizedit.ui \
    userpredmet.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target