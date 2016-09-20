#include "FormGraphFunction.h"
#include <ui_desktopmachinetoolsystem.h>
#include <vector>
#include "define.h"
#include <boost/preprocessor.hpp>




FormGraphFunction::FormGraphFunction()
{

}

void FormGraphFunction::loadforminf(std::vector<double> &conparam
                               ,std::vector<double> &conparam2)
{
    conparam = setParam1();
    conparam2 = setParam2();
}

std::vector<double> FormGraphFunction::setParam1(){
    std::vector<double> conparam;
        conparam.clear();
        conparam.resize(29);
    conparam[0]=ui->lineEdit_MassX->text().toDouble();//0
    conparam[1]=ui->lineEdit_MassY1->text().toDouble();//1
    conparam[2]=ui->lineEdit_MassY2->text().toDouble();//2
    conparam[3]=ui->lineEdit_MassZ->text().toDouble();//3
    conparam[4]=ui->lineEdit_MassC->text().toDouble();//4
    conparam[5]=ui->lineEdit_MassA1->text().toDouble();//5
    conparam[6]=ui->lineEdit_MassA2->text().toDouble();//6
    conparam[7]=ui->lineEdit_FrictionX->text().toDouble();//7
    conparam[8]=ui->lineEdit_FrictionY1->text().toDouble();//8
    conparam[9]=ui->lineEdit_FrictionY2->text().toDouble();//9
    conparam[10]=ui->lineEdit_FrictionZ->text().toDouble();//10
 //////////////////////////////////////////////////////////////////////////////////
    conparam[11]=ui->lineEdit_FrictionC->text().toDouble();//11
    conparam[12]=ui->lineEdit_FrictionA1->text().toDouble();//12
    conparam[13]=ui->lineEdit_FrictionA2->text().toDouble();//13
    conparam[14]=ui->lineEdit_PoleX->text().toDouble();//14
    conparam[15]=ui->lineEdit_PoleY1->text().toDouble();//15
    conparam[16]=ui->lineEdit_PoleY2->text().toDouble();//16
    conparam[17]=ui->lineEdit_PoleZ->text().toDouble();//17
    conparam[18]=ui->lineEdit_PoleC->text().toDouble();//18
    conparam[19]=ui->lineEdit_PoleA1->text().toDouble();//19
    conparam[20]=ui->lineEdit_PoleA2->text().toDouble();//20
//////////////////////////////////////////////////////////////////////////////
   conparam[21]=ui->lineEdit_Contouring_PoleT->text().toDouble();//21
   conparam[22]=ui->lineEdit_Contouring_PoleN->text().toDouble();//22
   conparam[23]=ui->lineEdit_Contouring_PoleB->text().toDouble();//23
   conparam[24]=ui->lineEdit_Contouring_PoleI->text().toDouble();//24
   conparam[25]=ui->lineEdit_Contouring_PoleJ->text().toDouble();//25
   conparam[26]=ui->lineEdit_Contouring_PoleK->text().toDouble();//26
   conparam[27]=ui->lineEdit_SyncPoleY->text().toDouble();//27
   conparam[28]=ui->lineEdit_SyncPoleA->text().toDouble();//28

   return conparam;
}

