#include "mThread.h"
#include <boost/timer.hpp>
#include "CONTROL/control2D.h"
#include "CONTROL/control3D.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>

#if basesystem == 0
    #include <unistd.h>
    #include <sys/mman.h>
    #include <native/task.h>
    #include <native/timer.h>
#endif




mThread::mThread(QObject *parent)
            :QObject(parent)
            ,con2dSim_(false)
            ,con3d_(false)
{
    mThreadPtr = this;
    IOboardptr = new IOboard;//zikken saiyuusen
    IOboardptr->Threadptr=this;
}

void mThread::softlimitchecker(){
    //IOboard_.InitIOboard(3);//Initboard
    //Init CNT
}


void mThread::start(){
    double calc_time;
    boost::timer b_timer;

    if(selectWork==1){
        if(select_DOF==2){

            con2dSim->ControlSim2D(selectControl,max_step,EnableNoise,true);


        }
        else if (select_DOF==3){
            con3d->ControlSim3D(selectControl,max_step,EnableNoise,false);
           // con3d->datalog =&datalog;
        }
        calc_time = b_timer.elapsed();
        emit Extextfunc("finished");
        emit Extextfunc("simulation time   "+QString::number(calc_time)+"s");
        calc_time = calc_time/max_step*1000;
        emit Extextfunc("average time   "+QString::number(calc_time)+"ms");
        emit finished();
    }

    else if(selectWork==2){
        bool TF;
        if(select_DOF==2){
            con2dExp->datalog=&datalog;
            std::cout<<"set para"<<std::endl;

            // TF = cb::IOboardptr->InitIOboard(3);
            }
        else if (select_DOF==3){
            //con3dExp->datalog=& datalog;
            TF = IOboardptr->InitIOboard(5);
        }
        //if(TF==false)cb::IOboardptr->ExitIOboard();
    }
    this->finished();
}
mThread::~mThread(){


    //cb::IOboardptr->ExitIOboard();

    //delete IOboardptr;

}
void mThread::IOtext(QString text){
    emit Extextfunc(text);
}

void mThread::getData(std::vector<double> *conparam
                        ,std::vector<double> *conparam2){



    selectWork=(*conparam2)[12];
    selectControl=(*conparam2)[11];
    select_DOF=(*conparam2)[13];
    max_step = (unsigned int)(*conparam2)[14];

    datalog.resize(define::NUM_ACTUATOR*8+17,max_step);
    datalog2.resize(8,max_step);
    datalog.clear();
    datalog2.clear();


    if(selectWork==1){
        if(select_DOF==2){
            con2dSim.reset(new control2dSim(max_step,&datalog));
            con2dSim->datalog=&datalog;
            con2dSim->datalog2=&datalog2;
            con2dSim->SetConParam(conparam,conparam2);
        }
        else if (select_DOF==3){
            //con3d.reset(new control3d(max_step,&datalog));
            con3d_=true;
            con3d->SetConParam(conparam);
        }
    }

/*
    else if(selectWork==2){
        if(select_DOF==2){
            con2dExp = new control2dExp(max_step);
            con2dExp_ = true;
            con2dExp->SetConParam(conparam,conparam2);
            con2dExp->max_step = max_step;
            (*Dim) = 3;
        }
        else if (select_DOF==3){
            con3dExp=new control3dExp(max_step);
            con3dExp->SetConParam(conparam);
            con3dExp->max_step = max_step;
            (*Dim) = 5;
        }
    }*/

    if ((*conparam2)[15]==0)       EnableNoise = false;
    else                           EnableNoise = true;


}



#if basesystem ==2
void cb::TimerCallBackProc(short m_Id, int wParam, int lParam, void * Param){
    using namespace define;
    (void)m_Id;
    (void)wParam;
    (void)lParam;
    (void)Param;



    if (Dim==3){
            cb::con2dExp->ControlAll(cb::con2dExp->stepcount
                                         ,cb::IOboardptr->AioId
                                         ,cb::IOboardptr->CntId);
            cb::con2dExp->stepcount++;
            if(cb::con2dExp->stepcount > cb::con2dExp->max_step){
                    cb::IOboardptr->ExitIOboard();
                    //delete  IOboardptr;
                    //mainwindow->textBrowser->append("EXP finished");
                    emit cb::mThreadPtr->Extextfunc("finished");
                    emit cb::mThreadPtr->finished();
                //if(is_stop == false){
                    //is_stop = true;
                    //ControlStop();
                //}
            }}
    else {
        cb::con3dExp->IndependentCon(cb::con3dExp->stepcount
                                     ,cb::IOboardptr->AioId
                                     ,cb::IOboardptr->CntId
                                     ,false);
        cb::con3dExp->stepcount++;
        if(cb::con3dExp->stepcount > cb::con3dExp->max_step){
                cb::IOboardptr->ExitIOboard();
                emit cb::mThreadPtr->Extextfunc("finished");
                emit cb::mThreadPtr->finished();

        }}


    /*
    else if(is_finish_condition_time == false){
        if(control2d::IsReachPoint(time,max_angle,datalog) && is_stop == false){
            is_stop = true;
            ControlStop();
        }
    }*/


    time = step * SAMPLING_TIME;//step=>global


    if(select_3d){
        if(control_type == control3d::INDEPENDENT)
            control3d::IndependentCon(step,AioId,CntId,enable_sync,datalog);
        else if(control_type == control3d::CONTOURING)
            control3d::ContouringCon(step,AioId,CntId,enable_sync,datalog);
        else if(control_type == control3d::MOD_CONTOURING)
            control3d::modContouringCon(step,AioId,CntId,enable_sync,datalog);
    }else{
        if(control_type == control2d::INDEPENDENT)
            control2d::IndependentCon(step,AioId,CntId,enable_sync,datalog);
            //control2d::Identification(step,AioId,CntId,enable_sync,datalog);
        else if(control_type == control2d::CONTOURING)
            control2d::ContouringCon(step,AioId,CntId,enable_sync,datalog);
        else if(control_type == control2d::MOD_CONTOURING)
            control2d::modContouringCon(step,AioId,CntId,enable_sync,datalog);
    }

    // show progress bar
    //double pro = static_cast<double>(step*100)/max_step;
    //SetProgressDelegate^ deleSetProgress = gcnew SetProgressDelegate(this, &Form1::SetProgress);
    //this->Invoke(deleSetProgress, static_cast<int>(pro));

    // 設定時間が経過したら制御停止
    // データログの変数アレイの数はmax_stepによって決まるので、設定時間経過後は終了条件に関わらず制御停止
    if(++step > max_step-1){
        if(is_stop == false){
            is_stop = true;
            ControlStop();
        }
    }
    else if(is_finish_condition_time == false){
        if(control2d::IsReachPoint(time,max_angle,datalog) && is_stop == false){
            is_stop = true;
            ControlStop();
        }
    }

    return;
}
#endif
