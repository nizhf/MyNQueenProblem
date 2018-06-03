TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    nqueenproblembasic.cpp

HEADERS += \
    nqueenproblembasic.h

QMAKE_CFLAGS_DEBUG += -MTd
QMAKE_CFLAGS_RELEASE += -MT
QMAKE_CXXFLAGS_DEBUG += -MTd
QMAKE_CXXFLAGS_RELEASE += -MT

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Library/googletest/x64/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Library/googletest/x64/ -lgtestd

INCLUDEPATH += $$PWD/../../../Library/googletest/x64/include
DEPENDPATH += $$PWD/../../../Library/googletest/x64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Library/googletest/x64/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Library/googletest/x64/libgtestd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Library/googletest/x64/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Library/googletest/x64/gtestd.lib
