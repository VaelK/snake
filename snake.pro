QT       += core gui

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
    actor.cpp \
    boardwidget.cpp \
    cpuactor.cpp \
    gamelogic.cpp \
    gamewidget.cpp \
    humanactor.cpp \
    main.cpp \
    mainwindow.cpp \
    naiveactor.cpp \
    selectactorwidget.cpp \
    stats.cpp \
    statwidget.cpp

HEADERS += \
    actor.h \
    actortype.h \
    boardwidget.h \
    celltype.h \
    cpuactor.h \
    direction.h \
    gamelogic.h \
    gamewidget.h \
    humanactor.h \
    mainwindow.h \
    naiveactor.h \
    selectactorwidget.h \
    stats.h \
    statwidget.h

FORMS += \
    boardwidget.ui \
    gamewidget.ui \
    mainwindow.ui \
    selectactorwidget.ui \
    statwidget.ui

TRANSLATIONS += \
    snake_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += charts
