QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/endgame.cpp \
    game/mainwindow.cpp \
    game/message.cpp \
    game/qnchatmessage.cpp \
    public/connection.cpp \
    room/roomWindow.cpp \
    user/forget_window.cpp \
    user/main.cpp \
    user/log_in_window.cpp \
    user/register_window.cpp \
    public/smtp.cpp \
    game/emoji.cpp \
    public/public.cpp \
    game/qchess.cpp \
    game/qchessmap.cpp \
    room/dating.cpp \
    room/dialog.cpp \
    room/room.cpp \
    room/test.cpp \
    support/advice.cpp \
    support/information.cpp \
    public/img.cpp \



HEADERS += \
    game/endgame.h \
    game/mainwindow.h \
    game/message.h \
    game/qnchatmessage.h \
    public/connection.h \
    room/roomWindow.h \
    user/forget_window.h \
    user/log_in_window.h \
    user/register_window.h \
    public/smtp.h \
    game/emoji.h \
    public/public.h \
    game/qchess.h \
    game/qchessmap.h \
    room/dating.h \
    room/dialog.h \
    room/room.h  \
    room/test.h \
    support/advice.h \
    support/information.h \
    public/img.h \

FORMS += \
    game/endgame.ui \
    game/mainwindow.ui \
    game/message.ui \
    room/roomWindow.ui \
    user/forget_window.ui \
    user/log_in_window.ui \
    user/register_window.ui \
    room/dating.ui \
    room/dialog.ui \
    room/room.ui \
    room/test.ui \
    support/advice.ui \
    support/information.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
