QT       += core gui
QT += dtkcore dtkgui dtkwidget

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
    dlghelp.cpp \
    main.cpp \
    mainwindow.cpp \
    themeitemdelegate.cpp \
    themelistmodel.cpp \
    themelistview.cpp \
    themepanel.cpp

HEADERS += \
    dlghelp.h \
    mainwindow.h \
    themeitemdelegate.h \
    themelistmodel.h \
    themelistview.h \
    themepanel.h

FORMS += \
    dlghelp.ui \
    mainwindow.ui

TRANSLATIONS += \
    deepin-terminal-themes_zh_CN.ts

DESTDIR = build/bin
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
unix:OBJECTS_DIR = build/o/unix

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    themes.qrc
