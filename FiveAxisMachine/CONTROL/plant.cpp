//#include "stdafx.h"
//#define NDEBUG
#undef BOOST_UBLAS_TYPE_CHECK
#define BOOST_UBLAS_TYPE_CHECK 0
#include "plant.h"
#include "LIB/math.hpp"
#include <cmath>
#include <boost/random.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <ctime>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include "LIB/math.hpp"



template <class T>
struct exponential : scalar_unary_functor<T> {
    static T apply(T t) { return exp(t); }
};
plant::plant()
{
    A.resize(NUM_ACTUATOR);
    B.resize(NUM_ACTUATOR);

	pos.resize(NUM_ACTUATOR);
	vel.resize(NUM_ACTUATOR);
	acc.resize(NUM_ACTUATOR);
    pos(0) = INIT_POS_X;
    pos(1) = INIT_POS_Y1;
    pos(2) = INIT_POS_Y2;
    pos(3) = INIT_POS_Z;
    pos(4) = INIT_ANGLE_C;
    pos(5) = INIT_ANGLE_A1;
    pos(6) = INIT_ANGLE_A2;
	vel.clear();
	acc.clear();

	mass.resize(NUM_ACTUATOR,NUM_ACTUATOR);
	mass(0,0)=MMASS_X;mass(1,1)=MMASS_Y1;mass(2,2)=MMASS_Y2;mass(3,3)=MMASS_Z;
	mass(4,4)=MINERTIA_C;mass(5,5)=MINERTIA_A1;mass(6,6)=MINERTIA_A2;
	math::invert(mass,invmass);

	c.resize(NUM_ACTUATOR,NUM_ACTUATOR);
	c(0,0)=MFRICTION_X;c(1,1)=MFRICTION_Y1;c(2,2)=MFRICTION_Y2;c(3,3)=MFRICTION_Z;
	c(4,4)=MFRICTION_C;c(5,5)=MFRICTION_A1;c(6,6)=MFRICTION_A2;
    math::invert(c,invc);//gyakugyouretu

	// init noise(Mersenne twister)
	noise.resize(NUM_ACTUATOR,MAX_COUNT);
	boost::mt19937 seed(static_cast<unsigned long>(time(NULL)));
	boost::uniform_real<> range(-1,1);
	boost::variate_generator< boost::mt19937, boost::uniform_real<> > rand( seed,range );
	for(int i=0;i<NUM_ACTUATOR;i++)
		for(int j=0;j<MAX_COUNT;j++)
			noise(i,j) = rand() * NOISE_GAIN;

    oldforce.resize(3);
    oldforce.clear();

    discreted = false;

    Ax.resize(2,2);
    Bx.resize(2);
    Fx.resize(2,2);
    Hx.resize(2);

    Ax.clear();
    Bx.clear();
    Fx.clear();
    Hx.clear();


    Ax(0,1) = 0;                    Ax(0,1) = 1;
    Ax(1,0) = - MSPRING_X/MMASS_X;  Ax(1,1) = - MFRICTION_X/MMASS_X;

    Bx(0) = 0;
    Bx(1) = 1/MMASS_X;


    double ramda1,ramda2,Framda1,Framda2;

    ramda1 = (-MFRICTION_X+sqrt(pow(MFRICTION_X,2)-4*MSPRING_X))/(2*MMASS_X);
    ramda2 = (-MFRICTION_X-sqrt(pow(MFRICTION_X,2)-4*MSPRING_X))/(2*MMASS_X);

    Framda1 = exp(ramda1*SAMPLING_TIME);
    Framda2 = exp(ramda2*SAMPLING_TIME);

    boost::numeric::ublas::matrix<double> UnitMat = identity_matrix<double> (2);

    Fx = Framda1 * (Ax-ramda2*UnitMat) / (ramda1 - ramda2) + Framda2 * (Ax-ramda1*UnitMat) / (ramda2 - ramda1);

    math::invert(Ax,invAx);

    Hx = prod(prod(invAx,Fx-UnitMat),Bx);

    cstate.resize(Fx.size1());
    cstate.clear();

    CiM = prod(c,invmass);
    E = numeric::ublas::apply_to_all<exponential<double>>(-prod(c,invmass)*define::SAMPLING_TIME);
    CiM2 = prod(CiM,CiM);

    prod_cim_E = prod(CiM,E);
    prod_cim2_E = prod(CiM2,E);

}



void plant::plantmodel(unsigned int step,boost::numeric::ublas::vector<double>& force,bool enable_noise)
{
    //インディシャル応答
    //無駄時間考慮せず

discreted = true;

    if(discreted==false){
        //matlab result
        if(step>2){
            /*2ms
            3.75e-07 z + 3.747e-07
            ----------------------
            z^2 - 1.998 z + 0.9981*/
           /*pos(0) = 1.998*(*datalog)(13,step)//pos
                        -0.9981*(*datalog)(13,step-1)//pos
                        +3.75*pow(0.1,7)*force(0)//force
                        +3.747*pow(0.1,7)*(*datalog)(16,step-1)//force
                        ;*/

            /*0.2ms
             3.752e-09 z + 3.752e-09
            -----------------------
              z^2 - 2 z + 0.9998*/
            pos(0) = 2*(*datalog)(13,step)//pos
                                    -0.9998*(*datalog)(13,step-1)//pos
                                    +3.752*pow(0.1,9)*force(0)//force
                                    +3.752*pow(0.1,9)*(*datalog)(16,step-1)//force
                                    ;



        }
        else {
            pos(0) = 0;
        }


        /*cstate = prod(Fx,cstate)+Hx*force(0);
        pos(0) = cstate(0);
        vel(0) = cstate(1);
        acc(0) = 1/MMASS_X*(force(0) - MFRICTION_X*vel(0)-MSPRING_X*vel(0));*/

    }

    else if(enable_noise==false){
        A = prod(prod(mass,invc),prod(invc,force)-vel);
        B = pos - A;


        pos = prod(E,A) + B + prod(invc,force)*SAMPLING_TIME;
        vel = -prod((prod_cim_E),A) + prod(invc,force);//posの微分
        //acc =prod(prod(boost::numeric::ublas::matrix<double>(prod(CiM,CiM)),E),A);//accの微分

        acc =prod(prod_cim2_E,A);//accの微分

    }
else{
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(1, 10);

    pos = prod(E,A) + B + prod(invc,force)*SAMPLING_TIME*(1000-dist(gen))/1000;
    vel = (-prod((prod(CiM,E)),A) + prod(invc,force))*(1000-dist(gen))/1000;//posの微分
    acc = (prod(prod(boost::numeric::ublas::matrix<double>(prod(CiM,CiM)),E),A))
            *(1000-dist(gen))/1000;//accの微分

}

}

void plant::getstate(vector<double>& refpos,vector<double>& refvel,vector<double>& refacc)
{
    oldpos = refpos;
    if(discreted==false){
	refpos = pos;
	refvel = vel;
    refacc = acc;
    }
    else{
        refpos = pos;
        refvel = vel;
        refacc = acc;
    }

}
