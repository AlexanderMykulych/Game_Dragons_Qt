#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T18:54:54
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        form.cpp \
    gamebutton.cpp \
    client.cpp \
    gameclient.cpp \
    gameserver.cpp \
    server.cpp \
    threade.cpp \
    myfont.cpp \
    gameedit.cpp \
    gamelabel.cpp \
    gamecombobox.cpp \
    server_finder.cpp \
    gameloadanimation.cpp \
    mystringlist.cpp \
    messageformat.cpp \
    game_canvas.cpp \
    game_object.cpp \
    bg_sky.cpp \
    dragon_obj.cpp \
    enemy_obj.cpp \
    explosion.cpp \
    bonus_obj.cpp \
    bullet_obj.cpp \
    info_box.cpp \
    g_sound.cpp

HEADERS  += form.h \
    gamebutton.h \
    client.h \
    gameclient.h \
    gameserver.h \
    propertis.h \
    server.h \
    threade.h \
    myfont.h \
    gameedit.h \
    gamelabel.h \
    gamecombobox.h \
    server_finder.h \
    gameloadanimation.h \
    mystringlist.h \
    messageformat.h \
    game_canvas.h \
    game_object.h \
    bg_sky.h \
    dragon_obj.h \
    enemy_obj.h \
    explosion.h \
    bonus_obj.h \
    bullet_obj.h \
    info_box.h \
    g_sound.h

FORMS    += form.ui

RESOURCES += \
    res_button.qrc
