#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T17:51:26
#
#-------------------------------------------------

QT       += core gui   network multimedia webkit webkitwidgets winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qxt
QXT += core gui
TARGET = Vkplayer
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    vk_get.cpp \
    vk_auth.cpp \
    vk_audiopop.cpp \
    json.cpp \
    auther.cpp \
    vk_friend.cpp \
    download.cpp \
    settings.cpp \
    helloy.cpp \
    vk_lyrics.cpp \
    lyrics_out.cpp \
    vk_add.cpp \
    updateversion.cpp \
    vk_post_status.cpp \
    vk_send_attachment.cpp \
    osdpretty.cpp \
    qtwin.cpp \
    vk_group.cpp \
    connecttoserver.cpp \
    audioedit.cpp \
    widgetparent.cpp \
    messages.cpp \
    threadplayer.cpp \
    runline.cpp \
    registration_key.cpp \
    vk_albums.cpp

HEADERS  += widget.h \
    vk_auth.h \
    vk_audiopop.h \
    auther.h \
    vk_get.h \
    vk_friend.h \
    download.h \
    settings.h \
    helloy.h \
    vk_lyrics.h \
    lyrics_out.h \
    vk_add.h \
    updateversion.h \
    vk_post_status.h \
    vk_send_attachment.h \
    osdpretty.h \
    qtwin.h \
    vk_group.h \
    connecttoserver.h \
    audioedit.h \
    widgetparent.h \
    messages.h \
    threadplayer.h \
    runline.h \
    registration_key.h \
    vk_albums.h

FORMS    += widget.ui \
    auther.ui \
    settings.ui \
    helloy.ui \
    lyrics_out.ui \
    osdpretty.ui \
    audioedit.ui \
    messages.ui \
    registration_key.ui

RC_FILE = myapp.rc


RESOURCES += \
    res.qrc \
    images.qrc \
    css.qrc

OTHER_FILES += \
    myapp.rc
