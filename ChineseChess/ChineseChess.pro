QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess.cpp \
    main.cpp \
    singlegame.cpp \
    start.cpp \
    step.cpp \
    stone.cpp \
    switch.cpp

HEADERS += \
    chess.h \
    singlegame.h \
    start.h \
    step.h \
    stone.h \
    switch.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    font.qrc \
    jay.qrc \
    jay.qrc \
    logo.qrc \
    pic.qrc
