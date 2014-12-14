#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T13:52:59
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameModel
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    gameserver.cpp \
    server.cpp \
    threade.cpp \
    lobby.cpp \
    messageformat.cpp \
    client.cpp \
    composer.cpp \
    enemy.cpp \
    bullet.cpp

HEADERS  += dialog.h \
    propertis.h \
    gameserver.h \
    server.h \
    threade.h \
    lobby.h \
    TConversation.h \
    messageformat.h \
    client.h \
    composer.h \
    enemy.h \
    bullet.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
