#include "stdafx.h"
#include "desktopmachinetoolsystem.h"
#include <ui_desktopmachinetoolsystem.h>
#include "OutputFile.h"
#include "form_tool.h"
#include "GUI/OPENGL/openglwindow.h"
#include "LIB/qcustomplot.h"
#include <QTimer>
#include "boost/numeric/ublas/matrix.hpp"

DesktopMachineToolSystem::DesktopMachineToolSystem(QWidget *parent) :
    QMainWindow(parent),ptr_con2dExp(false),ptr_con2dSim(false)
    ,ptr_form2(false)
{
    ui.reset(new Ui::DesktopMachineToolSystem);
    formgraphfunc.ui = ui.get();

    ui2.reset(new form_tool(ui.get()));

    ui->setupUi(this);

    QPixmap image("picture/logo2.jpg");
    ui->lab_logo->setPixmap(image);
    QPixmap image2("picture/boost_logo.jpg");
    ui->boost_logo->setPixmap(image2);
    QPixmap image3("picture/tut_logo.jpg");
    ui->tut_logo->setPixmap(image3);
    QPixmap image4("picture/xenomai_logo.jpg");
    ui->xenomai_logo->setPixmap(image4);


    ui2->xmlLoading();
    ui2->defineLoading();
    ui->radioButton_adaptiveCon_2->setChecked(true);

    ui->pushButton_Start->setStyleSheet("background-color:red");
    ui->pushButton_Start->setEnabled(true);

    ui->pushButton_Ready->setEnabled(false);

    ui->pushButton_DataDump->setStyleSheet("background-color: rgb(136, 136, 136)");
    ui->pushButton_Openglsim->setStyleSheet("background-color: rgb(136, 136, 136)");
    ui->pushButton_simulation->setStyleSheet("background-color: rgb(136, 136, 136)");
    ui->pushButton_Ready->setStyleSheet("background-color: rgb(136, 136, 136)");

    ControllerTabInit();
}



void DesktopMachineToolSystem::on_pushButton_clicked()
{
xenotest.show();
 //   foo();

}

void DesktopMachineToolSystem::on_pushButton_XMLGenerater_clicked()
{
}




void DesktopMachineToolSystem::on_lineEdit_MotionTime_textChanged(const QString &arg1)
{

    double TravelTime;
    TravelTime=ui->lineEdit_Loop->text().toDouble();
    TravelTime*=arg1.toDouble();
    ui->lineEdit_TravelTime->setText(QString::number(TravelTime));

}

void DesktopMachineToolSystem::on_lineEdit_Loop_textChanged(const QString &arg1)
{

    double TravelTime;
    TravelTime=ui->lineEdit_MotionTime->text().toDouble();
    TravelTime*=arg1.toDouble();
    ui->lineEdit_TravelTime->setText(QString::number(TravelTime));

}

void DesktopMachineToolSystem::on_pushButton_Start_clicked()
{
    ui->pushButton_Start->setStyleSheet("background-color: rgb(65, 65, 65)");

    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_StopControl->setStyleSheet("background-color:red");

    if (!(ui->radioButton_Experiment->isChecked()))SetParameter();

    emit Th1Emit((ui->radioButton_Experiment->isChecked()));

    /*
    if (ui->radioButton_Experiment->isChecked()){
        while(Th_main->isRunning()){
            QCoreApplication::processEvents();
            QThread::sleep(0.3);
        }
        ui->textBrowser->append("start Experiment");
        io.InitIOboard(0);
    }*/

}


void DesktopMachineToolSystem::SetParameter(){
    formgraphfunc.loadforminf(conparam,conparam2);
   return;
}

