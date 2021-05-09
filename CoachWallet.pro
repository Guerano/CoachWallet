QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += $$_PRO_FILE_PWD_/src/

SOURCES += \
    src/CoachWalletApplication.cpp \
    src/Project.cpp \
    src/User.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/utils/Json.cpp \
    src/utils/Singleshot.cpp \
    src/utils/Utility.cpp \
    src/utils/details/JsonImpl.cpp \
    src/views/HomeView.cpp \
    src/views/UserView.cpp \
    src/widgets/CWStackedWidget.cpp \
    src/widgets/NavigatorTree.cpp

HEADERS += \
    src/CoachWalletApplication.hpp \
    src/IWorkspaceView.hpp \
    src/MainWindow.hpp \
    src/Project.hpp \
    src/User.hpp \
    src/utils/Json.hpp \
    src/utils/Service.hpp \
    src/utils/ServiceLocator.hpp \
    src/utils/Singleshot.hpp \
    src/utils/StringFormatting.hpp \
    src/utils/StringLitterals.hpp \
    src/utils/Utility.hpp \
    src/utils/details/JsonImpl.hpp \
    src/utils/details/Singleshot.hpp \
    src/utils/details/StringFormatting.hpp \
    src/views/HomeView.hpp \
    src/views/UserView.hpp \
    src/widgets/CWStackedWidget.hpp \
    src/widgets/NavigatorTree.hpp

FORMS += \
    src/MainWindow.ui \
    src/views/HomeView.ui \
    src/views/UserView.ui

OTHER_FILES += \
    .gitignore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/coach-wallet_resources.qrc
