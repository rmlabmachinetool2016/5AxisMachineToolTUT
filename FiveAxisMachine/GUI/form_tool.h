#ifndef FORM_TOOL_H
#define FORM_TOOL_H
#include <string>
#include <vector>
#include <stdio.h>
namespace Ui{class DesktopMachineToolSystem;}

class form_tool
{
public:
    form_tool();
    form_tool(Ui::DesktopMachineToolSystem *ui);
    void xmlLoading();
    void xmlWriting(std::string path);
    void setParameter();
    void checker(bool check,std::string comment);
    void defineLoading();
    void nepuko();

//signals:

//public slots:

//private slots:


private:
    Ui::DesktopMachineToolSystem *myUi;

    std::vector<double> mGpara;
    std::vector<std::string> mDSpara;
    std::vector<double> MotionPara;
    std::vector<bool> DatalogSetting;
    std::vector<double> Datalog2Setting;
    std::vector<double> EnergyPara;
    std::vector<double> AdapPara;
};


class f_xml{
public:



};


#endif // FORM_TOOL_H
