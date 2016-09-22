#include "xeno_system.h"

#if basesystem == 0
    #include <sys/mman.h>
    #include <native/task.h>
    #include <native/timer.h>
#endif

#include "define.h"
#include "CONTROL/XenoReady.h"

#if basesystem == 0
    RT_TASK xeno_task;   // May be realtime task from xeno system
#endif

xeno_system::xeno_system(QObject *parent):QObject(parent)
{

}

void catch_signalb(int sig)
{
}

void XenoCallBack(void *arg){ // This function may be call each time  xenomai_timer tick (0.2 ms)

    xeno_func* xeno_var = (xeno_func*)arg;
    xeno_var->stop = false;


#if basesystem ==0
    using namespace define;
    RTIME now, previous,sampling;
    sampling = SAMPLING_TIME*pow(10,9);
    rt_task_set_periodic(NULL, TM_NOW, sampling);
    previous = rt_timer_read();

    sleep(0.5);  // What does it mean

    while (1) {
        rt_task_wait_period(NULL);// Is this waiting for sampling time example 0.2 ms
        now = rt_timer_read();

        if(xeno_var->con2dExp->stepcount < xeno_var->con2dExp->max_step&&!(xeno_var->stop))
        {
            (*xeno_var->con2dExp->datalog)(2,xeno_var->con2dExp->stepcount)=now;  // What does this function mean
            // save real time now data to datalog


            if (1)
            {
                xeno_var->con2dExp->ControlAll(xeno_var->con2dExp->stepcount);
                xeno_var->con2dExp->stepcount++;
            }
            else
            {
                xeno_var->con3dExp->IndependentCon(xeno_var->con3dExp->stepcount
                                             ,false);
                xeno_var->con3dExp->stepcount++;

                if(xeno_var->con3dExp->stepcount > xeno_var->con3dExp->max_step)
                {
                    //xeno_var->::IOboardptr->ExitIOboard();
                    emit xeno_var->mThreadPtr->Extextfunc("finished");
                    emit xeno_var->mThreadPtr->finished();
                }
            }
        }

        else
        {
             linuxio io;
             io.Init();  // Init mean reset CNT and DA board to origin state
             std::cout << "finished"<<std::endl;
             emit xeno_var->mThreadPtr->Extextfunc("finished");
             rt_task_delete(&xeno_task);
        }
   }
#endif
}

void xeno_system::Init(std::vector<double> *conparam  // Setting control parameter for con2dExp, con3dExp
                       ,std::vector<double> *conparam2){


    unsigned int max_step = (unsigned int)(*conparam2)[14];
    xeno_var.Dim = 3;

    xeno_var.con2dExp.reset(new control2dExp(max_step,&xeno_var.stop));
    xeno_var.con3dExp.reset(new control3dExp(max_step));

    xeno_var.con2dExp->datalog=&XenoDatalog;
    xeno_var.con2dExp->datalog2=&XenoDatalog2;


    //xeno_var->::con3dExp->datalog=&XenoDatalog;

    xeno_var.con2dExp->SetConParam(conparam,conparam2);
    xeno_var.con3dExp->SetConParam(conparam);

    xeno_var.con2dExp->max_step = max_step;
    XenoDatalog.resize(define::NUM_ACTUATOR*8+17,max_step);
    XenoDatalog2.resize(10,max_step);


    XenoReady xenoready;
    xenoready.con2dExpptr=xeno_var.con2dExp.get();


    //xeno_var.con2dExp->Ready();

    ///////xeno_var.con2dExp->IOcda.xeno_taskptr = &xeno_task;

    //cb::mThreadPtr.reset(new mThread);
    //cb::IOboardptr.reset(new IOboard);


}

void xeno_system::start(){  // Start Xeno_system for experiment
#if basesystem == 0
    io.Init();
    signal(SIGTERM, catch_signalb);
    signal(SIGINT, catch_signalb);
    mlockall(MCL_CURRENT|MCL_FUTURE);
    rt_task_create(&xeno_task, "RTthread", 0, 99, 0);//prio 99
    std::cout<<"setting"<<std::endl;
    rt_task_start(&xeno_task, &XenoCallBack, &xeno_var); // Run with   xeno_task for thread
#endif
}
