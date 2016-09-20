#ifndef FORMFUNCTION_H
#define FORMFUNCTION_H
#include "boost/shared_ptr.hpp"
#include <vector>
namespace Ui {class DesktopMachineToolSystem;}


class FormGraphFunction
{
public:
    FormGraphFunction();
    void loadforminf(std::vector<double> &conparam
                     , std::vector<double> &conparam2);
    void loadGraphinf(std::vector<unsigned int> &Graph1
                     , std::vector<unsigned int> &Graph2
                      , std::vector<unsigned int> &Graph3);
    void loadGraphsubinf(std::vector<unsigned int> &Graph1
                     , std::vector<unsigned int> &Graph2
                      , std::vector<unsigned int> &Graph3);

        Ui::DesktopMachineToolSystem *ui;
private:


    std::vector<double> setParam1();
    std::vector<double> setParam2();

    std::vector<unsigned int> setGraph1Param();
    std::vector<unsigned int> setGraph2Param();
    std::vector<unsigned int> setGraph3Param();

    std::vector<unsigned int> setGraph1subParam();
    std::vector<unsigned int> setGraph2subParam();
    std::vector<unsigned int> setGraph3subParam();

};

#endif // FORMFUNCTION_H
