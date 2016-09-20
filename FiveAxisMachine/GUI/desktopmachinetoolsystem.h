#ifndef DESKTOPMACHINETOOLSYSTEM_H
#define DESKTOPMACHINETOOLSYSTEM_H

#include <QMainWindow>
#include "define.h"
#include "xenomai_periodic_timer_checker.h"
#include "IO/ioboard.h"
#include "boost/shared_ptr.hpp"
#include "FormGraphFunction.h"
//extern control2dExp *con2dExptest;
#include <QtWidgets/QLineEdit>
class form_tool;
class openglwindow;
class QCustomPlot;
namespace Ui {class DesktopMachineToolSystem;}




class DesktopMachineToolSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit DesktopMachineToolSystem(QWidget *parent = 0);
    ~DesktopMachineToolSystem();
    std::vector<double>conparam;
    std::vector<double>conparam2;
    boost::numeric::ublas::matrix<double> *datalog;
    boost::numeric::ublas::matrix<double> *datalog2;
    QThread *Th_main;
    IOboard io;
public slots:
        void onValueChanged(QString);
        void ThreadQuit();

private slots:
    void on_lineEdit_MotionTime_textChanged(const QString &arg1);
    void on_lineEdit_Loop_textChanged(const QString &arg1);
    void on_pushButton_Start_clicked();
    void on_pushButton_clicked();
    void on_pushButton_XMLGenerater_clicked();
    void on_pushButton_DataDump_clicked();
    void on_pushButton_simulation_clicked();
    void on_pushButton_Openglsim_clicked();
    void on_pushButton_QuitMainwindow_clicked();
    void on_pushButton_OpenFolder_clicked();
    void on_pushButton_CreateFolder_clicked();
    void on_pushButton_StopControl_clicked();

    void on_pushButton_Ready_clicked();

    void on_radioButton_Experiment_clicked(bool checked);
    void on_radioButton_Simulation_clicked(bool checked);
    void AdaptiveParaUpdate(const QString & text);
private:

    boost::shared_ptr<Ui::DesktopMachineToolSystem> ui;
    boost::shared_ptr<form_tool> ui2;
    boost::shared_ptr<openglwindow> y;
    FormGraphFunction formgraphfunc;

    Xenomai_periodic_timer_checker xenotest;

    bool ptr_con2dExp,ptr_con2dSim,ptr_form2;
    double controlerType;


    void SetParameter();
    std::vector<std::string> graph_labelFunc
        (std::vector<unsigned int>graphNo);
    std::vector<std::string> graph_labelFunc2
        (std::vector<unsigned int>graphNo);
    void DrawGraphS();
    void DrawGraph(QCustomPlot *customPlot
                   , QString label[2], double range[4], int dataNum[2], int GraphNo, int mode);
    void DrawTrajectory(QCustomPlot *customPlot
                        , QString label[2], double range[4], int dataNum[2], int GraphNo);


    void ControllerTabInit();
    void connectAdapupdate(QLineEdit *boxname);

signals :
        void DataSet();
        void Th1Emit(bool flog_per);
};

#endif // DESKTOPMACHINETOOLSYSTEM_H
