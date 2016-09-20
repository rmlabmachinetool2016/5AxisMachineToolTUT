#ifndef _IO_H_
#define _IO_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "define.h"
#include "CONTROL/plant.h"
#include "linuxio.h"



using namespace boost::numeric::ublas;  // boost::numeric::ublas
using namespace define;

class iocda{
    linuxio io;
    private:
	static const unsigned int RESOLUTION_DA	= 4095;
	static const int DA_MAX_VOLT			= 10;
	static const int DA_MIN_VOLT			= -DA_MAX_VOLT;
    vector<double> oldpos,oldvel;

    //const int dir[NUM_COUNTER]={-1,1,-1,-1,1,1,-1};
   /* const double cut[NUM_COUNTER] = {CUTOFF_FREC_X,CUTOFF_FREC_Y1,CUTOFF_FREC_Y2
                                     ,CUTOFF_FREC_Z,CUTOFF_FREC_C,CUTOFF_FREC_A1,CUTOFF_FREC_A2};*/

    vector <double> cut;
    vector <double> cnt,cnt2;
    vector <double> resolution;
    vector <int> dir;


public:
    iocda();
    bool *stopptr;
    void GetStateVariable(double time,plant& plant
                          ,bool enable_resolution,vector<double>& pos,vector<double>& vel
                          ,vector<double>& acc);
    void GetStateVariable(double time, vector<double>& pos, vector<double>& vel, vector<double>& acc);
    void OutputControlVariable(vector<double>& f);
	void OutputControlVariable(bool enable_resolution,vector<double>& f);
    void LPF(vector<double> &pos, vector<double> &vel, vector<double> &acc);
};

#endif
