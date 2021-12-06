QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# https://stackoverflow.com/questions/49274025/qt-specify-project-directories-like-build-and-src-in-pro-flie

INCLUDEPATH += include/qt/
INCLUDEPATH += include

SOURCES += \
    src/qt/CompressionDialog.cpp \
    src/qt/EchoDialog.cpp \
    src/qt/GainDialog.cpp \
    src/qt/LowPassDialog.cpp \
    src/qt/NormalizationDialog.cpp \
    src/qt/main.cpp \
    src/qt/mainwindow.cpp \
    src/wav.cpp \
    src/wavmanip.cpp


HEADERS += \
    include/qt/CompressionDialog.h \
    include/qt/EchoDialog.h \
    include/qt/GainDialog.h \
    include/qt/LowPassDialog.h \
    include/qt/NormalizationDialog.h \
    include/qt/mainwindow.h \
    include/wav.h \
    include/wavheader.h \
    include/wavmanip.h

FORMS += \
    uic/compression.ui \
    uic/echo.ui \
    uic/gain.ui \
    uic/lowpass.ui \
    uic/mainwindow.ui \
    uic/normalization.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/OneDrive_Folder_Icon.svg.png

RESOURCES += \
    resources/resources.qrc
