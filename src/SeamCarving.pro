QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeamCarving
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CalcPath.cpp \
    SobelOp.cpp

HEADERS  += MainWindow.h \
    CalcPath.h \
    SobelOp.h

FORMS    += MainWindow.ui
