#-------------------------------------------------
#
# Project created by QtCreator 2022-10-10T18:08:29
#
#-------------------------------------------------

QT       += core gui
QT       +=sql

TARGET = kaoqin
TEMPLATE = app


SOURCES += main.cpp\
        lsk_add.cpp \
    lsk_main.cpp \
    test.cpp \
    ATSysDatabaseControl.cpp \
    login.cpp \
    lsk_card.cpp \
    lsk_chaxun.cpp

HEADERS  += lsk_add.h \
    lsk_main.h \
    test.h \
ATSysDatabaseControl.h \
    login.h \
    lsk_card.h \
    lsk_chaxun.h

FORMS    += lsk_add.ui \
    lsk_main.ui \
    test.ui \
    login.ui \
    lsk_card.ui \
    lsk_chaxun.ui


RESOURCES += \
    lsk_imgs.qrc
