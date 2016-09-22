#include "MainSystem.h"
#include "GUI/desktopmachinetoolsystem.h"
#include "mThread.h"
#include "iostream"
#include "xeno_system.h"
#include <QApplication>


MainSystem::MainSystem(QObject *parent):QObject(parent)
{
    multTh=false;

    SubController.reset(new mThread);
    SubThread.reset(new QThread);
    w.reset(new DesktopMachineToolSystem);
    xeno.reset(new xeno_system);

    SubController->moveToThread(SubThread.get());


    connect(SubThread.get()
            ,SIGNAL(started())
            ,SubController.get()
            ,SLOT(start()));

    connect(SubController.get()   // Signal to update string in main window desktopmachinetoolsystem.Ui
            ,SIGNAL(Extextfunc(QString))
            ,w.get()
            ,SLOT(onValueChanged(QString)));

    connect(SubController.get()
            ,SIGNAL(finished())
            ,this
            ,SLOT(ThreadStop()));  // Connect finished simulation to Thread stop in Main System

    connect(w.get()
            ,SIGNAL(Th1Emit(bool))
            ,this
            ,SLOT(ThreadStart(bool)));

    connect(xeno.get()
            ,SIGNAL(textFunc(QString))
            ,w.get()
            ,SLOT(onValueChanged(QString)));


    SubController->GUIptr=w.get();


    conparam=&w->conparam;
    conparam2=&w->conparam2;




    w->Th_main = SubThread.get(); // Not using now

    xeno->xeno_var.mThreadPtr = SubController.get();

    w->show();

}


MainSystem::~MainSystem(){

}


void MainSystem::ThreadStop(){

    SubThread->quit();

}

// Start thread for simulation or experimetn
void MainSystem::ThreadStart(bool flug_per){


    if(flug_per){ //run Experiment run

        while(SubThread->isRunning()){    // Dont know meaning
            QCoreApplication::processEvents();
            QThread::sleep(0.3);
        }

        xeno->Init(conparam,conparam2);

        w->datalog=&xeno->XenoDatalog;
        w->datalog2=&xeno->XenoDatalog2;

        xeno->start();

    }

    else{   //run simulation run

        disconnect(SubThread.get()
                   ,SIGNAL(started())
                   ,0
                   ,0);
        connect(SubThread.get()
                ,SIGNAL(started())
                ,SubController.get()
                ,SLOT(start()));

        w->datalog=&SubController->datalog;
        w->datalog2=&SubController->datalog2;

        SubController->getData(conparam,conparam2);

        SubThread->start();

    }

}


void MainSystem::ExpReady(){


    while(SubThread->isRunning()){
        QCoreApplication::processEvents();
        QThread::sleep(0.3);
    }

    xeno->Init(conparam,conparam2);

    w->datalog=&xeno->XenoDatalog;

}