std::vector<double> FormGraphFunction::setParam2(){
    std::vector<double> conparam2;
    conparam2.clear();
    conparam2.resize(44);

    conparam2[0]=ui->lineEdit_spline_L->text().toDouble();//0
    conparam2[1]=ui->lineEdit_spline_T->text().toDouble();//1
    conparam2[2]=ui->lineEdit_spline_t1->text().toDouble();//2
    conparam2[3]=ui->lineEdit_spline_a1->text().toDouble();//3
    conparam2[4]=ui->lineEdit_spline_a2->text().toDouble();//4
    conparam2[5]=ui->lineEdit_spline_a3->text().toDouble();//5
    conparam2[6]=ui->lineEdit_spline_x0->text().toDouble();//6
    conparam2[7]=ui->lineEdit_spline_x1->text().toDouble();//7
    conparam2[8]=ui->lineEdit_spline_velopt->text().toDouble();//8
    QString currentText;
    currentText = ui->comboBox_SplineModeSelect->currentText();

     if(currentText=="Toolvel")               conparam2[9]=0.0;
     else if (currentText=="Xaxisvel")        conparam2[9]=1.0;
     else if (currentText=="Yaxisvel")        conparam2[9]=2.0;
     else if (currentText=="Curve_Xaxisvel")  conparam2[9]=3.0;
     else if (currentText=="Matlab code")     conparam2[9]=4.0;
     else {ui->textBrowser->append("cannnot select Velocity Tyepe");}

     conparam2[10]=ui->lineEdit_Motion_rotationAngle->text().toDouble();//10

     if(ui->radioButton_IndependentCon->isChecked())         conparam2[11]=0;
     else if(ui->radioButton_ContouringCon->isChecked())     conparam2[11]=1.0;
     else if(ui->radioButton_modContouringCon->isChecked())  conparam2[11]=2.0;
     else if(ui->radioButton_adaptiveCon->isChecked())      conparam2[11]=3.0;
     else if(ui->radioButton_adaContouringCon->isChecked()) conparam2[11]=4.0;
     else if(ui->radioButton_adamodContouringCon->isChecked()) conparam2[11]=5.0;
     else if(ui->radioButton_adaptiveCon_2->isChecked()) conparam2[11]=6.0;

     else {ui->textBrowser->append("cannnot select Velocity Tyepe");}


     if(ui->radioButton_Simulation->isChecked())             conparam2[12]=1.0;//12
     else if (ui->radioButton_Experiment->isChecked())       conparam2[12]=2.0;//12
     else ui->textBrowser->append("cannnot select Work");


     if(ui->radioButton_2D3DOF->isChecked())                 conparam2[13]=(2.0);//13
     else if(ui->radioButton_3D7DOF->isChecked())            conparam2[13]=(3.0);//13
     else ui->textBrowser->append("cannot select DOF");

     conparam2[14]
             = ui->lineEdit_MotionTime->text().toDouble() / define::SAMPLING_TIME;//14max_step

     if(ui->checkBox_NoiseEnabled->isChecked())              conparam2[15]=1.0;
     else                                                    conparam2[15]=0;

     conparam2[16] = ui->lineEdit_AdaCon_L0_X->text().toDouble();
     conparam2[17] = ui->lineEdit_AdaCon_L1_X->text().toDouble();
     conparam2[18] = ui->lineEdit_AdaCon_L2_X->text().toDouble();
     conparam2[19] = ui->lineEdit_AdaCon_d_X->text().toDouble();
     conparam2[20] = ui->lineEdit_AdaCon_n_X->text().toDouble();
     conparam2[21] = ui->lineEdit_AdaCon_nb_X->text().toDouble();
     conparam2[22] = ui->lineEdit_AdaCon_nf_X->text().toDouble();
     conparam2[23] = ui->lineEdit_AdaCon_nd_X->text().toDouble();
     conparam2[24] = ui->lineEdit_AdaCon_m_X->text().toDouble();
     conparam2[25] = ui->lineEdit_AdaCon_nc_X->text().toDouble();
     conparam2[26] = ui->lineEdit_AdaCon_nr_X->text().toDouble();
     conparam2[27] = ui->lineEdit_AdaCon_np_X->text().toDouble();
     conparam2[28] = ui->lineEdit_AdaCon_nq_X->text().toDouble();
     conparam2[29] = ui->lineEdit_AdaCon_ns_X->text().toDouble();

     conparam2[30] = ui->lineEdit_AdaCon_L0_Y1->text().toDouble();
     conparam2[31] = ui->lineEdit_AdaCon_L1_Y1->text().toDouble();
     conparam2[32] = ui->lineEdit_AdaCon_L2_Y1->text().toDouble();
     conparam2[33] = ui->lineEdit_AdaCon_d_Y1->text().toDouble();
     conparam2[34] = ui->lineEdit_AdaCon_n_Y1->text().toDouble();
     conparam2[35] = ui->lineEdit_AdaCon_nb_Y1->text().toDouble();
     conparam2[36] = ui->lineEdit_AdaCon_nf_Y1->text().toDouble();
     conparam2[37] = ui->lineEdit_AdaCon_nd_Y1->text().toDouble();
     conparam2[38] = ui->lineEdit_AdaCon_m_Y1->text().toDouble();
     conparam2[39] = ui->lineEdit_AdaCon_nc_Y1->text().toDouble();
     conparam2[40] = ui->lineEdit_AdaCon_nr_Y1->text().toDouble();
     conparam2[41] = ui->lineEdit_AdaCon_np_Y1->text().toDouble();
     conparam2[42] = ui->lineEdit_AdaCon_nq_Y1->text().toDouble();
     conparam2[43] = ui->lineEdit_AdaCon_ns_Y1->text().toDouble();


    return conparam2;
}

