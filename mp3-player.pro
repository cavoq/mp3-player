QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiomedia.cpp \
    audioplaylist.cpp \
    main.cpp \
    mainwindow.cpp \
    playlisttablemodel.cpp

HEADERS += \
    audiomedia.h \
    audioplaylist.h \
    mainwindow.h \
    playlisttablemodel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -ltag
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -ltag
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -ltag
LIBS += -lz

INCLUDEPATH += $$PWD/../../../usr/local/include/taglib
DEPENDPATH += $$PWD/../../../usr/local/include/taglib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libtag.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libtag.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/tag.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/tag.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libtag.a
