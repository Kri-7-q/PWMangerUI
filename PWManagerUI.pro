QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Persistance/credentials.cpp \
    Persistance/sqlpersistance.cpp \
    accountdialog.cpp \
    accountliste.cpp \
    accountwidgetitem.cpp \
    main.cpp \
    mainwindow.cpp \
    showaccount.cpp

HEADERS += \
    Persistance/credentials.h \
    Persistance/sqlpersistance.h \
    accountdialog.h \
    accountliste.h \
    accountwidgetitem.h \
    mainwindow.h \
    showaccount.h

FORMS += \
    accountdialog.ui \
    accountliste.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