void DesktopMachineToolSystem::on_pushButton_DataDump_clicked()
{
    ExpeOutputFile datadumpFunc(*datalog);
    datadumpFunc.My_a1 = ui->lineEdit_spline_a1->text().toDouble();
    datadumpFunc.My_a2 = ui->lineEdit_spline_a2->text().toDouble();
    datadumpFunc.My_a3 = ui->lineEdit_spline_a3->text().toDouble();
    datadumpFunc.My_x1 = ui->lineEdit_spline_x1->text().toDouble();
    datadumpFunc.My_T = ui->lineEdit_spline_T->text().toDouble();

    std::string filename,filepath,path;
    unsigned int typeNo;
    bool energySim;
    if(ui->radioButton_Simulation->isChecked())
    typeNo = 0;
    else if(ui->radioButton_Experiment->isChecked())
    typeNo = 1;
    energySim = ui->checkBox_EnergyCalc->isChecked();
    filename = ui->lineEdit_filename_simulation->text().toStdString();
    filepath = ui->lineEdit_filepath_simulation->text().toStdString();


    unsigned long max_step;
    std::vector<double> para(28);
        para[0]= ui->lineEdit_Gcode_Sampling->text().toDouble()*0.001;
        para[1]= ui->lineEdit_Gcode_acctime->text().toDouble()*0.001;
        para[2]= ui->lineEdit_Gcode_loop->text().toDouble();
        if(ui->radioButton_Goption_default
                ->isChecked())para[3]= 0;
        else if(ui->radioButton_Goption_xaxis
                ->isChecked())para[3]=1;
        else if(ui->radioButton_Goption_yaxis
                ->isChecked())para[3]=2;
        else if(ui->radioButton_Goption_csvcheck
                ->isChecked())para[3]=3;
        std::string flag;
    flag = ui->comboBox_SelectTarget->currentText().toStdString();
    if (flag=="3 Axis Industrial Machine Tool System"){
        para[4]= ui->lineEditE_3axisMassX->text().toDouble();
        para[5]=ui->lineEditE_3axisViscoX->text().toDouble();
        para[6]=ui->lineEditE_3axisCoulombX->text().toDouble();
        para[7]=ui->lineEditE_3axisDistX->text().toDouble();
        para[8]= ui->lineEditE_3axisMassY->text().toDouble();
        para[9]=ui->lineEditE_3axisViscoY->text().toDouble();
        para[10]=ui->lineEditE_3axisCoulombY->text().toDouble();
        para[11]=ui->lineEditE_3axisDistY->text().toDouble();
        para[12]= ui->lineEditE_3axisMassZ->text().toDouble();
        para[13]=ui->lineEditE_3axisViscoZ->text().toDouble();
        para[14]=ui->lineEditE_3axisCoulombZ->text().toDouble();
        para[15]=ui->lineEditE_3axisDistZ->text().toDouble();
}
    else if (flag=="5 Axis Desktop Machine Tool System"){
        para[4]= ui->lineEditE_5axisMassX->text().toDouble();
        para[5]=ui->lineEditE_5axisViscoX->text().toDouble();
        para[6]=ui->lineEditE_5axisCoulombX->text().toDouble();
        para[7]=ui->lineEditE_5axisDistX->text().toDouble();
        para[8]= ui->lineEditE_5axisMassY->text().toDouble();
        para[9]=ui->lineEditE_5axisViscoY->text().toDouble();
        para[10]=ui->lineEditE_5axisCoulombY->text().toDouble();
        para[11]=ui->lineEditE_5axisDistY->text().toDouble();
        para[12]= ui->lineEditE_5axisMassZ->text().toDouble();
        para[13]=ui->lineEditE_5axisViscoZ->text().toDouble();
        para[14]=ui->lineEditE_5axisCoulombZ->text().toDouble();
        para[15]=ui->lineEditE_5axisDistZ->text().toDouble();}

    datadumpFunc.SetParameter(para);
    path =datadumpFunc.DataDumpfunc(&filename,&filepath,&typeNo,&energySim);
    ui2->xmlWriting(path);

    max_step = static_cast<unsigned long>
            (ui->lineEdit_MotionTime->text().toDouble() / define::SAMPLING_TIME);
    filename = ui->lineEdit_filename_gcode->text().toStdString();
    filepath = ui->lineEdit_filepath_gcode->text().toStdString();
    path = datadumpFunc.ModeSelect(1,filename,max_step,filepath);
    ui2->xmlWriting(path);
    ui->textBrowser->append("DataDump finished");
}

