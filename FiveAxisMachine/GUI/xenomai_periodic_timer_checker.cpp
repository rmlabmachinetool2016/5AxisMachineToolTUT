#include "xenomai_periodic_timer_checker.h"
#include "ui_xenomai_periodic_timer_checker.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <mutex>

#if basesystem == 0
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

RT_TASK demo_task;
std::mutex m;

double sampling_time ;
double max_latency=0;
double min_latency;
double  a;
#endif

Xenomai_periodic_timer_checker::Xenomai_periodic_timer_checker(QWidget *parent) :
    QMainWindow(parent)
{
    ui.reset(new Ui::Xenomai_periodic_timer_checker);

    ui->setupUi(this);
#if basesystem == 0
    QPixmap pix("/home/oda/Downloads/DesktopMachinetoolSystem/picture/xenomai-logo.png");
    ui->label_pic_xeno->setPixmap(pix);
#endif
}

Xenomai_periodic_timer_checker::~Xenomai_periodic_timer_checker()
{

}

/* NOTE: error handling omitted. */

void demo_printf(void *arg)
{
#if basesystem == 0
    RTIME now, previous;

    rt_task_set_periodic(NULL, TM_NOW, sampling_time);
    previous = rt_timer_read();
    int err;




    a = 0;
    m.lock();
        for(unsigned int i=0;i<100000;i++) {
                rt_task_wait_period(NULL);
                now = rt_timer_read();

                printf("Time since last turn: %ld.%06ld ms\n",
                       (long)(now - previous) / 1000000,
                       (long)(now - previous) % 1000000);
                       previous = now;
    }
    std::cout<<"finished"<<std::endl;
    m.unlock();

#endif
}

void demo_test(void *arg)
{
#if basesystem == 0
    RTIME now, previous;
    long start_time,running_time;//order pico second
    unsigned long finish_time;
    max_latency =0;
    min_latency =0;

    running_time = 5;//second

    rt_task_set_periodic(NULL, TM_NOW, sampling_time);
    previous = rt_timer_read();
    start_time = (long)previous;
    finish_time = start_time+running_time * 1000000000 ;

    while (now < finish_time) {
        long latency;
        rt_task_wait_period(NULL);
        now = rt_timer_read();

        latency = sampling_time-(long)(now-previous);

              a =  sampling_time-(now - previous);
if(a<min_latency){min_latency=a;}
if(a>max_latency){max_latency = a;}
printf("max latency: %f \n",a);
               previous = now;
    }
#endif
}

void catch_signal(int sig)
{
}



void Xenomai_periodic_timer_checker::on_pushButton_clicked()
{
#if basesystem == 0
    QString Q_sampling_time;
    Q_sampling_time = ui->checking_sampling_time->text();



    sampling_time = Q_sampling_time.toDouble();
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    mlockall(MCL_CURRENT|MCL_FUTURE);


    rt_task_create(&demo_task, "trivial", 0, 99, 0);

    int checker_mode;
    checker_mode = ui->comboBox_checkermode->currentText().toInt();

    switch (checker_mode) {
            case 1:
                rt_task_start(&demo_task, &demo_printf, NULL);
                break;
            case 2:
                rt_task_start(&demo_task, &demo_test, NULL);
                break;
            default:
                printf("error mode");
                break;
    }

#endif
}

void Xenomai_periodic_timer_checker::on_pushButton_2_clicked()
{
#if basesystem == 0
            rt_task_delete(&demo_task);
            printf("max latency: %f \n",max_latency);
            printf("min latency: %f \n",min_latency);
#endif
}
void Xenomai_periodic_timer_checker::on_pushButton_stop2_clicked(){
    #if basesystem == 0
    int err;
    m.lock();
    std::cout<<"coutttt"<<std::endl;
    m.unlock();
    #endif

}