void FormGraphFunction::loadGraphinf(std::vector<unsigned int> &Graph1
                 , std::vector<unsigned int> &Graph2
                  , std::vector<unsigned int> &Graph3){

    Graph1 = setGraph1Param();
    Graph2 = setGraph2Param();
    Graph3 = setGraph3Param();

}

void FormGraphFunction::loadGraphsubinf(std::vector<unsigned int> &Graph1
                 , std::vector<unsigned int> &Graph2
                  , std::vector<unsigned int> &Graph3){

    Graph1 = setGraph1subParam();
    Graph2 = setGraph2subParam();
    Graph3 = setGraph3subParam();

}



std::vector<unsigned int> FormGraphFunction::setGraph1Param(){


    std::vector<unsigned int> Graph1No;
        Graph1No.clear();


        if(ui->checkBox_sim_velpX->isChecked())Graph1No.push_back(11);
        if(ui->checkBox_sim_velpY1->isChecked())Graph1No.push_back(19);
        if(ui->checkBox_sim_velpY2->isChecked())Graph1No.push_back(27);
        if(ui->checkBox_sim_velpZ->isChecked())Graph1No.push_back(35);
        if(ui->checkBox_sim_velpC->isChecked())Graph1No.push_back(43);
        if(ui->checkBox_sim_velpA1->isChecked())Graph1No.push_back(51);
        if(ui->checkBox_sim_velpA2->isChecked())Graph1No.push_back(59);
        if(ui->checkBox_sim_velrX->isChecked())Graph1No.push_back(14);
        if(ui->checkBox_sim_velrY1->isChecked())Graph1No.push_back(22);
        if(ui->checkBox_sim_velrY2->isChecked())Graph1No.push_back(30);
        if(ui->checkBox_sim_velrZ->isChecked())Graph1No.push_back(38);
        if(ui->checkBox_sim_velrC->isChecked())Graph1No.push_back(46);
        if(ui->checkBox_sim_velrA1->isChecked())Graph1No.push_back(54);
        if(ui->checkBox_sim_velrA2->isChecked())Graph1No.push_back(62);
        if(ui->checkBox_sim_accpX->isChecked())Graph1No.push_back(12);
        if(ui->checkBox_sim_accpY1->isChecked())Graph1No.push_back(20);
        if(ui->checkBox_sim_accpY2->isChecked())Graph1No.push_back(28);
        if(ui->checkBox_sim_accpZ->isChecked())Graph1No.push_back(36);
        if(ui->checkBox_sim_accpC->isChecked())Graph1No.push_back(44);
        if(ui->checkBox_sim_accpA1->isChecked())Graph1No.push_back(52);
        if(ui->checkBox_sim_accpA2->isChecked())Graph1No.push_back(60);
        if(ui->checkBox_sim_accrX->isChecked())Graph1No.push_back(15);
        if(ui->checkBox_sim_accrY1->isChecked())Graph1No.push_back(23);
        if(ui->checkBox_sim_accrY2->isChecked())Graph1No.push_back(31);
        if(ui->checkBox_sim_accrZ->isChecked())Graph1No.push_back(39);
        if(ui->checkBox_sim_accrC->isChecked())Graph1No.push_back(47);
        if(ui->checkBox_sim_accrA1->isChecked())Graph1No.push_back(55);
        if(ui->checkBox_sim_accrA2->isChecked())Graph1No.push_back(63);
        if(ui->checkBox_sim_forcepX->isChecked())Graph1No.push_back(16);
        if(ui->checkBox_sim_forcepY1->isChecked())Graph1No.push_back(24);
        if(ui->checkBox_sim_forcepY2->isChecked())Graph1No.push_back(32);
        if(ui->checkBox_sim_forcepZ->isChecked())Graph1No.push_back(40);
        if(ui->checkBox_sim_forcepC->isChecked())Graph1No.push_back(48);
        if(ui->checkBox_sim_forcepA1->isChecked())Graph1No.push_back(56);
        if(ui->checkBox_sim_forcepA2->isChecked())Graph1No.push_back(64);
        if(ui->checkBox_sim_forcerX->isChecked())Graph1No.push_back(16);
        if(ui->checkBox_sim_forcerY1->isChecked())Graph1No.push_back(24);
        if(ui->checkBox_sim_forcerY2->isChecked())Graph1No.push_back(32);
        if(ui->checkBox_sim_forcerZ->isChecked())Graph1No.push_back(40);
        if(ui->checkBox_sim_forcerC->isChecked())Graph1No.push_back(48);
        if(ui->checkBox_sim_forcerA1->isChecked())Graph1No.push_back(56);
        if(ui->checkBox_sim_forcerA2->isChecked())Graph1No.push_back(64);
        if(ui->checkBox_sim_ErrorrX->isChecked())Graph1No.push_back(17);
        if(ui->checkBox_sim_ErrorrY1->isChecked())Graph1No.push_back(25);
        if(ui->checkBox_sim_ErrorrY2->isChecked())Graph1No.push_back(33);
        if(ui->checkBox_sim_ErrorrZ->isChecked())Graph1No.push_back(41);
        if(ui->checkBox_sim_ErrorrC->isChecked())Graph1No.push_back(49);
        if(ui->checkBox_sim_ErrorrA1->isChecked())Graph1No.push_back(57);
        if(ui->checkBox_sim_ErrorrA2->isChecked())Graph1No.push_back(65);

        return Graph1No;
}
std::vector<unsigned int> FormGraphFunction::setGraph2Param(){
    std::vector<unsigned int> Graph2No;
        Graph2No.clear();


        if(ui->checkBox_sim_velpX_2->isChecked())Graph2No.push_back(11);
        if(ui->checkBox_sim_velpY1_2->isChecked())Graph2No.push_back(19);
        if(ui->checkBox_sim_velpY2_2->isChecked())Graph2No.push_back(27);
        if(ui->checkBox_sim_velpZ_2->isChecked())Graph2No.push_back(35);
        if(ui->checkBox_sim_velpC_2->isChecked())Graph2No.push_back(43);
        if(ui->checkBox_sim_velpA1_2->isChecked())Graph2No.push_back(51);
        if(ui->checkBox_sim_velpA2_2->isChecked())Graph2No.push_back(59);
        if(ui->checkBox_sim_velrX_2->isChecked())Graph2No.push_back(14);
        if(ui->checkBox_sim_velrY1_2->isChecked())Graph2No.push_back(22);
        if(ui->checkBox_sim_velrY2_2->isChecked())Graph2No.push_back(30);
        if(ui->checkBox_sim_velrZ_2->isChecked())Graph2No.push_back(38);
        if(ui->checkBox_sim_velrC_2->isChecked())Graph2No.push_back(46);
        if(ui->checkBox_sim_velrA1_2->isChecked())Graph2No.push_back(54);
        if(ui->checkBox_sim_velrA2_2->isChecked())Graph2No.push_back(62);
        if(ui->checkBox_sim_accpX_2->isChecked())Graph2No.push_back(12);
        if(ui->checkBox_sim_accpY1_2->isChecked())Graph2No.push_back(20);
        if(ui->checkBox_sim_accpY2_2->isChecked())Graph2No.push_back(28);
        if(ui->checkBox_sim_accpZ_2->isChecked())Graph2No.push_back(36);
        if(ui->checkBox_sim_accpC_2->isChecked())Graph2No.push_back(44);
        if(ui->checkBox_sim_accpA1_2->isChecked())Graph2No.push_back(52);
        if(ui->checkBox_sim_accpA2_2->isChecked())Graph2No.push_back(60);
        if(ui->checkBox_sim_accrX_2->isChecked())Graph2No.push_back(15);
        if(ui->checkBox_sim_accrY1_2->isChecked())Graph2No.push_back(23);
        if(ui->checkBox_sim_accrY2_2->isChecked())Graph2No.push_back(31);
        if(ui->checkBox_sim_accrZ_2->isChecked())Graph2No.push_back(39);
        if(ui->checkBox_sim_accrC_2->isChecked())Graph2No.push_back(47);
        if(ui->checkBox_sim_accrA1_2->isChecked())Graph2No.push_back(55);
        if(ui->checkBox_sim_accrA2_2->isChecked())Graph2No.push_back(63);
        if(ui->checkBox_sim_forcepX_2->isChecked())Graph2No.push_back(16);
        if(ui->checkBox_sim_forcepY1_2->isChecked())Graph2No.push_back(24);
        if(ui->checkBox_sim_forcepY2_2->isChecked())Graph2No.push_back(32);
        if(ui->checkBox_sim_forcepZ_2->isChecked())Graph2No.push_back(40);
        if(ui->checkBox_sim_forcepC_2->isChecked())Graph2No.push_back(48);
        if(ui->checkBox_sim_forcepA1_2->isChecked())Graph2No.push_back(56);
        if(ui->checkBox_sim_forcepA2_2->isChecked())Graph2No.push_back(64);
        if(ui->checkBox_sim_forcerX_2->isChecked())Graph2No.push_back(16);
        if(ui->checkBox_sim_forcerY1_2->isChecked())Graph2No.push_back(24);
        if(ui->checkBox_sim_forcerY2_2->isChecked())Graph2No.push_back(32);
        if(ui->checkBox_sim_forcerZ_2->isChecked())Graph2No.push_back(40);
        if(ui->checkBox_sim_forcerC_2->isChecked())Graph2No.push_back(48);
        if(ui->checkBox_sim_forcerA1_2->isChecked())Graph2No.push_back(56);
        if(ui->checkBox_sim_forcerA2_2->isChecked())Graph2No.push_back(64);
        if(ui->checkBox_sim_ErrorrX_2->isChecked())Graph2No.push_back(17);
        if(ui->checkBox_sim_ErrorrY1_2->isChecked())Graph2No.push_back(25);
        if(ui->checkBox_sim_ErrorrY2_2->isChecked())Graph2No.push_back(33);
        if(ui->checkBox_sim_ErrorrZ_2->isChecked())Graph2No.push_back(41);
        if(ui->checkBox_sim_ErrorrC_2->isChecked())Graph2No.push_back(49);
        if(ui->checkBox_sim_ErrorrA1_2->isChecked())Graph2No.push_back(57);
        if(ui->checkBox_sim_ErrorrA2_2->isChecked())Graph2No.push_back(65);
        return Graph2No;
}


