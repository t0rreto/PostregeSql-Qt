QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connect.cpp \
    goals.cpp \
    main.cpp \
    mainwindow.cpp \
    matches.cpp \
    players.cpp \
    querywindow.cpp \
    teams.cpp \
    transactionwindow.cpp \
    viewwindow.cpp

HEADERS += \
    connect.h \
    goals.h \
    mainwindow.h \
    matches.h \
    players.h \
    querywindow.h \
    teams.h \
    transactionwindow.h \
    viewwindow.h

FORMS += \
    mainwindow.ui \
    querywindow.ui \
    transactionwindow.ui \
    viewwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