void DesktopMachineToolSystem::on_pushButton_simulation_clicked()
{

    double max_para,min_para,para;
/////////////////////trajectory///////////////////////////////////////
    int count = 0;
    double traveltime = ui->lineEdit_MotionTime->text().toDouble();
    double range[4] ={0,0.05,-0.05,0.05};
        ui->graph_tooltrajectory->clearGraphs();
    QString label[2] = {"X-Axis position[m]","Y-Axis position[m]"};

    int dataNum[2] = {10,18};
    this->DrawTrajectory(ui->graph_tooltrajectory,label
                    ,range,dataNum,0);
    std::vector<unsigned int> Graph1No,Graph2No,Graph3No,Graph1subNo,Graph2subNo,Graph3subNo;

formgraphfunc.loadGraphinf(Graph1No,Graph2No,Graph3No);
formgraphfunc.loadGraphsubinf(Graph1subNo,Graph2subNo,Graph3subNo);

std::vector<std::string> graph_label,graph_label2;
size_t Graph1size;

///////////////////////Graph1////////////////////////////////////
    max_para=0;min_para=0;
    ui->graph_Velocity->clearGraphs();
    graph_label = graph_labelFunc(Graph1No);
    graph_label2 = graph_labelFunc2(Graph1subNo);
    count = 0;
    for(QString i:{"time[sec]","velocity[m/s]"}){
        label[count] =i;
        count++;}
    range[0]=0;
    range[1]=traveltime;

    for(unsigned int j:Graph1No){
        //para = *std::max_element((*datalog)[j].begin(),(*datalog)[j].end());
        if(max_para<para)max_para=para;
        //para = *std::min_element((*datalog)[j].begin(),(*datalog)[j].end());
        if(min_para>para)min_para=para;
    }
    range[2]=min_para;
    range[3]=max_para;
    dataNum[0]=0;

    for(unsigned int i=0;i<Graph1No.size();i++){
        dataNum[1]=Graph1No[i];
        ui->graph_Velocity->addGraph();
        ui->graph_Velocity->graph(i)
                ->setName(QString::fromStdString(graph_label[i]));
        this->DrawGraph(ui->graph_Velocity,label
                        ,range,dataNum,i,0);
    }

    for(unsigned int i=0;i<Graph1subNo.size();i++){
        dataNum[1]=Graph1subNo[i];
        ui->graph_Velocity->addGraph();
        ui->graph_Velocity->graph(i+Graph1No.size())
                ->setName(QString::fromStdString(graph_label2[i]));
        this->DrawGraph(ui->graph_Velocity,label
                        ,range,dataNum,i+Graph1No.size(),1);
    }

    ui->graph_Velocity->yAxis->rescale(true);
    ui->graph_Velocity->replot();

/////////////////////////Graph2///////////////////////////////////////////////
    max_para=0;min_para=0;
    ui->graph_acceleration->clearGraphs();
    graph_label = graph_labelFunc(Graph2No);
    graph_label2 = graph_labelFunc2(Graph2subNo);
    count = 0;
    for(QString i:{"time[sec]","acceleration[m/s]"}){
        label[count] =i;
        count++;}
    range[0]=0;
    range[1]=traveltime;
    for(unsigned int j:Graph2No){
        //para = *std::max_element((*datalog)[j].begin(),(*datalog)[j].end());
        if(max_para<para)max_para=para;
        //para = *std::min_element((*datalog)[j].begin(),(*datalog)[j].end());
        if(min_para>para)min_para=para;
    }

    range[2]=min_para;
    range[3]=max_para;
    dataNum[0]=0;

    for(unsigned int i=0;i<Graph2No.size();i++){
        dataNum[1]=Graph2No[i];
    ui->graph_acceleration->addGraph();
    ui->graph_acceleration->graph(i)
            ->setName(QString::fromStdString(graph_label[i]));
    this->DrawGraph(ui->graph_acceleration,label
                    ,range,dataNum,i,0);
    }

    for(unsigned int i=0;i<Graph2subNo.size();i++){
        dataNum[1]=Graph2subNo[i];
        ui->graph_acceleration->addGraph();
        ui->graph_acceleration->graph(i+Graph2No.size())
                ->setName(QString::fromStdString(graph_label2[i]));
        this->DrawGraph(ui->graph_acceleration,label
                        ,range,dataNum,i+Graph2No.size(),1);
    }
    ui->graph_acceleration->yAxis->rescale(true);
    ui->graph_acceleration->replot();


////////////////////Graph3////////////////////////////////////////////////
max_para=0;min_para=0;
ui->graph_force->clearGraphs();
graph_label = graph_labelFunc(Graph3No);
graph_label2 = graph_labelFunc2(Graph3subNo);

count = 0;
for(QString i:{"time[sec]","acceleration[m/s]"}){
    label[count] =i;
    count++;}
range[0]=0;
range[1]=traveltime;
for(unsigned int j:Graph3No){
    //para = *std::max_element((*datalog)[j].begin(),(*datalog)[j].end());
    if(max_para<para)max_para=para;
    //para = *std::min_element((*datalog)[j].begin(),(*datalog)[j].end());
    if(min_para>para)min_para=para;
}

range[2]=min_para;
range[3]=max_para;
dataNum[0]=0;

for(unsigned int i=0;i<Graph3No.size();i++){
dataNum[1]=Graph3No[i];
ui->graph_force->addGraph();
ui->graph_force->graph(i)
    ->setName(QString::fromStdString(graph_label[i]));
this->DrawGraph(ui->graph_force,label
            ,range,dataNum,i,0);
}

for(unsigned int i=0;i<Graph3subNo.size();i++){
    dataNum[1]=Graph3subNo[i];
    ui->graph_force->addGraph();
    ui->graph_force->graph(i+Graph3No.size())
            ->setName(QString::fromStdString(graph_label2[i]));
    this->DrawGraph(ui->graph_force,label
                    ,range,dataNum,i+Graph3No.size(),1);
}

    ui->graph_force->yAxis->rescale(true);
    ui->graph_force->replot();


    ui->Maintab->tabBar()->currentChanged(4);
    ui->Maintab->tabBar()->setCurrentIndex(4);
}
void DesktopMachineToolSystem::DrawGraph(QCustomPlot *customPlot
                                         ,QString label[2]
                                         ,double range[4]
                                         ,int dataNum[2]
                                         ,int GraphNo
                                         ,int mode){
    (void)label;
    if(GraphNo==0){
    // create graph and assign data to it:

    customPlot->xAxis->setLabelFont(QFont("Times New Roman",14));
    customPlot->yAxis->setLabelFont(QFont("Times New Roman",14));
    customPlot->xAxis->setTickLabelFont(QFont("Times New Roman"));
    customPlot->yAxis->setTickLabelFont(QFont("Times New Roman"));
    // give the axes some labels:
    //customPlot->xAxis->setLabel(label[0]);
    //customPlot->yAxis->setLabel(label[1]);
    // set axes ranges, so we see all data:
    //customPlot->xAxis->setRange(range[0], range[1]);
    //customPlot->yAxis->setRange(range[2], range[3]);
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Times New Roman"));
}
    switch (GraphNo){
    case 0:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::red));
    break;
    case 1:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::blue));
    break;
    case 2:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::black));
    break;
    case 3:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::green));
    break;
    case 4:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::cyan));
    break;
    case 5:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::magenta));
    break;
    case 6:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::darkRed));
    break;
    case 7:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::darkGreen));
    break;
    case 8:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::darkBlue));
    break;
    case 9:
        customPlot->graph(GraphNo)->setPen(QPen(Qt::gray));
    break;
    }

    QVector<double> data_x,data_y;
    double max=0,min=0;
    unsigned int a = datalog->size2();
    data_x.resize(a);
    data_y.resize(a);
    for(unsigned int i = 0; i<a;i++){
        data_x[i]=(*datalog)(dataNum[0],i);
        if(mode==0){
        data_y[i]=(*datalog)(dataNum[1],i);}
        else if (mode == 1){
         data_y[i]=(*datalog2)(dataNum[1],i);
        }
    }
    customPlot->xAxis->setRange(range[0], range[1]);
    //data_x= QVector<double>::fromStdVector((*datalog)[dataNum[0]]);
    //data_y= QVector<double>::fromStdVector((*datalog)[dataNum[1]]);
    customPlot->graph(GraphNo)->setData(data_x, data_y);
    customPlot->replot();
}

