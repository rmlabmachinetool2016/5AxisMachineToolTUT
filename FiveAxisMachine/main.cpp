
#define _STDCALL_SUPPORTED

#include <stdafx.h>
#include <QApplication>
//#include <windows.h>
#include <GL/freeglut.h>
#include "GUI/desktopmachinetoolsystem.h"
#include "BASESYSTEM/MainSystem.h"
#include <QProcess>
int main(int argc, char *argv[])
{
    glutInit( & argc, argv );
    glutInitDisplayMode(GLUT_RGBA);
    QApplication a(argc, argv);
    MainSystem MainSystem_;  // Init program and  destopmachinetoolsystem UI
//    (void)MainSystem_;

    return a.exec();
    return 0;
}
