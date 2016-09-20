#include "stdafx.h"
#include "form_tool.h"
#include <QMainWindow>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <ui_desktopmachinetoolsystem.h>
form_tool::form_tool()
{

}
form_tool::form_tool(Ui::DesktopMachineToolSystem *ui){
    this->myUi = ui;
}


void form_tool::xmlLoading(){
    // xml parser 5axis programing <------> MATLAB
    boost::property_tree::ptree Tree;
    boost::property_tree::read_xml("config.xml", Tree);

    bool loading = true;
    //this->nepuko();
    myUi->textBrowser->setFontPointSize(12);

    for (auto& child : Tree.get_child("MachineParameter.General"))
    {
        if (child.first == "Xaxis"){myUi->lineEdit_PoleX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "Y1axis"){myUi->lineEdit_PoleY1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassY1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionY1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "Y2axis"){myUi->lineEdit_PoleY2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassY2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionY2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "Caxis"){myUi->lineEdit_PoleC->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassC->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionC->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "Zaxis"){myUi->lineEdit_PoleZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "A1axis"){myUi->lineEdit_PoleA1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassA1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionA1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "A2axis"){myUi->lineEdit_PoleA2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Pole", "error")));
                                    myUi->lineEdit_MassA2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                    myUi->lineEdit_FrictionA2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Friction", "error")));
                                    }
        else if (child.first == "Poles_of_ContouringControl"){myUi->lineEdit_Contouring_PoleT->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleT", "error")));
                                                    myUi->lineEdit_Contouring_PoleN->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleN", "error")));
                                                    myUi->lineEdit_Contouring_PoleB->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleB", "error")));
                                                    myUi->lineEdit_Contouring_PoleI->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleI", "error")));
                                                    myUi->lineEdit_Contouring_PoleJ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleJ", "error")));
                                                    myUi->lineEdit_Contouring_PoleK->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.PoleK", "error")));
        }
        else if (child.first == "Poles_of_SyncronousControl"){myUi->lineEdit_SyncPoleY->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.SyncPoleY", "error")));
                                                        myUi->lineEdit_SyncPoleA->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.SyncPoleA", "error")));

        }
        else loading=false;
    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading Machineparameter.General error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading Machineparameter.General done");
                }

    for (auto& child : Tree.get_child("MachineParameter.Device"))
    {
        if (child.first == "DAboard"){myUi->lineEdit_DAboard->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.id", "error")));}
        else if (child.first == "Counterboard")myUi->lineEdit_Counterboard->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.id", "error")));
        else loading = false;
    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading Machineparameter.Device error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading Machineparameter.Device done");
                }

    for (auto& child : Tree.get_child("MachineParameter.System"))
    {
        if (child.first == "QT")myUi->lineEdit_QTver->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.ver", "error")));
        else if (child.first == "xenomai")myUi->lineEdit_xenomaiver->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.ver", "error")));
        else if (child.first == "linuxkernel")myUi->lineEdit_linuxkernel->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.ver", "error")));
        else loading = false;
    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading Machineparameter.System error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading Machineparameter.System done");
                }

    for (auto& child : Tree.get_child("MotionParameter.General"))
    {
        if (child.first == "MotionTime")myUi->lineEdit_MotionTime->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "Loop")myUi->lineEdit_Loop->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "TravelTime")myUi->lineEdit_TravelTime->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "modeselect")myUi->comboBox_modeselect->setCurrentText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "SplineType")myUi->comboBox_SplineModeSelect->setCurrentText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else loading = false;
    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading MotionParameter.General error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading MotionParameter.General done");
                }


    for (auto& child : Tree.get_child("MotionParameter.Circle"))
    {
        if (child.first == "t1")myUi->lineEdit_circle_t1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "t2")myUi->lineEdit_circle_t2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "t3")myUi->lineEdit_circle_t3->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "T")myUi->lineEdit_circle_T->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "R")myUi->lineEdit_circle_R->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "v2")myUi->lineEdit_circle_v2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else loading = false;
    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading MotionParameter.Circle error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading MotionParameter.Circle done");
                }


    for (auto& child : Tree.get_child("MotionParameter.Spline"))
    {

        if (child.first == "t1")myUi->lineEdit_spline_t1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "t2")myUi->lineEdit_spline_t2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "t3")myUi->lineEdit_spline_t3->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "T")myUi->lineEdit_spline_T->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "a1")myUi->lineEdit_spline_a1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "a2")myUi->lineEdit_spline_a2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "a3")myUi->lineEdit_spline_a3->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "x0")myUi->lineEdit_spline_x0->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "x1")myUi->lineEdit_spline_x1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "y0")myUi->lineEdit_spline_y0->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "y1")myUi->lineEdit_spline_y1->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "L")myUi->lineEdit_spline_L->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "velopt")myUi->lineEdit_spline_velopt->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else if (child.first == "v2")myUi->lineEdit_spline_v2->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.param", "error")));
        else loading = false;

    }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading MotionParameter.Spline error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading MotionParameter.Splilne done");
                }

            for (auto& child : Tree.get_child("DatalogOption.General"))
            {
                if (child.first == "Xaxis"){myUi->checkBox_Xaxis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_Xaxis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_Xaxis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_Xaxis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_Xaxis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "Y1axis"){myUi->checkBox_Y1axis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_Y1axis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_Y1axis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_Y1axis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_Y1axis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "Y2axis"){myUi->checkBox_Y2axis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_Y2axis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_Y2axis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_Y2axis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_Y2axis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "Caxis"){myUi->checkBox_Caxis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_Caxis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_Caxis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_Caxis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_Caxis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "Zaxis"){myUi->checkBox_Zaxis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_Zaxis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_Zaxis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_Zaxis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_Zaxis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "A1axis"){myUi->checkBox_A1axis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_A1axis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_A1axis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_A1axis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_A1axis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else if (child.first == "A2axis"){myUi->checkBox_A2axis_position->setChecked(child.second.get<bool>("<xmlattr>.position", "error"));
                                            myUi->checkBox_A2axis_velocity->setChecked(child.second.get<bool>("<xmlattr>.velocity", "error"));
                                            myUi->checkBox_A2axis_acceleration->setChecked(child.second.get<bool>("<xmlattr>.acceleration", "error"));
                                            myUi->checkBox_A2axis_force->setChecked(child.second.get<bool>("<xmlattr>.force", "error"));
                                            myUi->checkBox_A2axis_error->setChecked(child.second.get<bool>("<xmlattr>.error", "error"));
                                            }
                else loading=false;}

            for (auto& child : Tree.get_child("DatalogOption.Simulation"))
            {
                if (child.first == "Graph1VelocityPredict")
                    {myUi->checkBox_sim_velpX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velpY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velpY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velpZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velpC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velpA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velpA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph1VelocityResult")
                    {myUi->checkBox_sim_velrX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velrY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velrY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velrZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velrC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velrA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velrA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph1AccelerationPredict")
                    {myUi->checkBox_sim_accpX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accpY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accpY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accpZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accpC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accpA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accpA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph1AccelerationResult")
                    {myUi->checkBox_sim_accrX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accrY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accrY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accrZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accrC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accrA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accrA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph1ForcePredict")
                    {myUi->checkBox_sim_forcepX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcepY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcepY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcepZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcepC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcepA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcepA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph1ForceResult")
                    {myUi->checkBox_sim_forcerX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcerY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcerY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcerZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcerC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcerA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcerA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph1ErrorResult")
                    {myUi->checkBox_sim_ErrorrX->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_ErrorrY1->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_ErrorrY2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_ErrorrZ->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_ErrorrC->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_ErrorrA1->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_ErrorrA2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                //////////graph2
                else if (child.first == "Graph2VelocityPredict")
                    {myUi->checkBox_sim_velpX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velpY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velpY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velpZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velpC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velpA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velpA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph2VelocityResult")
                    {myUi->checkBox_sim_velrX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velrY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velrY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velrZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velrC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velrA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velrA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph2AccelerationPredict")
                    {myUi->checkBox_sim_accpX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accpY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accpY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accpZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accpC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accpA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accpA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph2AccelerationResult")
                    {myUi->checkBox_sim_accrX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accrY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accrY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accrZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accrC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accrA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accrA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph2ForcePredict")
                    {myUi->checkBox_sim_forcepX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcepY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcepY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcepZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcepC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcepA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcepA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph2ForceResult")
                    {myUi->checkBox_sim_forcerX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcerY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcerY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcerZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcerC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcerA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcerA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph2ErrorResult")
                    {myUi->checkBox_sim_ErrorrX_2->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_ErrorrY1_2->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_ErrorrY2_2->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_ErrorrZ_2->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_ErrorrC_2->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_ErrorrA1_2->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_ErrorrA2_2->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                ///////////graph3
                else if (child.first == "Graph3VelocityPredict")
                    {myUi->checkBox_sim_velpX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velpY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velpY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velpZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velpC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velpA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velpA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph3VelocityResult")
                    {myUi->checkBox_sim_velrX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_velrY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_velrY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_velrZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_velrC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_velrA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_velrA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph3AccelerationPredict")
                    {myUi->checkBox_sim_accpX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accpY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accpY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accpZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accpC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accpA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accpA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));

                }
                else if (child.first == "Graph3AccelerationResult")
                    {myUi->checkBox_sim_accrX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_accrY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_accrY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_accrZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_accrC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_accrA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_accrA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph3ForcePredict")
                    {myUi->checkBox_sim_forcepX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcepY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcepY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcepZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcepC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcepA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcepA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph3ForceResult")
                    {myUi->checkBox_sim_forcerX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_forcerY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_forcerY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_forcerZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_forcerC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_forcerA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_forcerA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
                else if (child.first == "Graph3ErrorResult")
                    {myUi->checkBox_sim_ErrorrX_3->setChecked(child.second.get<bool>("<xmlattr>.Xaxis", "error"));
                    myUi->checkBox_sim_ErrorrY1_3->setChecked(child.second.get<bool>("<xmlattr>.Y1axis", "error"));
                    myUi->checkBox_sim_ErrorrY2_3->setChecked(child.second.get<bool>("<xmlattr>.Y2axis", "error"));
                    myUi->checkBox_sim_ErrorrZ_3->setChecked(child.second.get<bool>("<xmlattr>.Zaxis", "error"));
                    myUi->checkBox_sim_ErrorrC_3->setChecked(child.second.get<bool>("<xmlattr>.Caxis", "error"));
                    myUi->checkBox_sim_ErrorrA1_3->setChecked(child.second.get<bool>("<xmlattr>.A1axis", "error"));
                    myUi->checkBox_sim_ErrorrA2_3->setChecked(child.second.get<bool>("<xmlattr>.A2axis", "error"));
                }
            }

            for (auto& child : Tree.get_child("MachineParameter.Energy3Axis"))
            {
                if (child.first == "Xaxis"){myUi->lineEditE_3axisMassX->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Mass", "error")));

                                            myUi->lineEditE_3axisViscoX->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Viscous", "error")));

                                            myUi->lineEditE_3axisCoulombX->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Coulomb", "error")));

                                            myUi->lineEditE_3axisDistX->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Disturbance", "error")));

                }
                else if (child.first == "Yaxis"){myUi->lineEditE_3axisMassY->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.Mass", "error")));
                                            myUi->lineEditE_3axisViscoY->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Viscous", "error")));
                                            myUi->lineEditE_3axisCoulombY->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Coulomb", "error")));
                                            myUi->lineEditE_3axisDistY->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Disturbance", "error")));
                }
                else if (child.first == "Zaxis"){myUi->lineEditE_3axisMassZ->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.Mass", "error")));
                                            myUi->lineEditE_3axisViscoZ->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Viscous", "error")));
                                            myUi->lineEditE_3axisCoulombZ->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Coulomb", "error")));
                                            myUi->lineEditE_3axisDistZ->setText
                                                    (QString::fromStdString(child.second.get<std::string>
                                                                            ("<xmlattr>.Disturbance", "error")));
                }
            }

            for (auto& child : Tree.get_child("MachineParameter.Energy5Axis"))
            {
                if (child.first == "Xaxis"){myUi->lineEditE_5axisMassX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                            myUi->lineEditE_5axisViscoX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Viscous", "error")));
                                            myUi->lineEditE_5axisCoulombX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Coulomb", "error")));
                                            myUi->lineEditE_5axisDistX->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Disturbance", "error")));
                }
                else if (child.first == "Yaxis"){myUi->lineEditE_5axisMassY->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                            myUi->lineEditE_5axisViscoY->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Viscous", "error")));
                                            myUi->lineEditE_5axisCoulombY->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Coulomb", "error")));
                                            myUi->lineEditE_5axisDistY->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Disturbance", "error")));
                }
                else if (child.first == "Zaxis"){myUi->lineEditE_5axisMassZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Mass", "error")));
                                            myUi->lineEditE_5axisViscoZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Viscous", "error")));
                                            myUi->lineEditE_5axisCoulombZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Coulomb", "error")));
                                            myUi->lineEditE_5axisDistZ->setText(QString::fromStdString(child.second.get<std::string>("<xmlattr>.Disturbance", "error")));
                }
            }
            for (auto& child : Tree.get_child("DatalogOption.Option"))
            {
                myUi->checkBox_EnergyCalc->setChecked(child.second.get<bool>("<xmlattr>.AllAxis", "error"));
            }

            if(loading ==false){    myUi->textBrowser->setTextColor("red");
                                    myUi->textBrowser->append("loading DatalogOption error");
                                    loading = true;
            }
            else {  myUi->textBrowser->setTextColor("blue");
                    myUi->textBrowser->append("Loading DatalogOption done");
                }
            int num;
            for (auto& child : Tree.get_child("Formstates.tab"))
            {
                if (child.first == "Tabpage")num=child.second.get<int>("<xmlattr>.param", 100);
            }

            for (auto& child : Tree.get_child("DatalogOption.Simulation2"))
            {
                if (child.first == "Datalog2Graph1Check")
                    {myUi->checkBox_Graph1_data1->setChecked(child.second.get<bool>("<xmlattr>.1", "error"));
                    myUi->checkBox_Graph1_data2->setChecked(child.second.get<bool>("<xmlattr>.2", "error"));
                    myUi->checkBox_Graph1_data3->setChecked(child.second.get<bool>("<xmlattr>.3", "error"));
                    myUi->checkBox_Graph1_data4->setChecked(child.second.get<bool>("<xmlattr>.4", "error"));
                    myUi->checkBox_Graph1_data5->setChecked(child.second.get<bool>("<xmlattr>.5", "error"));
                    myUi->checkBox_Graph1_data6->setChecked(child.second.get<bool>("<xmlattr>.6", "error"));
                    myUi->checkBox_Graph1_data7->setChecked(child.second.get<bool>("<xmlattr>.7", "error"));
                }

                else if (child.first == "Datalog2Graph2Check")
                    {myUi->checkBox_Graph2_data1->setChecked(child.second.get<bool>("<xmlattr>.1", "error"));
                    myUi->checkBox_Graph2_data2->setChecked(child.second.get<bool>("<xmlattr>.2", "error"));
                    myUi->checkBox_Graph2_data3->setChecked(child.second.get<bool>("<xmlattr>.3", "error"));
                    myUi->checkBox_Graph2_data4->setChecked(child.second.get<bool>("<xmlattr>.4", "error"));
                    myUi->checkBox_Graph2_data5->setChecked(child.second.get<bool>("<xmlattr>.5", "error"));
                    myUi->checkBox_Graph2_data6->setChecked(child.second.get<bool>("<xmlattr>.6", "error"));
                    myUi->checkBox_Graph2_data7->setChecked(child.second.get<bool>("<xmlattr>.7", "error"));
                }

                else if (child.first == "Datalog2Graph3Check")
                    {myUi->checkBox_Graph3_data1->setChecked(child.second.get<bool>("<xmlattr>.1", "error"));
                    myUi->checkBox_Graph3_data2->setChecked(child.second.get<bool>("<xmlattr>.2", "error"));
                    myUi->checkBox_Graph3_data3->setChecked(child.second.get<bool>("<xmlattr>.3", "error"));
                    myUi->checkBox_Graph3_data4->setChecked(child.second.get<bool>("<xmlattr>.4", "error"));
                    myUi->checkBox_Graph3_data5->setChecked(child.second.get<bool>("<xmlattr>.5", "error"));
                    myUi->checkBox_Graph3_data6->setChecked(child.second.get<bool>("<xmlattr>.6", "error"));
                    myUi->checkBox_Graph3_data7->setChecked(child.second.get<bool>("<xmlattr>.7", "error"));
                }
                else if (child.first == "Datalog2Graph1Num")
                    {myUi->lineEdit_Graph1_data1->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.1", "error")));

                    myUi->lineEdit_Graph1_data2->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.2", "error")));

                    myUi->lineEdit_Graph1_data3->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.3", "error")));

                    myUi->lineEdit_Graph1_data4->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.4", "error")));

                    myUi->lineEdit_Graph1_data5->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.5", "error")));

                    myUi->lineEdit_Graph1_data6->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.6", "error")));

                    myUi->lineEdit_Graph1_data7->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.7", "error")));
                }

                else if (child.first == "Datalog2Graph2Num")
                    {myUi->lineEdit_Graph2_data1->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.1", "error")));

                    myUi->lineEdit_Graph2_data2->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.2", "error")));

                    myUi->lineEdit_Graph2_data3->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.3", "error")));

                    myUi->lineEdit_Graph2_data4->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.4", "error")));

                    myUi->lineEdit_Graph2_data5->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.5", "error")));

                    myUi->lineEdit_Graph2_data6->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.6", "error")));

                    myUi->lineEdit_Graph2_data7->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.7", "error")));
                }

                else if (child.first == "Datalog2Graph3Num")
                    {myUi->lineEdit_Graph3_data1->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.1", "error")));

                    myUi->lineEdit_Graph3_data2->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.2", "error")));

                    myUi->lineEdit_Graph3_data3->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.3", "error")));

                    myUi->lineEdit_Graph3_data4->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.4", "error")));

                    myUi->lineEdit_Graph3_data5->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.5", "error")));

                    myUi->lineEdit_Graph3_data6->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.6", "error")));

                    myUi->lineEdit_Graph3_data7->setText
                            (QString::fromStdString(child.second.get<std::string>
                                                    ("<xmlattr>.7", "error")));
                }

            }

            for (auto& child : Tree.get_child("AdaptiveParameter.General"))
            {
                if (child.first == "Xaxis")
                    {myUi->lineEdit_AdaCon_L0_X->setText(QString::fromStdString
                                                         (child.second.get<std::string>("<xmlattr>.L0", "error")));
                    myUi->lineEdit_AdaCon_L1_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.L1", "error")));
                    myUi->lineEdit_AdaCon_L2_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.L2", "error")));
                    myUi->lineEdit_AdaCon_d_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.d", "error")));
                    myUi->lineEdit_AdaCon_n_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.n", "error")));
                    myUi->lineEdit_AdaCon_nb_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nb", "error")));
                    myUi->lineEdit_AdaCon_nf_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nf", "error")));
                    myUi->lineEdit_AdaCon_nd_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nd", "error")));
                    myUi->lineEdit_AdaCon_m_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.m", "error")));
                    myUi->lineEdit_AdaCon_nc_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nc", "error")));
                    myUi->lineEdit_AdaCon_nr_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nr", "error")));
                    myUi->lineEdit_AdaCon_np_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.np", "error")));
                    myUi->lineEdit_AdaCon_nq_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nq", "error")));
                    myUi->lineEdit_AdaCon_ns_X->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.ns", "error")));
                }

                else if (child.first == "Y1axis")
                    {
                    myUi->lineEdit_AdaCon_L0_Y1->setText(QString::fromStdString
                                                         (child.second.get<std::string>("<xmlattr>.L0", "error")));
                    myUi->lineEdit_AdaCon_L1_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.L1", "error")));
                    myUi->lineEdit_AdaCon_L2_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.L2", "error")));
                    myUi->lineEdit_AdaCon_d_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.d", "error")));
                    myUi->lineEdit_AdaCon_n_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.n", "error")));
                    myUi->lineEdit_AdaCon_nb_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nb", "error")));
                    myUi->lineEdit_AdaCon_nf_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nf", "error")));
                    myUi->lineEdit_AdaCon_nd_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nd", "error")));
                    myUi->lineEdit_AdaCon_m_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.m", "error")));
                    myUi->lineEdit_AdaCon_nc_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nc", "error")));
                    myUi->lineEdit_AdaCon_nr_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nr", "error")));
                    myUi->lineEdit_AdaCon_np_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.np", "error")));
                    myUi->lineEdit_AdaCon_nq_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.nq", "error")));
                    myUi->lineEdit_AdaCon_ns_Y1->setText(QString::fromStdString
                                                        (child.second.get<std::string>("<xmlattr>.ns", "error")));
                }
            }

            myUi->Maintab->tabBar()->currentChanged(num);
            myUi->Maintab->tabBar()->setCurrentIndex(num);

}

void form_tool::xmlWriting(std::string path){

    std::string otype[3] = {"Pole","Mass","Friction"};
    std::string PoleType[6] = {"PoleT","PoleN","PoleB","PoleI","PoleJ","PoleK"};
    std::string SyncronousControl[2] = {"SyncPoleY","SyncPoleA"};
    std::string Axis[7] = {"Xaxis","Y1axis","Y2axis","Zaxis","Caxis","A1axis","A2axis"};
    std::string Axis3[3] = {"Xaxis","Yaxis","Zaxis"};
    std::string DS[5] = {"DAboard","Counterboard","QT","xenomai","linuxkernel"};
    std::string SM[2] = {"modeselect","SplineType"};
    std::string MG[3] = {"MotionTime","Loop","TravelTime"};
    std::string MC[6] ={"t1","t2","t3","T","R","v2"};
    std::string MS[14]={"t1","t2","t3","T","a1","a2","a3","x0","x1","y0","y1","L","velopt","v2"};
    std::string EF[4]={"Mass","Viscous","Coulomb","Disturbance"};
    std::string DatalogOption[5] = {"position","velocity","acceleration","force","error"};
    std::string GraphNo[3]={"Graph1","Graph2","Graph3"};
    std::string TypeSim[7] = {"VelocityPredict"
                              ,"VelocityResult"
                             ,"AccelerationPredict"
                             ,"AccelerationResult"
                             ,"ForcePredict"
                              ,"ForceResult"
                             ,"ErrorResult"};
    std::string AdapParalabel[14] ={"L0","L1","L2","d","n","nb","nf","nd","m","nc","nr","np","nq","ns"};
    std::string num_data[7] = {"1","2","3","4","5","6","7"};
    this->setParameter();
    std::string text;

    boost::property_tree::ptree     tree;
    boost::property_tree::ptree&    MparaGTree = tree.add("MachineParameter.General", "");
    boost::property_tree::ptree&    MparaDTree = tree.add("MachineParameter.Device", "");
    boost::property_tree::ptree&    MparaSTree = tree.add("MachineParameter.System", "");
    boost::property_tree::ptree&    MparaE3Tree = tree.add("MachineParameter.Energy3Axis", "");
    boost::property_tree::ptree&    MparaE5Tree = tree.add("MachineParameter.Energy5Axis", "");
    boost::property_tree::ptree&    MotionParaTree = tree.add("MotionParameter.General", "");
    boost::property_tree::ptree&    MotionParaCTree = tree.add("MotionParameter.Circle", "");
    boost::property_tree::ptree&    MotionParaSTree = tree.add("MotionParameter.Spline", "");
    boost::property_tree::ptree&    DatalogOptionTree = tree.add("DatalogOption.General", "");
    boost::property_tree::ptree&    DatalogOption_OptionTree = tree.add("DatalogOption.Option", "");
    boost::property_tree::ptree&    FormTabTree = tree.add("Formstates.tab", "");
    boost::property_tree::ptree&    DatalogOptionSimtree = tree.add("DatalogOption.Simulation", "");
    boost::property_tree::ptree&    DatalogOptionSim2tree = tree.add("DatalogOption.Simulation2", "");
    boost::property_tree::ptree&    AdapParametertree = tree.add("AdaptiveParameter.General", "");

    int count = 0;

    for(int j=0;j<7;j++)
        for(int i = 0;i<3;i++,count++)
            MparaGTree.put(Axis[j]+".<xmlattr>."+otype[i],QString::number(mGpara[count]).toStdString());

    for(int i =0;i<6;i++,count++)
        MparaGTree.put("Poles_of_ContouringControl.<xmlattr>."+PoleType[i]
                       ,QString::number(mGpara[count]).toStdString());

    for(int i = 0;i<2;i++,count++)
        MparaGTree.put("Poles_of_SyncronousControl.<xmlattr>."+SyncronousControl[i]
                       ,QString::number(mGpara[count]).toStdString());
    count=0;

    for(int q=0;q<3;q++)
        for(int j=0;j<4;j++,count++)
        MparaE3Tree.put(Axis3[q]+".<xmlattr>."+EF[j]
                        ,QString::number(EnergyPara[count]).toStdString());

    for(int q=0;q<3;q++)
        for(int j=0;j<4;j++,count++)
        MparaE5Tree.put(Axis3[q]+".<xmlattr>."+EF[j]
                        ,QString::number(EnergyPara[count]).toStdString());

    for(int i=0;i<2;i++)MparaDTree.put(DS[i]+".<xmlattr>.id",mDSpara[i]);

    for(int i=2;i<5;i++)MparaSTree.put(DS[i]+".<xmlattr>.ver",mDSpara[i]);

    text = myUi->comboBox_modeselect->currentText().toStdString();
    MotionParaTree.put(SM[0]+".<xmlattr>.param",text);
    text = myUi->comboBox_SplineModeSelect->currentText().toStdString();
    MotionParaTree.put(SM[1]+".<xmlattr>.param",text);

    for(int i=0;i<3;i++
        )MotionParaTree.put(MG[i]+".<xmlattr>.param",QString::number(MotionPara[i]).toStdString());

    for(int i=3;i<9;i++)
        MotionParaCTree.put(MC[i-3]+".<xmlattr>.param", QString::number(MotionPara[i]).toStdString());

    for(int i=9;i<23;i++)
        MotionParaSTree.put(MS[i-9]+".<xmlattr>.param",QString::number(MotionPara[i]).toStdString());

    for(int i=0,count = 0;i<7;i++)
        for(int j=0;j<5;j++,count++)
            DatalogOptionTree.put(Axis[i]+".<xmlattr>."+DatalogOption[j],DatalogSetting[count]);


    count=36;

    for(int j=0;j<3;j++)for(int ii=0;ii<7;ii++)for(int i=0;i<7;i++,count++)
        DatalogOptionSimtree.put(GraphNo[j]+TypeSim[ii]+".<xmlattr>."+Axis[i],DatalogSetting[count]);

count = 0;
    for(int j=0;j<3;j++)for(int i=0;i<7;i++,count++)
        DatalogOptionSim2tree.put("Datalog2"+GraphNo[j]+"Check"+".<xmlattr>."+num_data[i],Datalog2Setting[count]);

    for(int j=0;j<3;j++)for(int i=0;i<7;i++,count++)
        DatalogOptionSim2tree.put("Datalog2"+GraphNo[j]+"Num"+".<xmlattr>."+num_data[i],Datalog2Setting[count]);

    for(int i=0,j=0;i<2;i++)for(int k=0;k<14;k++,j++){
        AdapParametertree.put(Axis[i]+".<xmlattr>."+AdapParalabel[k],AdapPara[j]);
    }

    int num;
    num= myUi->Maintab->tabBar()->currentIndex();
    FormTabTree.put("Tabpage.<xmlattr>.param",num);


    boost::property_tree::write_xml(path, tree, std::locale()
    ,boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));

}

void form_tool::setParameter(){

    mGpara.clear();
    mGpara.push_back(myUi->lineEdit_PoleX->text().toDouble());//1
    mGpara.push_back(myUi->lineEdit_MassX->text().toDouble());//2
    mGpara.push_back(myUi->lineEdit_FrictionX->text().toDouble());//3
    mGpara.push_back(myUi->lineEdit_PoleY1->text().toDouble());//4
    mGpara.push_back(myUi->lineEdit_MassY1->text().toDouble());//5
    mGpara.push_back(myUi->lineEdit_FrictionY1->text().toDouble());//6
    mGpara.push_back(myUi->lineEdit_PoleY2->text().toDouble());//7
    mGpara.push_back(myUi->lineEdit_MassY2->text().toDouble());//8
    mGpara.push_back(myUi->lineEdit_FrictionY2->text().toDouble());//9
    mGpara.push_back(myUi->lineEdit_PoleZ->text().toDouble());//10
    mGpara.push_back(myUi->lineEdit_MassZ->text().toDouble());//11
    mGpara.push_back(myUi->lineEdit_FrictionZ->text().toDouble());//12
    mGpara.push_back(myUi->lineEdit_PoleC->text().toDouble());//13
    mGpara.push_back(myUi->lineEdit_MassC->text().toDouble());;//14
    mGpara.push_back(myUi->lineEdit_FrictionC->text().toDouble());//15
    mGpara.push_back(myUi->lineEdit_PoleA1->text().toDouble());//16
    mGpara.push_back(myUi->lineEdit_MassA1->text().toDouble());//17
    mGpara.push_back(myUi->lineEdit_FrictionA1->text().toDouble());//18
    mGpara.push_back(myUi->lineEdit_PoleA2->text().toDouble());//19
    mGpara.push_back(myUi->lineEdit_MassA2->text().toDouble());//20
    mGpara.push_back(myUi->lineEdit_FrictionA2->text().toDouble());//21
    mGpara.push_back(myUi->lineEdit_Contouring_PoleT->text().toDouble());//22
    mGpara.push_back(myUi->lineEdit_Contouring_PoleN->text().toDouble());//23
    mGpara.push_back(myUi->lineEdit_Contouring_PoleB->text().toDouble());//24
    mGpara.push_back(myUi->lineEdit_Contouring_PoleI->text().toDouble());//25
    mGpara.push_back(myUi->lineEdit_Contouring_PoleJ->text().toDouble());//26
    mGpara.push_back(myUi->lineEdit_Contouring_PoleK->text().toDouble());//27
    mGpara.push_back(myUi->lineEdit_SyncPoleY->text().toDouble());//28
    mGpara.push_back(myUi->lineEdit_SyncPoleA->text().toDouble());//29





    mDSpara.clear();
    mDSpara.push_back((myUi->lineEdit_DAboard->text().toStdString()));//1
    mDSpara.push_back(myUi->lineEdit_Counterboard->text().toStdString());//2
    mDSpara.push_back(myUi->lineEdit_QTver->text().toStdString());//3
    mDSpara.push_back(myUi->lineEdit_xenomaiver->text().toStdString());//4
    mDSpara.push_back(myUi->lineEdit_linuxkernel->text().toStdString());//5

    MotionPara.clear();
    MotionPara.push_back(myUi->lineEdit_MotionTime->text().toDouble());//1
    MotionPara.push_back(myUi->lineEdit_Loop->text().toDouble());//2
    MotionPara.push_back(myUi->lineEdit_TravelTime->text().toDouble());//3
    MotionPara.push_back(myUi->lineEdit_circle_t1->text().toDouble());//4
    MotionPara.push_back(myUi->lineEdit_circle_t2->text().toDouble());//5
    MotionPara.push_back(myUi->lineEdit_circle_t3->text().toDouble());//6
    MotionPara.push_back(myUi->lineEdit_circle_T->text().toDouble());//7
    MotionPara.push_back(myUi->lineEdit_circle_R->text().toDouble());//8
    MotionPara.push_back(myUi->lineEdit_circle_v2->text().toDouble());//9
    MotionPara.push_back(myUi->lineEdit_spline_t1->text().toDouble());//10
    MotionPara.push_back(myUi->lineEdit_spline_t2->text().toDouble());//11
    MotionPara.push_back(myUi->lineEdit_spline_t3->text().toDouble());//12
    MotionPara.push_back(myUi->lineEdit_spline_T->text().toDouble());//13
    MotionPara.push_back(myUi->lineEdit_spline_a1->text().toDouble());//14
    MotionPara.push_back(myUi->lineEdit_spline_a2->text().toDouble());//15
    MotionPara.push_back(myUi->lineEdit_spline_a3->text().toDouble());//16
    MotionPara.push_back(myUi->lineEdit_spline_x0->text().toDouble());//17
    MotionPara.push_back(myUi->lineEdit_spline_x1->text().toDouble());//18
    MotionPara.push_back(myUi->lineEdit_spline_y0->text().toDouble());//19
    MotionPara.push_back(myUi->lineEdit_spline_y1->text().toDouble());//20
    MotionPara.push_back(myUi->lineEdit_spline_L->text().toDouble());//21
    MotionPara.push_back(myUi->lineEdit_spline_velopt->text().toDouble());//22
    MotionPara.push_back(myUi->lineEdit_spline_v2->text().toDouble());//23

    DatalogSetting.clear();
    DatalogSetting.push_back((myUi->checkBox_Xaxis_position->isChecked()));//1
    DatalogSetting.push_back((myUi->checkBox_Xaxis_velocity->isChecked()));//2
    DatalogSetting.push_back((myUi->checkBox_Xaxis_acceleration->isChecked()));//3
    DatalogSetting.push_back((myUi->checkBox_Xaxis_force->isChecked()));//4
    DatalogSetting.push_back((myUi->checkBox_Xaxis_error->isChecked()));//5
    DatalogSetting.push_back((myUi->checkBox_Y1axis_position->isChecked()));//6
    DatalogSetting.push_back((myUi->checkBox_Y1axis_velocity->isChecked()));//7
    DatalogSetting.push_back((myUi->checkBox_Y1axis_acceleration->isChecked()));//8
    DatalogSetting.push_back((myUi->checkBox_Y1axis_force->isChecked()));//9
    DatalogSetting.push_back((myUi->checkBox_Y1axis_error->isChecked()));//10
    DatalogSetting.push_back((myUi->checkBox_Y2axis_position->isChecked()));//11
    DatalogSetting.push_back((myUi->checkBox_Y2axis_velocity->isChecked()));//12
    DatalogSetting.push_back((myUi->checkBox_Y2axis_acceleration->isChecked()));//13
    DatalogSetting.push_back((myUi->checkBox_Y2axis_force->isChecked()));//14
    DatalogSetting.push_back((myUi->checkBox_Y2axis_error->isChecked()));//15
    DatalogSetting.push_back((myUi->checkBox_Caxis_position->isChecked()));//16
    DatalogSetting.push_back((myUi->checkBox_Caxis_velocity->isChecked()));//17
    DatalogSetting.push_back((myUi->checkBox_Caxis_acceleration->isChecked()));//18
    DatalogSetting.push_back((myUi->checkBox_Caxis_force->isChecked()));//19
    DatalogSetting.push_back((myUi->checkBox_Caxis_error->isChecked()));//20
    DatalogSetting.push_back((myUi->checkBox_Zaxis_position->isChecked()));//21
    DatalogSetting.push_back((myUi->checkBox_Zaxis_velocity->isChecked()));//22
    DatalogSetting.push_back((myUi->checkBox_Zaxis_acceleration->isChecked()));//23
    DatalogSetting.push_back((myUi->checkBox_Zaxis_force->isChecked()));//24
    DatalogSetting.push_back((myUi->checkBox_Zaxis_error->isChecked()));//25
    DatalogSetting.push_back((myUi->checkBox_A1axis_position->isChecked()));//26
    DatalogSetting.push_back((myUi->checkBox_A1axis_velocity->isChecked()));//27
    DatalogSetting.push_back((myUi->checkBox_A1axis_acceleration->isChecked()));//28
    DatalogSetting.push_back((myUi->checkBox_A1axis_force->isChecked()));//29
    DatalogSetting.push_back((myUi->checkBox_A1axis_error->isChecked()));//30
    DatalogSetting.push_back((myUi->checkBox_A2axis_position->isChecked()));//31
    DatalogSetting.push_back((myUi->checkBox_A2axis_velocity->isChecked()));//32
    DatalogSetting.push_back((myUi->checkBox_A2axis_acceleration->isChecked()));//33
    DatalogSetting.push_back((myUi->checkBox_A2axis_force->isChecked()));//34
    DatalogSetting.push_back((myUi->checkBox_A2axis_error->isChecked()));//35
    DatalogSetting.push_back((myUi->checkBox_EnergyCalc->isChecked()));//36

    DatalogSetting.push_back(myUi->checkBox_sim_velpX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrX->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrZ->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrC->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA1->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA2->isChecked());


    DatalogSetting.push_back(myUi->checkBox_sim_velpX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrX_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY2_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrZ_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrC_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA1_2->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA2_2->isChecked());


    DatalogSetting.push_back(myUi->checkBox_sim_velpX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velpA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_velrA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accpA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_accrA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcepA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_forcerA2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrX_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrY2_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrZ_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrC_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA1_3->isChecked());
    DatalogSetting.push_back(myUi->checkBox_sim_ErrorrA2_3->isChecked());


    Datalog2Setting.clear();
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data1->isChecked()));//0
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data2->isChecked()));//1
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data3->isChecked()));//2
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data4->isChecked()));//3
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data5->isChecked()));//4
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data6->isChecked()));//5
    Datalog2Setting.push_back((myUi->checkBox_Graph1_data7->isChecked()));//6

    Datalog2Setting.push_back((myUi->checkBox_Graph2_data1->isChecked()));//1
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data2->isChecked()));//2
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data3->isChecked()));//3
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data4->isChecked()));//4
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data5->isChecked()));//5
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data6->isChecked()));//6
    Datalog2Setting.push_back((myUi->checkBox_Graph2_data7->isChecked()));//7


    Datalog2Setting.push_back((myUi->checkBox_Graph3_data1->isChecked()));//1
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data2->isChecked()));//2
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data3->isChecked()));//3
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data4->isChecked()));//4
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data5->isChecked()));//5
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data6->isChecked()));//6
    Datalog2Setting.push_back((myUi->checkBox_Graph3_data7->isChecked()));//7

    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data1->text().toDouble()));//0
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data2->text().toDouble()));//1
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data3->text().toDouble()));//2
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data4->text().toDouble()));//3
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data5->text().toDouble()));//4
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data6->text().toDouble()));//5
    Datalog2Setting.push_back((myUi->lineEdit_Graph1_data7->text().toDouble()));//6

    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data1->text().toDouble()));//1
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data2->text().toDouble()));//2
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data3->text().toDouble()));//3
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data4->text().toDouble()));//4
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data5->text().toDouble()));//5
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data6->text().toDouble()));//6
    Datalog2Setting.push_back((myUi->lineEdit_Graph2_data7->text().toDouble()));//7


    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data1->text().toDouble()));//1
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data2->text().toDouble()));//2
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data3->text().toDouble()));//3
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data4->text().toDouble()));//4
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data5->text().toDouble()));//5
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data6->text().toDouble()));//6
    Datalog2Setting.push_back((myUi->lineEdit_Graph3_data7->text().toDouble()));//7



    EnergyPara.push_back(myUi->lineEditE_3axisMassX->text().toDouble());//0
    EnergyPara.push_back(myUi->lineEditE_3axisViscoX->text().toDouble());//1
    EnergyPara.push_back(myUi->lineEditE_3axisCoulombX->text().toDouble());//2
    EnergyPara.push_back(myUi->lineEditE_3axisDistY->text().toDouble());//3
    EnergyPara.push_back(myUi->lineEditE_3axisMassY->text().toDouble());//4
    EnergyPara.push_back(myUi->lineEditE_3axisViscoY->text().toDouble());//5
    EnergyPara.push_back(myUi->lineEditE_3axisCoulombY->text().toDouble());//6
    EnergyPara.push_back(myUi->lineEditE_3axisDistY->text().toDouble());//7
    EnergyPara.push_back(myUi->lineEditE_3axisMassZ->text().toDouble());//8
    EnergyPara.push_back(myUi->lineEditE_3axisViscoZ->text().toDouble());//9
    EnergyPara.push_back(myUi->lineEditE_3axisCoulombZ->text().toDouble());//10
    EnergyPara.push_back(myUi->lineEditE_3axisDistZ->text().toDouble());//11
    EnergyPara.push_back(myUi->lineEditE_5axisMassX->text().toDouble());//12
    EnergyPara.push_back(myUi->lineEditE_5axisViscoX->text().toDouble());//13
    EnergyPara.push_back(myUi->lineEditE_5axisCoulombX->text().toDouble());//14
    EnergyPara.push_back(myUi->lineEditE_5axisDistY->text().toDouble());//15
    EnergyPara.push_back(myUi->lineEditE_5axisMassY->text().toDouble());//16
    EnergyPara.push_back(myUi->lineEditE_5axisViscoY->text().toDouble());//17
    EnergyPara.push_back(myUi->lineEditE_5axisCoulombY->text().toDouble());//18
    EnergyPara.push_back(myUi->lineEditE_5axisDistY->text().toDouble());//19
    EnergyPara.push_back(myUi->lineEditE_5axisMassZ->text().toDouble());//20
    EnergyPara.push_back(myUi->lineEditE_5axisViscoZ->text().toDouble());//21
    EnergyPara.push_back(myUi->lineEditE_5axisCoulombZ->text().toDouble());//22
    EnergyPara.push_back(myUi->lineEditE_5axisDistZ->text().toDouble());//23

    AdapPara.clear();
    AdapPara.push_back(myUi->lineEdit_AdaCon_L0_X->text().toDouble());//0
    AdapPara.push_back(myUi->lineEdit_AdaCon_L1_X->text().toDouble());//1
    AdapPara.push_back(myUi->lineEdit_AdaCon_L2_X->text().toDouble());//2
    AdapPara.push_back(myUi->lineEdit_AdaCon_d_X->text().toDouble());//3
    AdapPara.push_back(myUi->lineEdit_AdaCon_n_X->text().toDouble());//4
    AdapPara.push_back(myUi->lineEdit_AdaCon_nb_X->text().toDouble());//5
    AdapPara.push_back(myUi->lineEdit_AdaCon_nf_X->text().toDouble());//6
    AdapPara.push_back(myUi->lineEdit_AdaCon_nd_X->text().toDouble());//7
    AdapPara.push_back(myUi->lineEdit_AdaCon_m_X->text().toDouble());//8
    AdapPara.push_back(myUi->lineEdit_AdaCon_nc_X->text().toDouble());//9
    AdapPara.push_back(myUi->lineEdit_AdaCon_nr_X->text().toDouble());//10
    AdapPara.push_back(myUi->lineEdit_AdaCon_np_X->text().toDouble());//11
    AdapPara.push_back(myUi->lineEdit_AdaCon_nq_X->text().toDouble());//12
    AdapPara.push_back(myUi->lineEdit_AdaCon_ns_X->text().toDouble());//13


    AdapPara.push_back(myUi->lineEdit_AdaCon_L0_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_L1_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_L2_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_d_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_n_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_nb_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_nf_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_nd_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_m_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_nc_Y1->text().toDouble());
    AdapPara.push_back(myUi->lineEdit_AdaCon_nr_Y1->text().toDouble());//10
    AdapPara.push_back(myUi->lineEdit_AdaCon_np_Y1->text().toDouble());//11
    AdapPara.push_back(myUi->lineEdit_AdaCon_nq_Y1->text().toDouble());//12
    AdapPara.push_back(myUi->lineEdit_AdaCon_ns_Y1->text().toDouble());//13
}