void DesktopMachineToolSystem::DrawTrajectory(QCustomPlot *customPlot
                    ,QString label[2],double range[4],int dataNum[2],int GraphNo){
    (void)GraphNo;
    QVector<double> data_x,data_y;
    //data_x= QVector<double>::fromStdVector((*datalog)[dataNum[0]]);
    //data_y= QVector<double>::fromStdVector((*datalog)[dataNum[1]]);
    unsigned int a = datalog->size2();
    data_x.resize(a);
    data_y.resize(a);
    for(unsigned int i = 0; i<a;i++){
        data_x[i]=(*datalog)(dataNum[0],i);
        data_y[i]=(*datalog)(dataNum[1],i);
    }
    QCPCurve trajectory(customPlot->xAxis, customPlot->yAxis);
    trajectory.setData(data_x, data_y);
    customPlot->xAxis->setLabelFont(QFont("Times New Roman",14));
    customPlot->yAxis->setLabelFont(QFont("Times New Roman",14));
    customPlot->xAxis->setTickLabelFont(QFont("Times New Roman"));
    customPlot->yAxis->setTickLabelFont(QFont("Times New Roman"));

    customPlot->xAxis->setLabel(label[0]);
    customPlot->yAxis->setLabel(label[1]);
    customPlot->xAxis->setRange(range[0], range[1]);
    //customPlot->yAxis->setRange(range[2], range[3]);
    customPlot->replot();
}

