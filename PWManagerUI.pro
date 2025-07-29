QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/accountlistmodel.cpp \
    Model/modelindexiterator.cpp \
    Persistance/credentials.cpp \
    Persistance/sqlpersistance.cpp \
    SearchAccount/matchobject.cpp \
    SearchAccount/matchstring.cpp \
    Utility/range.cpp \
    accountdialog.cpp \
    accountliste.cpp \
    main.cpp \
    mainwindow.cpp \
    newaccountdlg.cpp \
    showaccountdlg.cpp

HEADERS += \
    Model/accountlistmodel.h \
    Model/modelindexiterator.h \
    Persistance/credentials.h \
    Persistance/enumapp.h \
    Persistance/enumeration.h \
    Persistance/sqlpersistance.h \
    SearchAccount/matchobject.h \
    SearchAccount/matchstring.h \
    Utility/range.h \
    Utility/sortlist.h \
    accountdialog.h \
    accountliste.h \
    mainwindow.h \
    newaccountdlg.h \
    showaccountdlg.h

FORMS += \
    accountdialog.ui \
    accountliste.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
