
#Update Haiz het chan
QT      +=  core gui opengl
QT      +=  printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES +=  DeviceReady=0
#In the experiment, use expression template!!!!

DEFINES += NDEBUG#enable expression template
TARGET      = 5axis_MCDinhBa

TEMPLATE    = app
CONFIG      += c++14


SOURCES +=  main.cpp \
            BASESYSTEM/mThread.cpp \
            BASESYSTEM/MainSystem.cpp \
            CONTROL/control3D.cpp \
            GUI/xenomai_periodic_timer_checker.cpp \
            IO/linuxio.cpp \
            CONTROL/SGfilter.cpp \
            LIB/mass.cpp \
            BASESYSTEM/xeno_system.cpp \
            GUI/desktopmachinetoolsystem.cpp \
            GUI/form_tool.cpp\
            CONTROL/control2D.cpp\
            IO/io.cpp\
            CONTROL/plant.cpp \
            GUI/OutputFile.cpp\
            LIB/qcustomplot.cpp\
            GUI/OPENGL/openglwindow.cpp\
            GUI/OPENGL/glwidget.cpp\
            IO/ioboard.cpp \
            CONTROL/XenoReady.cpp \
            CONTROL/AdaptiveControl.cpp \
            GUI/FormDrawGraph.cpp \
            GUI/FormGraphFunction.cpp

HEADERS  += GUI/desktopmachinetoolsystem.h \
            GUI/form_tool.h\
            define.h\
            CONTROL/control2D.h\
            IO/io.h \
            CONTROL/plant.h\
            LIB/math.hpp \
            GUI/OutputFile.h\
            LIB/qcustomplot.h \
            GUI/OPENGL/openglwindow.h \
            GUI/OPENGL/glwidget.h \
            stdafx.h\
            IO/ioboard.h \
            BASESYSTEM/mThread.h \
            BASESYSTEM/MainSystem.h \
            CONTROL/control3D.h \
            optimization.h \
            GUI/xenomai_periodic_timer_checker.h \
            IO/linuxio.h \
            CONTROL/SGfilter.h \
            BASESYSTEM/xeno_system.h \
            CONTROL/XenoReady.h \
            LIB/numeric.hpp \
            CONTROL/AdaptiveControl.h \
            GUI/FormDrawGraph.h \
            GUI/FormGraphFunction.h

FORMS   +=  desktopmachinetoolsystem.ui \
                    openglwindow.ui \
                    xenomai_periodic_timer_checker.ui


#win32 {
#    HEADERS  += Caio.h CCnt.h #for windows
#}


win32:LIBS += -lopengl32
#win32:LIBS += -lglut32
#win32:LIBS += -LF:\UbuntuROST\Window OS\freeglutt
unix: LIBS += -lGLU -lGL -lglut

unix {
    QMAKE_CXXFLAGS +=   -I/usr/xenomai/include/trank -D__XENO_COMPAT__\
                        -I/usr/xenomai/include/cobalt -I/usr/xenomai/include -D_GNU_SOURCE\
                        -D_REENTRANT -D__COBALT__\
                        -I/usr/xenomai/include/alchemy

    QMAKE_LIBS+=        -ltrank  \
                        -lalchemy \
                        -Wl,--wrap=main \
                        -Wl,--dynamic-list=/usr/xenomai/lib/dynlist.ld \
                        -lcopperplate \
                        -L/usr/xenomai/lib \
                        -lcobalt \
                        -lpthread \
                        -lrt\
                        -Xlinker -rpath \
                        -Xlinker /usr/xenomai/lib

#QMAKE_CXXFLAGS  +=  -I/home/threeaxiscnc/boost_1_61_0/
#/media/threeaxiscnc/LINUX/5AxisCNCExperiment/Rmlab5AxisCNCSoft/Linux5AxisCNC

QMAKE_CXXFLAGS  +=  -I/media/threeaxiscnc/LINUX/5AxisCNCExperiment/Rmlab5AxisCNCSoft/Linux5AxisCNC/boost_1_61_0/
#-I/home/rnlab/boost_1_61_0/stage/include/

#linux::DEPENDPATH   +=/home/oda/boost_1_61_0/stage/include/

    #CONFIG += console
    #CONFIG += /usr/bin/gnome-terminal -x
}

windows::INCLUDEPATH += D:\5AxisCNCExperiment\Rmlab5AxisCNCSoft\Linux5AxisCNC\boost_1_61_0
#windows::INCLUDEPATH += F:\UbuntuROST\Window OS\freeglut
windows::DEPENDPATH += D:\5AxisCNCExperiment\Rmlab5AxisCNCSoft\Linux5AxisCNC\boost_1_61_0
#windows::DEPENDPATH += F:\UbuntuROST\Window OS\freeglut

#-L/home/rnlab/boost_1_61_0/stage/lib/\
unix:LIBS +=  -L/media/threeaxiscnc/LINUX/5AxisCNCExperiment/Rmlab5AxisCNCSoft/Linux5AxisCNC/boost_1_61_0/
#unix:LIBS +=  -L/home/threeaxiscnc/boost_1_61_0/\
unix:LIBS +=  -lboost_date_time
QMAKE_CXXFLAGS+=  -O2
#windows::DISTFILES += \
#    lib/caio.lib\
#    lib/CCNT.lib\
#    lib/ciolib.lib

win32: LIBS += -L$$PWD/lib/ -lcaio

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/


#win32: LIBS += -L$$PWD/lib/ -lCCNT
#win32: LIBS += -L$$PWD/lib/ -lciolib

unix {
    DEFINES += basesystem=0
}
win32 {
    DEFINES += basesystem=1
}