void DesktopMachineToolSystem::on_pushButton_Openglsim_clicked()
{
    /*
        ptr_form2=true;
        if(bool(glutInit)){ ui->textBrowser->append("OpenGL GLUT Initialilization");
                            ui->textBrowser->append("Call opengl simulation window");
        }
        else ui->textBrowser->append("Warning OpenGL GLUT is not initialized");
*/
        y.reset(new openglwindow());

        y->ready(datalog);
}



void DesktopMachineToolSystem::on_pushButton_QuitMainwindow_clicked()
{
    y.reset();
    close();
}
DesktopMachineToolSystem::~DesktopMachineToolSystem()
{
    std::string path="config.xml";
    ui2->xmlWriting(path);
}


void DesktopMachineToolSystem::on_pushButton_OpenFolder_clicked()
{
    QString path = QCoreApplication::applicationDirPath();
    ui->textBrowser->append(path);
    //QDesktopServices::openUrl(QUrl(path+"/"));
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
   /* QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                |QFileDialog::DontResolveSymlinks);*/
}


void DesktopMachineToolSystem::on_pushButton_CreateFolder_clicked()
{
    QString exePath,targetpath;
    exePath =QCoreApplication::applicationDirPath();
    targetpath = exePath+"/outputfile";
    if (QDir(targetpath).exists())ui->textBrowser->append("exists outputfile folder");
else {
        QDir().mkdir(exePath+"/outputfile");
        QDir().mkdir(exePath+"/outputfile/Simulation");
        QDir().mkdir(exePath+"/outputfile/Experiment");
        QDir().mkdir(exePath+"/outputfile/Gcode");
        ui->textBrowser->append("create outputfile folder");
    }
}




