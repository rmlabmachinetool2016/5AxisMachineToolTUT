#ifndef _OUTPUTFILE_H_
#define _OUTPUTFILE_H_
#include <string.h>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

class ExpeOutputFile
{

public:
    std::string DataDumpfunc(std::string *filename
                      , const std::string *filepath
                      , const unsigned int *typeNo
                      , const bool *energySim);
    std::string ModeSelect(int mode_num, std::string filename, unsigned long max_step, std::string filepath);
    void SetParameter(std::vector<double> GcodeParam);
    ExpeOutputFile(boost::numeric::ublas::matrix<double> &datalog);
    boost::numeric::ublas::matrix<double> *datalogptr;
    double My_a1,My_a2,My_a3,My_x1,My_T;
private:

    double MotionCount, AccTime, GcodeSampling;
    std::vector<double> MparaAxis;
    unsigned int option;
    std::string HighPrecision(std::string filename,std::string filepath);
    std::string G01AutoContouringMotion(std::string filename, unsigned long max_step, std::string filepath);
//  void G01ManualContouringMotion(String^ filename, array<double, 2>^ datalog, int max_step);
    std::string  defaultNamegenerator();
    void CalcContouringError(unsigned long max_step);

      // double Mass,friction,efficiency;


};


#endif
