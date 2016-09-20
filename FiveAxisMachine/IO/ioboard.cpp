//#include "desktopmachinetoolsystem.h"
#include "ioboard.h"
#include "stdafx.h"
//#include "Caio.h"
//#include "CCnt.h"
//#include "CIoLib.h"
#include "BASESYSTEM/mThread.h"
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
RT_TASK Ra_task;
#endif
void XenoCallBackProc(void *arg){
#if basesystem ==0




#endif
}



IOboard::IOboard(QObject *parent) :
     AIONoptr(NULL),CNTNoptr(NULL),QThread(parent)
{
    /*strcpy(AIONo,"AIO002");
    strcpy(CNTNo,"CNT001");
    AIONoptr = AIONo;
    CNTNoptr= CNTNo;*/

}

void IOboard::ExitIOboard(){
int checker;
#if basesystem == 0
    checker = rt_task_delete(&Ra_task);
    sleep(1);
    std::cout<<checker<<std::endl;
    io.Exit();
#endif
    std::cout<<"Exit"<<std::endl;
    #if DeviceReady == 1
    short ChNo[define::NUM_COUNTER] = {0,1,2,3,4,5,6};
        CNTret = CntOutputDOBit ( CntId , 0 , 0 , 0 );
        CNTret = CntStopNotifyTimer ( CntId );
        if (CNTret != 0){
            emit Threadptr->Extextfunc("CntStopNotifyTimer failure");
        }
        // Stoping counter board and DA board
        CNTret = CntStopCount ( CntId , ChNo , define::NUM_COUNTER );
        if (CNTret != 0){
         emit Threadptr->Extextfunc("CntStopCount failure");

        }
        for(unsigned int i=0;i<define::NUM_ACTUATOR;i++)
        {
            Aioret = AioSingleAoEx(AioId,i,0);
            if (Aioret != 0){
         emit Threadptr->Extextfunc("AioSingleAoEx failure");
            }
        }
        // ＤＡボードのクローズ
        Aioret = AioExit(AioId);
        if (Aioret != 0){
         emit Threadptr->Extextfunc("AioExit failure");
        }
        // カウンタボードのクローズ
        CNTret = CntExit(CntId);
        if (CNTret != 0){
         emit Threadptr->Extextfunc("CntExit failure");
        }
#endif

}
bool IOboard::InitIOboard(unsigned int mode){

#if basesystem == 0
    io.Init();
    signal(SIGTERM, catch_signalb);
    signal(SIGINT, catch_signalb);
    mlockall(MCL_CURRENT|MCL_FUTURE);
    rt_task_create(&Ra_task, "RTthread", 0, 99, 0);//prio 99
    std::cout<<"setting"<<std::endl;
    rt_task_start(&Ra_task, &XenoCallBackProc, NULL);
#endif
#if DeviceReady == 1
    strcpy(AIONo,"AIO000");
    strcpy(CNTNo,"CNT000");
    AIONoptr = AIONo;
    CNTNoptr= CNTNo;


using namespace define;

    short ChNo[define::NUM_COUNTER] = {0,1,2,3,4,5,6};
    //////init////////////////////////


        Aioret = AioInit(AIONoptr,&AioId);
                    if(Aioret != 0)
                {
                    emit Threadptr->Extextfunc("AioInit failure");
                    return false;
                }
                else emit Threadptr->Extextfunc("AioInit success");

       CNTret = CntInit(CNTNoptr,&CntId);
                               if(CNTret != 0)
                            {
                               emit Threadptr->Extextfunc("CntInit failure");
                               return false;
                            }
                            else emit Threadptr->Extextfunc("CntInit success");

    /////////resetprocess//////////////
        Aioret = AioResetProcess(AioId);
                                if(Aioret != 0)
                            {
                                emit Threadptr->Extextfunc("AioResetProcess failure");
                                return false;
                            }
                            else emit Threadptr->Extextfunc("AioResetProcess success");

    ////////ResetDevice/////////////////
        Aioret = AioResetDevice(AioId);
                                if(Aioret != 0)
                            {
                                emit Threadptr->Extextfunc("AioResetDevice failure");
                                return false;
                            }
                            else emit Threadptr->Extextfunc("AioResetDevice success");

        CNTret = CntResetDevice(CntId);
                                if(CNTret != 0)
                             {
                                emit Threadptr->Extextfunc("CntResetDevice failure");
                                return false;
                             }
                             else emit Threadptr->Extextfunc("CntResetDevice success");
    ///////SetAoRangeAll///////////////////////
        Aioret = AioSetAoRangeAll(AioId,PM10);
                                if(Aioret != 0)
                            {
                                emit Threadptr->Extextfunc("AioSetAoRangeAll failure");
                                return false;
                            }
                            else emit Threadptr->Extextfunc("AioSetAoRangeAll success");



    ///////CNTsetting///
        for(short i = 0;i<define::NUM_COUNTER;i++){

            CNTret = CntSelectChannelSignal(CntId,i,CNT_SIGTYPE_LINERECEIVER);
                                if(CNTret != 0)
                             {
                                emit Threadptr->Extextfunc("CntSelectChannelSignal failure");
                               return false;
                             }

            CNTret = CntSetOperationMode(CntId,i,CNT_MODE_2PHASE,CNT_MUL_X4,CNT_CLR_ASYNC);
                                if(CNTret != 0)
                             {
                                emit Threadptr->Extextfunc("CntSetOperationMode failure");
                               return false;
                             }

            CNTret = CntSetZMode(CntId,i,CNT_ZPHASE_NOT_USE);
                                if(CNTret != 0)
                             {
                                emit Threadptr->Extextfunc("CntSetZMode failure");
                               return false;
                             }

            CNTret = CntSetCountDirection (CntId,i,CNT_DIR_UP);
                                if(CNTret != 0)
                             {
                                emit Threadptr->Extextfunc("CntSetCountDirection failure");
                               return false;
                             }}

                             Sleep(200);
                       ////////////////////////////


                             CNTret = CntZeroClearCount ( CntId , ChNo , NUM_COUNTER );
                             if (CNTret != 0){
                                 return false;
                             }
                             CNTret = CntStartCount ( CntId , ChNo , NUM_COUNTER );
                           if (CNTret != 0){
                               std::cout<<CNTret<<std::endl;
                               return false;
                           }

                            double pos_pre[NUM_COUNTER];
                             unsigned long PresetData[NUM_COUNTER];
                             if(mode == 3){
                             double aa[NUM_COUNTER] = {INIT_POS_X,INIT_POS_Y1,INIT_POS_Y2,INIT_POS_Z,INIT_ANGLE_C,INIT_ANGLE_A1,INIT_ANGLE_A2};
                             for(int i=0;i<NUM_COUNTER;i++)pos_pre[i]=aa[i];
                             }
                             else {
                             double aa[NUM_COUNTER] = {INIT5_POS_X,INIT5_POS_Y1,INIT5_POS_Y2,INIT5_POS_Z,INIT5_ANGLE_C,INIT5_ANGLE_A1,INIT5_ANGLE_A2};
                             for(int i=0;i<NUM_COUNTER;i++){pos_pre[i]=aa[i];}

                             }

                             double resonate[NUM_COUNTER] = {RESONATE_LINER_ENC_X,RESONATE_LINER_ENC_Y1,RESONATE_LINER_ENC_Y2,RESONATE_LINER_ENC_Z,RESONATE_ROTATION_ENC_C,RESONATE_ROTATION_ENC_A1,RESONATE_ROTATION_ENC_A2};
                             long dir[NUM_COUNTER]={-1,1,-1,-1,1,1,-1};
                             for(unsigned int i=0;i<NUM_COUNTER;i++){
                                 pos_pre[i] = pos_pre[i]*dir[i]/resonate[i];
                                 PresetData[i] = static_cast<unsigned long>(pos_pre[i]);
                                 std::cout<<PresetData[i]<<std::endl;
                             }
                             CNTret = CntPreset( CntId , ChNo , NUM_COUNTER , PresetData );
                             if (CNTret != 0){
                                 return false ;
                             }

                             // reset power tester
                             CNTret = CntOutputDOBit ( CntId , 1 , 0 , 1 );
                             Sleep(200);
                             //System::Threading::Thread::Sleep(200);
                             CNTret = CntOutputDOBit ( CntId , 1 , 0 , 0 );
                             //pTimer	= Marshal::GetFunctionPointerForDelegate(dele_Timer);
                             CNTret	= CntTimerCallbackProc(CntId,cb::TimerCallBackProc, nullptr);
                             if(CNTret != 0)
                          {
                             emit Threadptr->Extextfunc("CntTimerCallbackProc failure");
                            return false;
                          }
                             CNTret = CntNotifyTimer ( CntId , static_cast<unsigned long>(SAMPLING_TIME*1000) , 0 );
                             if(CNTret != 0)
                          {
                             emit Threadptr->Extextfunc("CntNotifyTimer failure");
                            return false;
                          }
                             // start power tester
//this->ExitIOboard();

   emit Threadptr->Extextfunc("all init finished ");
#endif
   return true;
}