std::vector<std::string> DesktopMachineToolSystem::graph_labelFunc
    (std::vector<unsigned int>graphNo){
std::vector<std::string> graph_label;
graph_label.clear();
for(unsigned int i=0;i<graphNo.size();i++){
    switch(graphNo[i]){
    case 11:
        graph_label.push_back("rvelX");
    break;
    case 12:
        graph_label.push_back("raccX");
    break;
    case 14:
        graph_label.push_back("velX");
    break;
    case 15:
        graph_label.push_back("accX");
    break;
    case 16:
        graph_label.push_back("forceX");
    break;
    case 17:
        graph_label.push_back("errorX");
    break;
    case 19:
        graph_label.push_back("rvelY1");
    break;
    case 20:
        graph_label.push_back("raccY1");
    break;
    case 22:
        graph_label.push_back("velY1");
    break;
    case 23:
        graph_label.push_back("accY1");
    break;
    case 24:
        graph_label.push_back("forceY1");
    break;
    case 25:
        graph_label.push_back("errorY1");
    break;
    case 27:
        graph_label.push_back("rvelY2");
    break;
    case 28:
        graph_label.push_back("raccY2");
    break;
    case 30:
        graph_label.push_back("velY2");
    break;
    case 31:
        graph_label.push_back("accY2");
    break;
    case 32:
        graph_label.push_back("forceY2");
    break;
    case 33:
        graph_label.push_back("errorY2");
    break;
    case 35:
        graph_label.push_back("rvelZ");
    break;
    case 36:
        graph_label.push_back("raccZ");
    break;
    case 38:
        graph_label.push_back("velZ");
    break;
    case 39:
        graph_label.push_back("accZ");
    break;
    case 40:
        graph_label.push_back("forceZ");
    break;
    case 41:
        graph_label.push_back("errorZ");
    break;
    case 43:
        graph_label.push_back("rvelC");
    break;
    case 44:
        graph_label.push_back("raccC");
    break;
    case 46:
        graph_label.push_back("velC");
    break;
    case 47:
        graph_label.push_back("accC");
    break;
    case 48:
        graph_label.push_back("torqueC");
    break;
    case 49:
        graph_label.push_back("errorC");
    break;
    case 51:
        graph_label.push_back("rvelA1");
    break;
    case 52:
        graph_label.push_back("raccA1");
    break;
    case 54:
        graph_label.push_back("velA1");
    break;
    case 55:
        graph_label.push_back("accA1");
    break;
    case 56:
        graph_label.push_back("torqueA1");
    break;
    case 57:
        graph_label.push_back("errorA1");
    break;
    case 59:
        graph_label.push_back("rvelA2");
    break;
    case 60:
        graph_label.push_back("raccA2");
    break;
    case 62:
        graph_label.push_back("velA2");
    break;
    case 63:
        graph_label.push_back("accA2");
    break;
    case 64:
        graph_label.push_back("torqueA2");
    break;
    case 65:
        graph_label.push_back("errorA2");
    break;
    }
}

return graph_label;
}




std::vector<std::string> DesktopMachineToolSystem::graph_labelFunc2
    (std::vector<unsigned int>graphNo){
std::vector<std::string> graph_label;
graph_label.clear();
for(unsigned int i=0;i<graphNo.size();i++){
    switch(graphNo[i]){
    case 0:
        graph_label.push_back("data1");
    break;
    case 1:
        graph_label.push_back("data2");
    break;
    case 2:
        graph_label.push_back("data3");
    break;
    case 3:
        graph_label.push_back("data4");
    break;
    case 4:
        graph_label.push_back("data5");
    break;
    case 5:
        graph_label.push_back("data6");
    break;
    case 6:
        graph_label.push_back("data7");
    break;
    case 7:
        graph_label.push_back("data8");
    break;
    }
}

return graph_label;
}


