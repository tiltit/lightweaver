CONFIG += qt debug
SOURCES += main.cpp MainWindow.cpp colorwheel.cpp split.cpp Serial.cpp motorcontrol.cpp paintings.cpp
HEADERS += MainWindow.h colorwheel.h split.h Serial.h motorcontrol.h

#ui_mainwindow.h

INCLUDEPATH += /usr/include/opencv2 /usr/include
CFLAGS += -std=c++11 -fPIC -g -Wall `pkg-config --cflags opencv`
CXXFLAGS += -std=c++11

LIBS += `pkg-config --libs opencv`

LIBS += -lm

QT += widgets

TARGET = lightweaver-gui

FORMS = ui-main-window.ui

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += $(CFLAGS)
