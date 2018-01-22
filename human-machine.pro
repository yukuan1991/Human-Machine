#-------------------------------------------------
#
# Project created by QtCreator 2017-07-19T14:22:43
#
#-------------------------------------------------

QT       += core gui
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = human-machine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cc \
    Balance/Channel.cc \
    Balance/ResourceScene.cc \
    Balance/TaskBlock.cc \
    Balance/HmAnalysis/HaBlock.cc \
    Balance/HmAnalysis/HaView.cc \
    Balance/HmAnalysis/AddTaskDlg.cc \
    Ribbon.cc \
    HmRibbon.cc \
    HmMain.cc \
    Balance/HmAnalysis/Analysis.cc \
    Balance/HmAnalysis/HaChannel.cc \
    Balance/HmAnalysis/ChannelTitle.cc \
    openvaf.cc \
    verification/des.cc \
    verification/encryption.cc \
    verification/verification.cpp


FORMS += \
    Balance/HmAnalysis/AddTaskDlg.ui \
    HmMain.ui \
    Balance/HmAnalysis/Analysis.ui

HEADERS += \
    Balance/Channel.h \
    Balance/parameters.hpp \
    Balance/ResourceScene.h \
    Balance/TaskBlock.h \
    Balance/HmAnalysis/HaBlock.h \
    Balance/HmAnalysis/HaView.h \
    Balance/HmAnalysis/AddTaskDlg.h \
    Ribbon.h \
    HmRibbon.h \
    HmMain.h \
    Balance/HmAnalysis/Analysis.h \
    Balance/HmAnalysis/HaChannel.h \
    Balance/HmAnalysis/ChannelTitle.h \
    openvaf.h \
    verification/des.h \
    verification/encryption.h \
    verification/json.hpp \
    verification/verification.h

LIBS += -lboost_filesystem
LIBS += -lboost_system
LIBS += -lboost_regex
LIBS += -lboost_thread
LIBS += -lboost_locale
LIBS += -liconv
LIBS += -lwininet
LIBS += -lws2_32