void DesktopMachineToolSystem::onValueChanged(QString text){
    ui->textBrowser->append(text);
    if(text=="finished"){
    if(ui->radioButton_Experiment->isChecked()){
        ui->pushButton_Ready->setEnabled(true);
        ui->pushButton_Ready->setStyleSheet("background-color:red");
    }
    else{
        ui->pushButton_Start->setEnabled(true);
        ui->pushButton_Start->setStyleSheet("background-color:red");
    }

    ui->pushButton_DataDump->setEnabled(true);
    ui->pushButton_Openglsim->setEnabled(true);
    ui->pushButton_StopControl->setStyleSheet("background-color: rgb(65, 65, 65)");
    ui->pushButton_DataDump->setStyleSheet("background-color: rgb(65, 65, 65)");
    ui->pushButton_Openglsim->setStyleSheet("background-color: rgb(65, 65, 65)");

    ui->pushButton_simulation->setStyleSheet("background-color: rgb(65, 65, 65)");
    ui->radioButton_Simulation->setStyleSheet("color:white");
    ui->radioButton_Simulation->setEnabled(true);

    ui->radioButton_Experiment->setStyleSheet("background-color: rgb(65, 65, 65)");

    on_pushButton_Openglsim_clicked();
    }

}
void DesktopMachineToolSystem::ThreadQuit(){
}
void DesktopMachineToolSystem::DrawGraphS(){

    double t1 = ui->lineEdit_spline_t1->text().toDouble();
    double sampling=define::SAMPLING_TIME;
    unsigned int max_step = (t1*2)/sampling;
    QVector<double> data_x,data_y,data_y2;
    data_x.resize(max_step);
    data_y.resize(max_step);
    data_y.resize(max_step);
    data_x[0] = 0;
    /*
    for (unsigned int i = 1;i<max_step ; i++){
        data_x[i] = data_x[i-1]+sampling;
    }
    for (unsigned int i=0;i<t1;i+=sampling){
        data_y=0;
    }
    for (unsigned int i=t1;i<t1*2;i+=sampling){
        data_y=1;
    }
    data_y2=data_y;
    for(unsigned int i = 0.5*t1/sampling;i<1.5*t1/sampling;i++){

        data_y2[i]=0;//t1で移動平均フィルタ
    }
    */
}

void DesktopMachineToolSystem::on_pushButton_StopControl_clicked()
{
    io.ExitIOboard();
    ui->pushButton_Start->setEnabled(true);
    ui->pushButton_DataDump->setEnabled(true);
    ui->pushButton_Openglsim->setEnabled(true);

    ui->pushButton_simulation->setStyleSheet("background-color: rgb(65, 65, 65)");
    ui->radioButton_Simulation->setStyleSheet("color:white");
    ui->radioButton_Simulation->setEnabled(true);

    ui->radioButton_Experiment->setStyleSheet("background-color: rgb(65, 65, 65)");

    on_pushButton_Openglsim_clicked();
}

void DesktopMachineToolSystem::on_pushButton_Ready_clicked()
{
    ui->pushButton_Ready->setStyleSheet("background-color: rgb(65, 65, 65)");
    ui->pushButton_Ready->setEnabled(false);

    ui->pushButton_Start->setStyleSheet("background-color:red");
    ui->pushButton_Start->setEnabled(true);

    ui->radioButton_Simulation->setStyleSheet("color:rgb(65, 65, 65)");
    ui->radioButton_Simulation->setEnabled(false);

    ui->radioButton_Experiment->setStyleSheet("background-color:red");

    SetParameter();

    //emit Th1Emit((ui->radioButton_Experiment->isChecked()));
}

void DesktopMachineToolSystem::on_radioButton_Experiment_clicked(bool checked)
{
    if(checked == true){
        ui->pushButton_Start->setStyleSheet("background-color: rgb(65, 65, 65)");
        ui->pushButton_Start->setEnabled(false);

        ui->pushButton_Ready->setStyleSheet("background-color:red");
        ui->pushButton_Ready->setEnabled(true);
    }
}

void DesktopMachineToolSystem::on_radioButton_Simulation_clicked(bool checked)
{
    if(checked == true){
        ui->pushButton_Ready->setStyleSheet("background-color: rgb(65, 65, 65)");
        ui->pushButton_Ready->setEnabled(false);

        ui->pushButton_Start->setStyleSheet("background-color:red");
        ui->pushButton_Start->setEnabled(true);

    }
}

