QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/src/audiomedia.cpp \
    model/src/audioplaylist.cpp \
    main.cpp \
    view/src/mainwindow.cpp \
    model/src/playlisttablemodel.cpp

HEADERS += \
    model/header/audiomedia.h \
    model/header/audioplaylist.h \
    view/header/mainwindow.h \
    model/header/playlisttablemodel.h

FORMS += \
    view/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/icons.qrc

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