std::vector<unsigned int> FormGraphFunction::setGraph3Param(){
    std::vector<unsigned int> Graph3No;
        Graph3No.clear();

        if(ui->checkBox_sim_velpX_3->isChecked())Graph3No.push_back(11);
        if(ui->checkBox_sim_velpY1_3->isChecked())Graph3No.push_back(19);
        if(ui->checkBox_sim_velpY2_3->isChecked())Graph3No.push_back(27);
        if(ui->checkBox_sim_velpZ_3->isChecked())Graph3No.push_back(35);
        if(ui->checkBox_sim_velpC_3->isChecked())Graph3No.push_back(43);
        if(ui->checkBox_sim_velpA1_3->isChecked())Graph3No.push_back(51);
        if(ui->checkBox_sim_velpA2_3->isChecked())Graph3No.push_back(59);
        if(ui->checkBox_sim_velrX_3->isChecked())Graph3No.push_back(14);
        if(ui->checkBox_sim_velrY1_3->isChecked())Graph3No.push_back(22);
        if(ui->checkBox_sim_velrY2_3->isChecked())Graph3No.push_back(30);
        if(ui->checkBox_sim_velrZ_3->isChecked())Graph3No.push_back(38);
        if(ui->checkBox_sim_velrC_3->isChecked())Graph3No.push_back(46);
        if(ui->checkBox_sim_velrA1_3->isChecked())Graph3No.push_back(54);
        if(ui->checkBox_sim_velrA2_3->isChecked())Graph3No.push_back(62);
        if(ui->checkBox_sim_accpX_3->isChecked())Graph3No.push_back(12);
        if(ui->checkBox_sim_accpY1_3->isChecked())Graph3No.push_back(20);
        if(ui->checkBox_sim_accpY2_3->isChecked())Graph3No.push_back(28);
        if(ui->checkBox_sim_accpZ_3->isChecked())Graph3No.push_back(36);
        if(ui->checkBox_sim_accpC_3->isChecked())Graph3No.push_back(44);
        if(ui->checkBox_sim_accpA1_3->isChecked())Graph3No.push_back(52);
        if(ui->checkBox_sim_accpA2_3->isChecked())Graph3No.push_back(60);
        if(ui->checkBox_sim_accrX_3->isChecked())Graph3No.push_back(15);
        if(ui->checkBox_sim_accrY1_3->isChecked())Graph3No.push_back(23);
        if(ui->checkBox_sim_accrY2_3->isChecked())Graph3No.push_back(31);
        if(ui->checkBox_sim_accrZ_3->isChecked())Graph3No.push_back(39);
        if(ui->checkBox_sim_accrC_3->isChecked())Graph3No.push_back(47);
        if(ui->checkBox_sim_accrA1_3->isChecked())Graph3No.push_back(55);
        if(ui->checkBox_sim_accrA2_3->isChecked())Graph3No.push_back(63);
        if(ui->checkBox_sim_forcepX_3->isChecked())Graph3No.push_back(16);
        if(ui->checkBox_sim_forcepY1_3->isChecked())Graph3No.push_back(24);
        if(ui->checkBox_sim_forcepY2_3->isChecked())Graph3No.push_back(32);
        if(ui->checkBox_sim_forcepZ_3->isChecked())Graph3No.push_back(40);
        if(ui->checkBox_sim_forcepC_3->isChecked())Graph3No.push_back(48);
        if(ui->checkBox_sim_forcepA1_3->isChecked())Graph3No.push_back(56);
        if(ui->checkBox_sim_forcepA2_3->isChecked())Graph3No.push_back(64);
        if(ui->checkBox_sim_forcerX_3->isChecked())Graph3No.push_back(16);
        if(ui->checkBox_sim_forcerY1_3->isChecked())Graph3No.push_back(24);
        if(ui->checkBox_sim_forcerY2_3->isChecked())Graph3No.push_back(32);
        if(ui->checkBox_sim_forcerZ_3->isChecked())Graph3No.push_back(40);
        if(ui->checkBox_sim_forcerC_3->isChecked())Graph3No.push_back(48);
        if(ui->checkBox_sim_forcerA1_3->isChecked())Graph3No.push_back(56);
        if(ui->checkBox_sim_forcerA2_3->isChecked())Graph3No.push_back(64);
        if(ui->checkBox_sim_ErrorrX_3->isChecked())Graph3No.push_back(17);
        if(ui->checkBox_sim_ErrorrY1_3->isChecked())Graph3No.push_back(25);
        if(ui->checkBox_sim_ErrorrY2_3->isChecked())Graph3No.push_back(33);
        if(ui->checkBox_sim_ErrorrZ_3->isChecked())Graph3No.push_back(41);
        if(ui->checkBox_sim_ErrorrC_3->isChecked())Graph3No.push_back(49);
        if(ui->checkBox_sim_ErrorrA1_3->isChecked())Graph3No.push_back(57);
        if(ui->checkBox_sim_ErrorrA2_3->isChecked())Graph3No.push_back(65);

        return Graph3No;
}


