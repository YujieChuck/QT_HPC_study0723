#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T11:17:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       +=xml    #For qdom.h
TARGET = QT_HPC_study
TEMPLATE = app
PRECOMPILED_HEADER  = head.h
CONFIG  +=C++11

#For C1083
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"
LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"

INCLUDEPATH +=$$PWD/inc/goodwidget
INCLUDEPATH +=$$PWD/inc
INCLUDEPATH +=$$PWD/inc/goodwidget/PropertBrowser/src
include($$PWD/inc/goodwidget/PropertBrowser/src/qtpropertybrowser.pri)

SOURCES += main.cpp\
    inc/gui/gui.cpp \
    inc/gui/basewindow.cpp \
    inc/gui/csvfileparse.cpp \
    inc/gui/groupboxextend.cpp \
    inc/gui/mytitlebar.cpp \
    inc/gui/csvfilewrite.cpp \
    inc/unity/caeglobalfunction.cpp \
    ccenterwidget.cpp \
    qt_hpc_studyy_qmainwindow.cpp \
    qt_hpc_study_qdialog.cpp \
    inc/goodwidget/Demo_MsgNotify/demo_msgnotify.cpp \
    inc/goodwidget/msgNotify/notify.cpp \
    inc/goodwidget/msgNotify/notifymanager.cpp \
    inc/gui/Text/codeeditor.cpp \
    inc/gui/Text/myhighlighter.cpp \
    inc/goodwidget/drawprogressbar/drawprogressbar.cpp \
    tab/json/cgeneratejson.cpp \
    inc/goodwidget/NavListView/navlistview.cpp \
    inc/goodwidget/NavListView/navlistview.cpp \
    inc/goodwidget/drawprogressbar/drawprogressbar.cpp \
    tab/json/cgeneratejson.cpp \
#    tab/thirft/Interface_constants.cpp \
#    tab/thirft/Interface_types.cpp \
#    tab/thirft/RPCMasterService.cpp \
#    tab/thirft/cmanegeservice.cpp
    inc/gui/Text/myhighlighter.cpp

HEADERS  += \
    inc/gui/gui.h \
    inc/gui/basewindow.h \
    inc/gui/csvfileparse.h \
    inc/gui/groupboxextend.h \
    inc/gui/mytitlebar.h \
    inc/gui/csvfilewrite.h \
    inc/unity/caeglobalfunction.h \
    head.h \
    ccenterwidget.h \
    qt_hpc_study_qmainwindow.h \
    qt_hpc_study_qdialog.h \
    inc/goodwidget/Demo_MsgNotify/demo_msgnotify.h \
    inc/goodwidget/msgNotify/notify.h \
    inc/goodwidget/msgNotify/notifymanager.h \
    inc/gui/Text/codeeditor.h \
    inc/gui/Text/myhighlighter.h \
    inc/gui/Text/typedef.h \
    inc/goodwidget/drawprogressbar/drawprogressbar.h \
    tab/json/cgeneratejson.h \
    inc/goodwidget/NavListView/navlistview.h \
    inc/goodwidget/NavListView/navlistview.h \
    inc/goodwidget/drawprogressbar/drawprogressbar.h \
    tab/json/cgeneratejson.h \
#    tab/thirft/Interface_constants.h \
#    tab/thirft/Interface_types.h \
#    tab/thirft/RPCMasterService.h \
#    tab/thirft/cmanegeservice.h \
#    tab/thirft/RPCMasterService_server.h \
#    tab/thirft/winsock2i.h
    inc/gui/Text/typedef.h


RESOURCES += \
    ConfigurationFolder/images/QSS/qt_hpc_rc.qrc \
    ConfigurationFolder/images/LQRes/ExampleImage.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/poco/ -lCppUnit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/poco/ -lCppUnitd
else:unix: LIBS += -L$$PWD/../lib/poco/ -lCppUnit

INCLUDEPATH += $$PWD/../lib/poco
DEPENDPATH += $$PWD/../lib/poco

INCLUDEPATH += $$PWD/../lib/PropertBrowser
DEPENDPATH += $$PWD/../lib/PropertBrowser


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/for_thirft/boost/lib_x64 -lCppUnit
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/for_thirft/boost/lib_x64 -lCppUnitd
#else:unix: LIBS += -L$$PWD/../lib/for_thirft/boost/lib_x64 -lCppUnit

#INCLUDEPATH += $$PWD/../lib/for_thirft/boost/lib_x64
#DEPENDPATH += $$PWD/../lib/for_thirft/boost/lib_x64
#INCLUDEPATH += $$PWD/../lib/for_thirft/boost/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/for_thirft/libevent/lib_x64 -lCppUnit
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/for_thirft/libevent/lib_x64 -lCppUnitd
#else:unix: LIBS += -L$$PWD/../lib/for_thirft/libevent/lib_x64 -lCppUnit

#INCLUDEPATH += $$PWD/../lib/for_thirft/libevent/lib_x64
#DEPENDPATH += $$PWD/../lib/for_thirft/libevent/lib_x64
#INCLUDEPATH += $$PWD/../lib/for_thirft/libevent/include


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/for_thirft/thrift/lib_x64 -lCppUnit
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/for_thirft/thrift/lib_x64 -lCppUnitd
#else:unix: LIBS += -L$$PWD/../lib/for_thirft/thrift/lib_x64 -lCppUnit

#INCLUDEPATH += $$PWD/../lib/for_thirft/thrift/lib_x64
#DEPENDPATH += $$PWD/../lib/for_thirft/thrift/lib_x64
#INCLUDEPATH += $$PWD/../lib/for_thirft/thrift/inc


