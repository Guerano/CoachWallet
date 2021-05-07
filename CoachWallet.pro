QT += core gui widgets

CONFIG += c++17

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    src/MainWindow.hpp

FORMS += \
    src/MainWindow.ui

OTHER_FILES += \
    .gitignore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
