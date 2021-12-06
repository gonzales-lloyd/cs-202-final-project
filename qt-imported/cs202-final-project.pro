QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# https://stackoverflow.com/questions/49274025/qt-specify-project-directories-like-build-and-src-in-pro-flie

INCLUDEPATH += include/

SOURCES += \
    src/CompressionDialog.cpp \
    src/EchoDialog.cpp \
    src/GainDialog.cpp \
    src/LowPassDialog.cpp \
    src/NormalizationDialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp


HEADERS += \
    include/CompressionDialog.h \
    include/EchoDialog.h \
    include/GainDialog.h \
    include/LowPassDialog.h \
    include/NormalizationDialog.h \
    include/mainwindow.h

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
