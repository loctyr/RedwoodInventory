QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appleitem.cpp \
    dbadapter.cpp \
    inventory.cpp \
    inventorycell.cpp \
    item.cpp \
    itemfactory.cpp \
    itemlabel.cpp \
    itemrecord.cpp \
    main.cpp \
    mainwindow.cpp \
    mainmenuwidget.cpp

HEADERS += \
    appleitem.h \
    dbadapter.h \
    inventory.h \
    inventorycell.h \
    item.h \
    itemfactory.h \
    itemlabel.h \
    itemrecord.h \
    mainwindow.h \
    mainmenuwidget.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Inventory_ru_RU.ts

RESOURCES += \
    resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