void form_tool::defineLoading(){
    using namespace define;
    myUi->lineEdit_defInitX->setText(QString::number(INIT_POS_X));
    myUi->lineEdit_defInitY1->setText(QString::number(INIT_POS_Y1));
    myUi->lineEdit_defInitY2->setText(QString::number(INIT_POS_Y2));
    myUi->lineEdit_defInitZ->setText(QString::number(INIT_POS_Z));
    myUi->lineEdit_defInitC->setText(QString::number(INIT_ANGLE_C));
    myUi->lineEdit_defInitA1->setText(QString::number(INIT_ANGLE_A1));
    myUi->lineEdit_defInitA2->setText(QString::number(INIT_ANGLE_A2));

    myUi->lineEdit_defResX->setText(QString::number(RESONATE_LINER_ENC_X));
    myUi->lineEdit_defResY1->setText(QString::number(RESONATE_LINER_ENC_Y1));
    myUi->lineEdit_defResY2->setText(QString::number(RESONATE_LINER_ENC_Y2));
    myUi->lineEdit_defResZ->setText(QString::number(RESONATE_LINER_ENC_Z));
    myUi->lineEdit_defResC->setText(QString::number(RESONATE_ROTATION_ENC_C));
    myUi->lineEdit_defResA1->setText(QString::number(RESONATE_ROTATION_ENC_A1));
    myUi->lineEdit_defResA2->setText(QString::number(RESONATE_ROTATION_ENC_A2));

    myUi->lineEdit_defLPFX->setText(QString::number(CUTOFF_FREC_X));
    myUi->lineEdit_defLPFY1->setText(QString::number(CUTOFF_FREC_Y1));
    myUi->lineEdit_defLPFY2->setText(QString::number(CUTOFF_FREC_Y2));
    myUi->lineEdit_defLPFZ->setText(QString::number(CUTOFF_FREC_Z));
    myUi->lineEdit_defLPFC->setText(QString::number(CUTOFF_FREC_C));
    myUi->lineEdit_defLPFA1->setText(QString::number(CUTOFF_FREC_A1));
    myUi->lineEdit_defLPFA2->setText(QString::number(CUTOFF_FREC_A2));

    myUi->lineEdit_defMaxfX->setText(QString::number(MAX_FORCE_X));
    myUi->lineEdit_defMaxfY1->setText(QString::number(MAX_FORCE_Y1));
    myUi->lineEdit_defMaxfY2->setText(QString::number(MAX_FORCE_Y2));
    myUi->lineEdit_defMaxfZ->setText(QString::number(MAX_FORCE_Z));
    myUi->lineEdit_defMaxfC->setText(QString::number(MAX_TORQUE_C));
    myUi->lineEdit_defMaxfA1->setText(QString::number(MAX_TORQUE_A1));
    myUi->lineEdit_defMaxfA2->setText(QString::number(MAX_TORQUE_A2));

    myUi->lineEdit_defSampling->setText(QString::number(SAMPLING_TIME));
    myUi->lineEdit_defMaxCount->setText(QString::number(MAX_COUNT));

}

void form_tool::nepuko(){
    myUi->textBrowser->setFontPointSize(8);
   // myUi->textBrowser->setStyleSheet("font-size: 9pt;font-family:IPAMonaPGothic;");
}


void form_tool::checker(bool check,std::string comment){
    if (check = true)myUi->textBrowser->setTextColor("blue");
    else myUi->textBrowser->setTextColor("red");
    myUi->textBrowser->append(QString::fromStdString(comment));
}