std::vector<unsigned int> FormGraphFunction::setGraph1subParam(){
        std::vector<unsigned int> Graph1subNo;
            Graph1subNo.clear();

            if(ui->checkBox_Graph1_data1->isChecked())Graph1subNo.push_back(0);
            if(ui->checkBox_Graph1_data2->isChecked())Graph1subNo.push_back(1);
            if(ui->checkBox_Graph1_data3->isChecked())Graph1subNo.push_back(2);
            if(ui->checkBox_Graph1_data4->isChecked())Graph1subNo.push_back(3);
            if(ui->checkBox_Graph1_data5->isChecked())Graph1subNo.push_back(4);
            if(ui->checkBox_Graph1_data6->isChecked())Graph1subNo.push_back(5);
            if(ui->checkBox_Graph1_data7->isChecked())Graph1subNo.push_back(6);

            return Graph1subNo;
}
std::vector<unsigned int> FormGraphFunction::setGraph2subParam(){
        std::vector<unsigned int> Graph2subNo;
        Graph2subNo.clear();

        if(ui->checkBox_Graph2_data1->isChecked())Graph2subNo.push_back(0);
        if(ui->checkBox_Graph2_data2->isChecked())Graph2subNo.push_back(1);
        if(ui->checkBox_Graph2_data3->isChecked())Graph2subNo.push_back(2);
        if(ui->checkBox_Graph2_data4->isChecked())Graph2subNo.push_back(3);
        if(ui->checkBox_Graph2_data5->isChecked())Graph2subNo.push_back(4);
        if(ui->checkBox_Graph2_data6->isChecked())Graph2subNo.push_back(5);
        if(ui->checkBox_Graph2_data7->isChecked())Graph2subNo.push_back(6);

            return Graph2subNo;
}
std::vector<unsigned int> FormGraphFunction::setGraph3subParam(){
        std::vector<unsigned int> Graph3subNo;
        Graph3subNo.clear();

        if(ui->checkBox_Graph3_data1->isChecked())Graph3subNo.push_back(0);
        if(ui->checkBox_Graph3_data2->isChecked())Graph3subNo.push_back(1);
        if(ui->checkBox_Graph3_data3->isChecked())Graph3subNo.push_back(2);
        if(ui->checkBox_Graph3_data4->isChecked())Graph3subNo.push_back(3);
        if(ui->checkBox_Graph3_data5->isChecked())Graph3subNo.push_back(4);
        if(ui->checkBox_Graph3_data6->isChecked())Graph3subNo.push_back(5);
        if(ui->checkBox_Graph3_data7->isChecked())Graph3subNo.push_back(6);
            return Graph3subNo;
}
