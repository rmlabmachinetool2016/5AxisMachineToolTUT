#ifndef _PLANT_H_
#define _PLANT_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include "define.h"

using namespace boost::numeric::ublas;  // boost::numeric::ublas
using namespace define;



    class plant{
	private:

        // model parameter of machine tool
         double MMASS_X			= 5.33;		// kg
         double MMASS_Y1		= 4.545;	// kg
         double MMASS_Y2		= 4.545;	// kg
         double MMASS_Z			= 1.72;		// kg
         double MINERTIA_C		= 0.00342;	// kg*m^2
         double MINERTIA_A1		= 0.00956;	// kg*m^2
         double MINERTIA_A2		= 0.00956;	// kg*m^2
         double MFRICTION_X		= 25.175;	// N*sec/m
         double MFRICTION_Y1	= 24.202;	// N*sec/m
         double MFRICTION_Y2	= 24.202;	// N*sec/m
         double MFRICTION_Z		= 71.647;	// N*sec/m
         double MFRICTION_C		= 0.022;	// N*sec*m
         double MFRICTION_A1	= 0.100;	// N*sec*m
         double MFRICTION_A2	= 0.100;	// N*sec*m

         double MSPRING_X  = 1;

         double NOISE_GAIN		= OMG*RADIUS*10;



        diagonal_matrix<double> mass,c,invmass,invc;
		vector<double> pos,vel,acc;
        matrix<double> noise;
        boost::numeric::ublas::vector<double> A,B,Bx,Hx,cstate;
        boost::numeric::ublas::matrix<double> Fx,Ax;
        boost::numeric::ublas::diagonal_matrix<double> CiM,E;
        boost::numeric::ublas::matrix<double> CiM2;
        boost::numeric::ublas::matrix<double> prod_cim2_E,prod_cim_E;

        vector<double> oldforce;
        vector<double> oldpos;
	public:
        plant();
        boost::numeric::ublas::matrix<double> *datalog;
        bool discreted;
        void plantmodel(unsigned int step, vector<double>& force, bool enable_noise);
		void getstate(vector<double>& pos,vector<double>& vel,vector<double>& acc);
        boost::numeric::ublas::matrix<double> invAx;
	};



#endif