void DesktopMachineToolSystem::AdaptiveParaUpdate(const QString & text)
{
    double d,n,nb,nf,nd,m,nc,nr,np,nq,ns;
    d = ui->lineEdit_AdaCon_d_X->text().toDouble();
    n = ui->lineEdit_AdaCon_n_X->text().toDouble();
    nb = ui->lineEdit_AdaCon_nb_X->text().toDouble();
    nf = ui->lineEdit_AdaCon_nf_X->text().toDouble();
    nd = ui->lineEdit_AdaCon_nd_X->text().toDouble();
    m = ui->lineEdit_AdaCon_m_X->text().toDouble();
    nc = ui->lineEdit_AdaCon_nc_X->text().toDouble();

    nr = m+d-1;
    np = nb+nd+nr;

    if(nf-1<=nc-m-d)nq = nc-m-d;
    else            nq = nf-1;

    if(n+nd-1<=nc-m-d)ns = nc-m-d;
    else            ns = n+nd-1;

    ui->lineEdit_AdaCon_nr_X->setText(QString::number(nr));
    ui->lineEdit_AdaCon_np_X->setText(QString::number(np));
    ui->lineEdit_AdaCon_nq_X->setText(QString::number(nq));
    ui->lineEdit_AdaCon_ns_X->setText(QString::number(ns));



    d = ui->lineEdit_AdaCon_d_Y1->text().toDouble();
    n = ui->lineEdit_AdaCon_n_Y1->text().toDouble();
    nb = ui->lineEdit_AdaCon_nb_Y1->text().toDouble();
    nf = ui->lineEdit_AdaCon_nf_Y1->text().toDouble();
    nd = ui->lineEdit_AdaCon_nd_Y1->text().toDouble();
    m = ui->lineEdit_AdaCon_m_Y1->text().toDouble();
    nc = ui->lineEdit_AdaCon_nc_Y1->text().toDouble();

    nr = m+d-1;
    np = nb+nd+nr;

    if(nf-1<=nc-m-d)nq = nc-m-d;
    else            nq = nf-1;

    if(n+nd-1<=nc-m-d)ns = nc-m-d;
    else            ns = n+nd-1;

    ui->lineEdit_AdaCon_nr_Y1->setText(QString::number(nr));
    ui->lineEdit_AdaCon_np_Y1->setText(QString::number(np));
    ui->lineEdit_AdaCon_nq_Y1->setText(QString::number(nq));
    ui->lineEdit_AdaCon_ns_Y1->setText(QString::number(ns));

}


void DesktopMachineToolSystem::ControllerTabInit()
{
    connectAdapupdate(ui->lineEdit_AdaCon_L0_X);
    connectAdapupdate(ui->lineEdit_AdaCon_L1_X);
    connectAdapupdate(ui->lineEdit_AdaCon_L2_X);
    connectAdapupdate(ui->lineEdit_AdaCon_d_X);
    connectAdapupdate(ui->lineEdit_AdaCon_n_X);
    connectAdapupdate(ui->lineEdit_AdaCon_nb_X);
    connectAdapupdate(ui->lineEdit_AdaCon_nf_X);
    connectAdapupdate(ui->lineEdit_AdaCon_nd_X);
    connectAdapupdate(ui->lineEdit_AdaCon_m_X);
    connectAdapupdate(ui->lineEdit_AdaCon_nc_X);

    connectAdapupdate(ui->lineEdit_AdaCon_L0_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_L1_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_L2_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_d_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_n_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_nb_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_nf_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_nd_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_m_Y1);
    connectAdapupdate(ui->lineEdit_AdaCon_nc_Y1);


//QLineEdit *
}
void DesktopMachineToolSystem::connectAdapupdate(QLineEdit *boxname)
{
    connect(boxname,SIGNAL(textChanged(const QString &)),this,SLOT(AdaptiveParaUpdate(const QString & )));

}
