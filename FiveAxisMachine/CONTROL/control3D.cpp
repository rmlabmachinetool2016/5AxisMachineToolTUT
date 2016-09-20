
#include "stdafx.h"
#include "control3D.h"
#include "LIB/math.hpp"
#include "IO/io.h"
#include "plant.h"
#include <cmath>

#undef BOOST_UBLAS_TYPE_CHECK
#define BOOST_UBLAS_TYPE_CHECK 0
control3d::control3d(unsigned int max_step, std::vector<std::vector<double> > *datalogptr)
{
    (void)max_step;
     datalog = datalogptr;
    /*(*datalog).resize(define::NUM_ACTUATOR*8+17);
    for(auto &n :(*datalog)
        )n.resize(max_step+1);*/
    stepcount = 0;
}
void control3d::GenR(double time
                        ,boost::numeric::ublas::vector<double>& wref
                        ,boost::numeric::ublas::vector<double>& wref1
                        ,boost::numeric::ublas::vector<double>& wref2){

#ifdef REF_WORLD
        = GenRW(time,wref,wref1,wref2);
#else
         GenRL(time,wref,wref1,wref2);
#endif
}
void control3d::GenR34(double time
                      ,boost::numeric::ublas::vector<double>& wref3
                      ,boost::numeric::ublas::vector<double>& wref4){

#ifdef REF_WORLD
        = GenRW34(time,wref3,wref4);
#else
    GenRL34(time,wref3,wref4);
#endif
}

void control3d::ControlSim3D(int control_type,
						unsigned int max_step,
						bool enable_noise,
                        bool enable_resolution)
{
    bool enable_sync=false;
	switch(control_type){
        case 0:
            IndependentCon(max_step,enable_noise,enable_resolution,enable_sync);
			break;
        case 1:
            ContouringCon(max_step,enable_noise,enable_resolution,enable_sync);
			break;
        case 2:
            modContouringCon(max_step,enable_noise,enable_resolution,enable_sync);
			break;
		default:
            IndependentCon(max_step,enable_noise,enable_resolution,enable_sync);
			break;
	}
}

void control3d::SetConParam(std::vector<double> *conparam)
{

    mass_x		= (*conparam)[0];
    mass_y1		= (*conparam)[1];
    mass_y2		= (*conparam)[2];
    mass_z		= (*conparam)[3];
    mass_c		= (*conparam)[4];
    mass_a1		= (*conparam)[5];
    mass_a2		= (*conparam)[6];
    c_x			= (*conparam)[7];
    c_y1		= (*conparam)[8];
    c_y2		= (*conparam)[9];
    c_z			= (*conparam)[10];
    c_c			= (*conparam)[11];
    c_a1		= (*conparam)[12];
    c_a2		= (*conparam)[13];
    pole_x		= (*conparam)[14];
    pole_y1		= (*conparam)[15];
    pole_y2		= (*conparam)[16];
    pole_z		= (*conparam)[17];
    pole_c		= (*conparam)[18];
    pole_a1		= (*conparam)[19];
    pole_a2		= (*conparam)[20];
    pole_t		= (*conparam)[21];
    pole_n		= (*conparam)[22];
    pole_b		= (*conparam)[23];
    pole_i		= (*conparam)[24];
    pole_j		= (*conparam)[25];
    pole_k		= (*conparam)[26];
    pole_sync_y	= (*conparam)[27];
    pole_sync_a	= (*conparam)[28];

	mass.resize(NUM_DOF,NUM_DOF);
	c.resize(NUM_DOF,NUM_DOF);
	kpw.resize(NUM_DOF,NUM_DOF);
	kvw.resize(NUM_DOF,NUM_DOF);
	kpl.resize(NUM_DOF,NUM_DOF);
	kvl.resize(NUM_DOF,NUM_DOF);
	mass.clear();
	c.clear();
	kpw.clear();
	kvw.clear();
	kpl.clear();
	kvl.clear();

	masss.resize(2,2);
	cs.resize(2,2);
	kps.resize(2,2);
	kvs.resize(2,2);
	masss.clear();
	cs.clear();
	kps.clear();
	kvs.clear();

	Mo.resize(2,2);
	Co.resize(Mo.size1(),Mo.size2());
	Mo.clear();
	Co.clear();
	kpo.resize(3,3);
	kvo.resize(kpo.size1(),kpo.size2());
	kpo.clear();
	kvo.clear();

	mass(0,0) = mass_x;mass(1,1) = mass_y1;mass(2,2) = mass_z;
	mass(3,3) = mass_c;mass(4,4) = mass_a1;
	c(0,0) = c_x;c(1,1) = c_y1;c(2,2) = c_z;
	c(3,3) = c_c;c(4,4) = c_a1;
	math::invert(mass,invmass);

	kpw(0,0) = pole_x*pole_x;kpw(1,1) = pole_y1*pole_y1;kpw(2,2) = pole_z*pole_z;
	kpw(3,3) = pole_c*pole_c;kpw(4,4) = pole_a1*pole_a1;
	kvw(0,0) = 2*pole_x;kvw(1,1) = 2*pole_y1;kvw(2,2) = 2*pole_z;
	kvw(3,3) = 2*pole_c;kvw(4,4) = 2*pole_a1;

	kpl(0,0) = pole_t * pole_t;
	kpl(1,1) = pole_n * pole_n;
	kpl(2,2) = pole_b * pole_b;
	kpl(3,3) = pole_c * pole_c;
	kpl(4,4) = pole_a1 * pole_a1;
	kvl(0,0) = 2 * pole_t;
	kvl(1,1) = 2 * pole_n;
	kvl(2,2) = 2 * pole_b;
	kvl(3,3) = 2 * pole_c;
	kvl(4,4) = 2 * pole_a1;

	masss(0,0) = mass_y2;
	masss(1,1) = mass_a2;
	cs(0,0) = c_y2;
	cs(1,1) = c_a2;
	kvs(0,0) = 2 * pole_sync_y;
	kvs(1,1) = 2 * pole_sync_a;
	kps(0,0) = pole_sync_y * pole_sync_y;
	kps(1,1) = pole_sync_a * pole_sync_a;

	Mo(0,0) = mass_a1;	Mo(1,1) = mass_c;
	Co(0,0) = c_a1;		Co(1,1) = c_c;
	kvo(0,0) = 2 * pole_i;
	kvo(1,1) = 2 * pole_j;
	kvo(2,2) = 2 * pole_k;
	kpo(0,0) = pole_i * pole_i;
	kpo(1,1) = pole_j * pole_j;
	kpo(2,2) = pole_k * pole_k;

	force.resize(NUM_DOF),forceall.resize(NUM_ACTUATOR);
	ew_log.resize(NUM_ACTUATOR),el_log.resize(NUM_ACTUATOR),
	pw_log.resize(NUM_ACTUATOR),pwdot_log.resize(NUM_ACTUATOR),pw2dot_log.resize(NUM_ACTUATOR),
	pl_log.resize(NUM_ACTUATOR),pldot_log.resize(NUM_ACTUATOR),pl2dot_log.resize(NUM_ACTUATOR),
	prw_log.resize(NUM_ACTUATOR),prwdot_log.resize(NUM_ACTUATOR),prw2dot_log.resize(NUM_ACTUATOR),
	prl_log.resize(NUM_ACTUATOR),prldot_log.resize(NUM_ACTUATOR),prl2dot_log.resize(NUM_ACTUATOR),
	force_log.resize(NUM_ACTUATOR);

	posall.resize(NUM_ACTUATOR),velall.resize(NUM_ACTUATOR),accall.resize(NUM_ACTUATOR);
	pl.resize(NUM_DOF),pldot.resize(NUM_DOF),pl2dot.resize(NUM_DOF),
	pw.resize(NUM_DOF),pwdot.resize(NUM_DOF),pw2dot.resize(NUM_DOF);
	prl.resize(NUM_DOF),prldot.resize(NUM_DOF),prl2dot.resize(NUM_DOF),
	prw.resize(NUM_DOF),prwdot.resize(NUM_DOF),prw2dot.resize(NUM_DOF);

	ew.resize(NUM_DOF),ewdot.resize(NUM_DOF),ew2dot.resize(NUM_DOF);

	es.resize(2),esdot.resize(2),forces.resize(2),
	poss.resize(2),vels.resize(2),accs.resize(2),
	rposs.resize(2),rvels.resize(2),raccs.resize(2);

	eF.resize(NUM_DOF),eFa.resize(NUM_DOF);
	eF.clear(),eFa.clear();
	td = 0;
}

void control3d::GenTWorld(double time
                          ,boost::numeric::ublas::vector<double>& wref
                          ,boost::numeric::ublas::vector<double>& wref1
                          ,boost::numeric::ublas::vector<double>& wref2)
{
	const double theta = OMG * time;

	wref(0)		=  RADIUS*sin(theta);		// x-axis
	wref(1)		=  RADIUS*sin(theta/10);		// y1-axis
	wref(1)=0;
	wref(2)		= -RADIUS*cos(theta);		// z-axis
	wref(3)		=  20*PI/180*sin(theta/2);	// c-axis
	wref(4)		=  10*PI/180*sin(theta/2);	// a1-axis

	wref1(0)	=  RADIUS*OMG*cos(theta);		// x-axis
	wref1(1)	=  RADIUS*OMG*cos(theta/10)/10;		// y1-axis
	wref1(1)=0;
	wref1(2)	=  RADIUS*OMG*sin(theta);		// z-axis
	wref1(3)	=  20*PI/180*OMG*cos(theta/2)/2;	// c-axis
	wref1(4)	=  10*PI/180*OMG*cos(theta/2)/2;	// a1-axis

	wref2(0)	= -RADIUS*OMG*OMG*sin(theta);		// x-axis
	wref2(1)	= -RADIUS*OMG*OMG*sin(theta/10)/100;		// y1-axis
	wref2(1)=0;
	wref2(2)	=  RADIUS*OMG*OMG*cos(theta);		// z-axis
	wref2(3)	= -20*PI/180*OMG*OMG*sin(theta/2)/4;	// c-axis
	wref2(4)	= -10*PI/180*OMG*OMG*sin(theta/2)/4;	// a1-axis
}

void control3d::GenTWorld34(double time
                            ,boost::numeric::ublas::vector<double>& wref3
                            ,boost::numeric::ublas::vector<double>& wref4)
{
	const double theta = OMG * time;

	wref3(0) = -RADIUS*OMG*OMG*OMG*cos(theta);		// x-axis
	wref3(1) = -RADIUS*OMG*OMG*OMG*cos(theta/10)/1000;	// y1-axis
	wref3(1)=0;
	wref3(2) = -RADIUS*OMG*OMG*OMG*sin(theta);		// z-axis
	wref3(3) = -20*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// c-axis
	wref3(4) = -10*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// a1-axis

	wref4(0) =  RADIUS*OMG*OMG*OMG*OMG*sin(theta);		// x-axis
	wref4(1) =  RADIUS*OMG*OMG*OMG*OMG*sin(theta/10)/10000;		// y1-axis
	wref4(1)=0;
	wref4(2) = -RADIUS*OMG*OMG*OMG*OMG*cos(theta);		// z-axis
	wref4(3) =  20*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// c-axis
	wref4(4) =  10*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// a1-axis
}
///*
void control3d::GenTLocal(double time
                          ,boost::numeric::ublas::vector<double>& lref
                          ,boost::numeric::ublas::vector<double>& lref1
                          ,boost::numeric::ublas::vector<double>& lref2)
{
	const double theta = OMG * time;

	//lref(0)		=  RADIUS*sin(theta);		// x-axis
	//lref(1)		=  RADIUS*sin(theta);		// y1-axis
	//lref(2)		= -RADIUS*cos(theta);		// z-axis
	//lref(3)		=  20*PI/180*sin(theta/2);	// c-axis
	//lref(4)		=  10*PI/180*sin(theta/2);	// a1-axis

	//lref1(0)	=  RADIUS*OMG*cos(theta);		// x-axis
	//lref1(1)	=  RADIUS*OMG*cos(theta);		// y1-axis
	//lref1(2)	=  RADIUS*OMG*sin(theta);		// z-axis
	//lref1(3)	=  20*PI/180*OMG*cos(theta/2)/2;	// c-axis
	//lref1(4)	=  10*PI/180*OMG*cos(theta/2)/2;	// a1-axis

	//lref2(0)	= -RADIUS*OMG*OMG*sin(theta);		// x-axis
	//lref2(1)	= -RADIUS*OMG*OMG*sin(theta);		// y1-axis
	//lref2(2)	=  RADIUS*OMG*OMG*cos(theta);		// z-axis
	//lref2(3)	= -20*PI/180*OMG*OMG*sin(theta/2)/4;	// c-axis
	//lref2(4)	= -10*PI/180*OMG*OMG*sin(theta/2)/4;	// a1-axis
    //const double stop[] = {10,20,30};

	lref(0)		= -RADIUS*sin(theta);		// x-axis
	lref(1)		= -RADIUS*cos(theta);		// y1-axis
	lref(2)		= -RADIUS*cos(theta)+SPEEDZ*time;		// z-axis
	//lref(2)		=  SPEEDZ*time;	// z-axis
	//if(time < stop[0])
	//	lref(2)	=  SPEEDZ*time;	// z-axis
	//else 
	//	lref(2)	= SPEEDZ*stop[0];
	lref(3)		=  20*PI/180*sin(theta/2);	// c-axis
	lref(4)		=  10*PI/180*sin(theta/2);	// a1-axis

	lref1(0)	= -RADIUS*OMG*cos(theta);		// x-axis
	lref1(1)	=  RADIUS*OMG*sin(theta);		// y1-axis
	lref1(2)	=  RADIUS*OMG*sin(theta)+SPEEDZ;		// z-axis
	//lref1(2)	=  SPEEDZ;	// z-axis
	//if(time < stop[0])
	//	lref1(2)	=  SPEEDZ;	// z-axis
	//else
	//	lref1(2)	=  SPEEDZ;		// z-axis
	lref1(3)	=  20*PI/180*OMG*cos(theta/2)/2;	// c-axis
	lref1(4)	=  10*PI/180*OMG*cos(theta/2)/2;	// a1-axis

	lref2(0)	=  RADIUS*OMG*OMG*sin(theta);		// x-axis
	lref2(1)	=  RADIUS*OMG*OMG*cos(theta);		// y1-axis
	lref2(2)	=  RADIUS*OMG*OMG*cos(theta);		// z-axis
	//lref2(2)	=  0;		// z-axis
	lref2(3)	= -20*PI/180*OMG*OMG*sin(theta/2)/4;	// c-axis
	lref2(4)	= -10*PI/180*OMG*OMG*sin(theta/2)/4;	// a1-axis
}

void control3d::GenTLocal34(double time
                            ,boost::numeric::ublas::vector<double>& lref3
                            ,boost::numeric::ublas::vector<double>& lref4)
{
	const double theta = OMG * time;

	//lref3(0) = -RADIUS*OMG*OMG*OMG*cos(theta);		// x-axis
	//lref3(1) = -RADIUS*OMG*OMG*OMG*cos(theta);		// y1-axis
	//lref3(2) = -RADIUS*OMG*OMG*OMG*sin(theta);		// z-axis
	//lref3(3) = -20*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// c-axis
	//lref3(4) = -10*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// a1-axis

	//lref4(0) =  RADIUS*OMG*OMG*OMG*OMG*sin(theta);		// x-axis
	//lref4(1) =  RADIUS*OMG*OMG*OMG*OMG*sin(theta);		// y1-axis
	//lref4(2) = -RADIUS*OMG*OMG*OMG*OMG*cos(theta);		// z-axis
	//lref4(3) =  20*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// c-axis
	//lref4(4) =  10*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// a1-axis

    //const double stop[] = {10,20,30};
	
	lref3(0) =  RADIUS*OMG*OMG*OMG*cos(theta);		// x-axis
	lref3(1) = -RADIUS*OMG*OMG*OMG*sin(theta);		// y1-axis
	lref3(2) = -RADIUS*OMG*OMG*OMG*sin(theta);		// z-axis
	//lref3(2) =  0;		// z-axis
	lref3(3) = -20*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// c-axis
	lref3(4) = -10*PI/180*OMG*OMG*OMG*cos(theta/2)/8;	// a1-axis

	lref4(0) = -RADIUS*OMG*OMG*OMG*OMG*sin(theta);		// x-axis
	lref4(1) = -RADIUS*OMG*OMG*OMG*OMG*cos(theta);		// y1-axis
	lref4(2) = -RADIUS*OMG*OMG*OMG*OMG*cos(theta);		// z-axis
	//lref4(2) =  0;		// z-axis
	lref4(3) =  20*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// c-axis
	lref4(4) =  10*PI/180*OMG*OMG*OMG*OMG*sin(theta/2)/16;	// a1-axis
}
//*/


/*
void control3d::GenTLocal(double time,vector<double>& lref,vector<double>& lref1,vector<double>& lref2)
{
	const double theta = OMG * time;

	if(time < 10){
		lref(0)=lref(1)=0;
		lref(2) = time*1;
	}
}

void control3d::GenTLocal34(double time,vector<double>& lref3,vector<double>& lref4)
{
	const double theta = OMG * time;

}
*/

void control3d::GenRL(double time
                      ,boost::numeric::ublas::vector<double>& wref
                      ,boost::numeric::ublas::vector<double>& wref1
                      ,boost::numeric::ublas::vector<double>& wref2)
{
	GenTLocal(time,wref,wref1,wref2);
}

void control3d::GenRL34(double time
                        ,boost::numeric::ublas::vector<double>& wref3
                        ,boost::numeric::ublas::vector<double>& wref4)
{
	GenTLocal34(time,wref3,wref4);
}

void control3d::CalcJ23(boost::numeric::ublas::matrix<double>& J1
             ,boost::numeric::ublas::matrix<double>& J2
             ,boost::numeric::ublas::matrix<double>& J3
             ,boost::numeric::ublas::vector<double>& q
             ,boost::numeric::ublas::vector<double>& q1
             ,boost::numeric::ublas::vector<double>& q2
             ,boost::numeric::ublas::vector<double>& q3
             ,boost::numeric::ublas::vector<double>& q4)
{
    (void)J1;
    (void)q4;
    //static boost::numeric::ublas::matrix<double> oldJ1(5,5,0),oldJ2(5,5,0);
	double x = q(0),y = q(1),z = q(2),c = q(3),a = q(4),
		   x1 = q1(0),y1 = q1(1),z1 = q1(2),c1 = q1(3),a1 = q1(4),
		   x2 = q2(0),y2 = q2(1),z2 = q2(2),c2 = q2(3),a2 = q2(4),
           x3 = q3(0),y3 = q3(1),z3 = q3(2),c3 = q3(3),a3 = q3(4);
           //x4 = q4(0),y4 = q4(1),z4 = q4(2),c4 = q4(3),a4 = q4(4);
    double sa = sin(a),sc = sin(c),ca = cos(a),cc = cos(c);

	J2.clear();
	J2(0,0) = c*c1*cc+c2*sc;
	J2(0,1) = a*(a1*sc*ca+c1*sa*cc)+c*(a1*sa*cc+c1*sc*ca)+a2*sa*sc-c2*cc*ca;
	J2(0,2) = a*(-a1*sa*sc+c1*cc*ca)+c*(a1*cc*ca-c1*sa*sc)+a2*sc*ca+c2*sa*cc;
	J2(0,3) = y*(a1*sc*ca+c1*sa*cc)+z*(-a1*sa*sc+c1*cc*ca)+a*(y1*sc*ca-z1*sa*sc+a1*(-y*sc*sa-z*ca*sc)+c1*(y*cc*ca-z*sa*cc))+c*(y1*sa*cc+z1*cc*ca+a1*(y*cc*ca-z*sa*cc)+c1*(-y*sc*sa-z*ca*sc))+y2*sa*sc+z2*sc*ca+a2*(y*sc*ca-z*sa*sc)+c2*(y*cc*sa+z*ca*cc);
	J2(0,4) = x*c1*cc+y*(a1*sa*cc+c1*sc*ca)+z*(a1*cc*ca-c1*sa*sc)+a*(y1*sa*cc+z1*cc*ca+a1*(y*cc*ca-z*sa*cc)+c1*(-y*sc*sa-z*ca*sc))+c*(x1*cc+y1*sc*ca-z1*sa*sc+a1*(-y*sc*sa-z*ca*sc)+c1*(-x*sc+y*cc*ca-z*sa*cc))+x2*sc-y2*cc*ca+z2*sa*cc+a2*(y*cc*sa+z*ca*cc)+c2*(x*cc+y*sc*ca-z*sa*sc);

	J2(1,0) = -c*c1*sc+c2*cc;
	J2(1,1) =  a*(a1*cc*ca-c1*sa*sc)+c*(-a1*sa*sc+c1*cc*ca)+a2*sa*cc+c2*sc*ca;
	J2(1,2) =  a*(-a1*sa*cc-c1*sc*ca)+c*(-a1*sc*ca-c1*sa*cc)+a2*cc*ca-c2*sa*sc;
	J2(1,3) =  y*(a1*cc*ca-c1*sa*sc)+z*(-a1*sa*cc-c1*sc*ca)+a*(y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-y*sc*ca+z*sa*sc))+c*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+y2*sa*cc+z2*cc*ca+a2*(y*cc*ca-z*sa*cc)+c2*(-y*sc*sa-z*ca*sc);
	J2(1,4) = -x*c1*sc+y*(-a1*sa*sc+c1*cc*ca)+z*(-a1*sc*ca-c1*sa*cc)+a*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+c*(-x1*sc+y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-x*cc-y*sc*ca+z*sa*sc))+x2*cc+y2*sc*ca-z2*sa*sc+a2*(-y*sc*sa-z*ca*sc)+c2*(-x*sc+y*cc*ca-z*sa*cc);

	J2(2,0) =  0;
	J2(2,1) = -a*a1*sa+a2*ca;
	J2(2,2) = -a*a1*ca-a2*sa;
	J2(2,3) = -y*a1*sa-z*a1*ca+a*(-y1*sa-z1*ca+a1*(-y*ca+z*sa))+y2*ca-z2*sa+a2*(-y*sa-z*ca);
	J2(2,4) =  0;
	
	J3.clear();
	J3(0,0) = c*(c1*cc-c*c1*sc+c2*cc)+c2*c*cc+c3*sc;
	J3(0,1) = a*(a1*sc*ca+c1*sa*cc+a*(-a1*sa*sc+c1*cc*ca)+c*(a1*cc*ca-c1*sa*sc)+a2*sc*ca+c2*sa*cc)+c*(a1*sa*cc+c1*sc*ca+a*(a1*cc*ca-c1*sa*sc)+c*(-a1*sa*sc+c1*cc*ca)+a2*sa*cc+c2*sc*ca)+a2*(a*sc*ca+c*sa*cc)+c2*(a*sa*cc+c*sc*ca)+a3*sa*sc-c3*cc*ca;
	J3(0,2) = a*(-a1*sa*sc+c1*cc*ca+a*(-a1*sc*ca-c1*sa*cc)+c*(-a1*sa*cc-c1*sc*ca)-a2*sa*sc+c2*cc*ca)+c*(a1*cc*ca-c1*sa*sc+a*(-a1*sa*cc-c1*sc*ca)+c*(-a1*sc*ca-c1*sa*cc)+a2*cc*ca-c2*sa*sc)+a2*(-a*sa*sc+c*cc*ca)+c2*(a*cc*ca-c*sa*sc)+a3*sc*ca+c3*sa*cc;
	J3(0,3) = y*(a1*sc*ca+c1*sa*cc+a*(-a1*sa*sc+c1*cc*ca)+c*(a1*cc*ca-c1*sa*sc)+a2*sc*ca+c2*sa*cc)+z*(-a1*sa*sc+c1*cc*ca+a*(-a1*sc*ca-c1*sa*cc)+c*(-a1*sa*cc-c1*sc*ca)-a2*sa*sc+c2*cc*ca)+a*(y*(-a1*sa*sc+c1*cc*ca)+z*(-a1*sc*ca-c1*sa*cc)+y1*sc*ca-z1*sa*sc+a1*(-y*sc*sa-z*ca*sc)+c1*(y*cc*ca-z*sa*cc)+a*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+c*(y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-y*sc*ca+z*sa*sc))+y2*sc*ca-z2*sa*sc+a2*(-y*sc*sa-z*ca*sc)+c2*(y*cc*ca-z*sa*cc))+c*(y*(a1*cc*ca-c1*sa*sc)+z*(-a1*sa*cc-c1*sc*ca)+y1*sa*cc+z1*cc*ca+a1*(y*cc*ca-z*sa*cc)+c1*(-y*sc*sa-z*ca*sc)+a*(y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-y*sc*ca+z*sa*sc))+c*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+y2*sa*cc+z2*cc*ca+a2*(y*cc*ca-z*sa*cc)+c2*(-y*sc*sa-z*ca*sc))+y2*(a*sc*ca+c*sa*cc)+z2*(-a*sa*sc+c*cc*ca)+a2*(y*sc*ca-z*sa*sc+a*(-y*sc*sa-z*ca*sc)+c*(y*cc*ca-z*sa*cc))+c2*(y*cc*sa+z*ca*cc+a*(y*cc*ca-z*sa*cc)+c*(-y*sc*sa-z*ca*sc))+y3*sa*sc+z3*sc*ca+a3*(y*sc*ca-z*sa*sc)+c3*(y*cc*sa+z*ca*cc);
	J3(0,4) = x*(c1*cc-c*c1*sc+c2*cc)+y*(a1*sa*cc+c1*sc*ca+a*(a1*cc*ca-c1*sa*sc)+c*(-a1*sa*sc+c1*cc*ca)+a2*sa*cc+c2*sc*ca)+z*(a1*cc*ca-c1*sa*sc+a*(-a1*sa*cc-c1*sc*ca)+c*(-a1*sc*ca-c1*sa*cc)+a2*cc*ca-c2*sa*sc)+a*(y*(a1*cc*ca-c1*sa*sc)+z*(-a1*sa*cc-c1*sc*ca)+y1*sa*cc+z1*cc*ca+a1*(y*cc*ca-z*sa*cc)+c1*(-y*sc*sa-z*ca*sc)+a*(y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-y*sc*ca+z*sa*sc))+c*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+y2*sa*cc+z2*cc*ca+a2*(y*cc*ca-z*sa*cc)+c2*(-y*sc*sa-z*ca*sc))+c*(-x*c1*sc+y*(-a1*sa*sc+c1*cc*ca)+z*(-a1*sc*ca-c1*sa*cc)+a*(-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc))+x1*cc+y1*sc*ca-z1*sa*sc+a1*(-y*sc*sa-z*ca*sc)+c1*(-x*sc+y*cc*ca-z*sa*cc)+c*(-x1*sc+y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-x*cc-y*sc*ca+z*sa*sc))+x2*cc+y2*sc*ca-z2*sa*sc+a2*(-y*sc*sa-z*ca*sc)+c2*(-x*sc+y*cc*ca-z*sa*cc))+x2*c*cc+y2*(a*sa*cc+c*sc*ca)+z2*(a*cc*ca-c*sa*sc)+a2*(y*cc*sa+z*ca*cc+a*(y*cc*ca-z*sa*cc)+c*(-y*sc*sa-z*ca*sc))+c2*(x*cc+y*sc*ca-z*sa*sc+a*(-y*sc*sa-z*ca*sc)+c*(-x*sc+y*cc*ca-z*sa*cc))+x3*sc-y3*cc*ca+z3*sa*cc+a3*(y*cc*sa+z*ca*cc)+c3*(x*cc+y*sc*ca-z*sa*sc);

	J3(1,0) = c*(-c1*sc-c*c1*cc-c2*sc)-c2*c*sc+c3*cc;
	J3(1,1) = a*(a1*cc*ca-c1*sa*sc+a*(-a1*sa*cc-c1*sc*ca)+c*(-a1*sc*ca-c1*sa*cc)+a2*cc*ca-c2*sa*sc)+c*(-a1*sa*sc+c1*cc*ca+a*(-a1*sc*ca-c1*sa*cc)+c*(-a1*sa*cc-c1*sc*ca)-a2*sa*sc+c2*cc*ca)+a2*(a*cc*ca-c*sa*sc)+c2*(-a*sa*sc+c*cc*ca)+a3*sa*cc+c3*sc*ca;
	J3(1,2) = a*(-a1*sa*cc-c1*sc*ca+a*(-a1*cc*ca+c1*sa*sc)+c*(a1*sa*sc-c1*cc*ca)-a2*sa*cc-c2*sc*ca)+c*(-a1*sc*ca-c1*sa*cc+a*(a1*sa*sc-c1*cc*ca)+c*(-a1*cc*ca+c1*sa*sc)-a2*sc*ca-c2*sa*cc)+a2*(-a*sa*cc-c*sc*ca)+c2*(-a*sc*ca-c*sa*cc)+a3*cc*ca-c3*sa*sc;
	J3(1,3) = y*(a1*cc*ca-c1*sa*sc+a*(-a1*sa*cc-c1*sc*ca)+c*(-a1*sc*ca-c1*sa*cc)+a2*cc*ca-c2*sa*sc)+z*(-a1*sa*cc-c1*sc*ca+a*(-a1*cc*ca+c1*sa*sc)+c*(a1*sa*sc-c1*cc*ca)-a2*sa*cc-c2*sc*ca)+a*(y*(-a1*sa*cc-c1*sc*ca)+z*(-a1*cc*ca+c1*sa*sc)+y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-y*sc*ca+z*sa*sc)+a*(-y1*sa*cc-z1*cc*ca+a1*(-y*cc*ca+z*sa*cc)+c1*(y*sc*sa+z*ca*sc))+c*(-y1*sc*ca+z1*sa*sc+a1*(y*sc*sa+z*ca*sc)+c1*(-y*cc*ca+z*sa*cc))+y2*cc*ca-z2*sa*cc+a2*(-y*cc*sa-z*ca*cc)+c2*(-y*sc*ca+z*sa*sc))+c*(y*(-a1*sc*ca-c1*sa*cc)+z*(a1*sa*sc-c1*cc*ca)-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc)+a*(-y1*sc*ca+z1*sa*sc+a1*(y*sc*sa+z*ca*sc)+c1*(-y*cc*ca+z*sa*cc))+c*(-y1*sa*cc-z1*cc*ca+a1*(-y*cc*ca+z*sa*cc)+c1*(y*sc*sa+z*ca*sc))-y2*sa*sc-z2*sc*ca+a2*(-y*sc*ca+z*sa*sc)+c2*(-y*cc*sa-z*ca*cc))+y2*(a*cc*ca-c*sa*sc)+z2*(-a*sa*cc-c*sc*ca)+a2*(y*cc*ca-z*sa*cc+a*(-y*cc*sa-z*ca*cc)+c*(-y*sc*ca+z*sa*sc))+c2*(-y*sc*sa-z*ca*sc+a*(-y*sc*ca+z*sa*sc)+c*(-y*cc*sa-z*ca*cc))+y3*sa*cc+z3*cc*ca+a3*(y*cc*ca-z*sa*cc)+c3*(-y*sc*sa-z*ca*sc);
	J3(1,4) = x*(-c1*sc-c*c1*cc-c2*sc)+y*(-a1*sa*sc+c1*cc*ca+a*(-a1*sc*ca-c1*sa*cc)+c*(-a1*sa*cc-c1*sc*ca)-a2*sa*sc+c2*cc*ca)+z*(-a1*sc*ca-c1*sa*cc+a*(a1*sa*sc-c1*cc*ca)+c*(-a1*cc*ca+c1*sa*sc)-a2*sc*ca-c2*sa*cc)+a*(y*(-a1*sc*ca-c1*sa*cc)+z*(a1*sa*sc-c1*cc*ca)-y1*sa*sc-z1*sc*ca+a1*(-y*sc*ca+z*sa*sc)+c1*(-y*cc*sa-z*ca*cc)+a*(-y1*sc*ca+z1*sa*sc+a1*(y*sc*sa+z*ca*sc)+c1*(-y*cc*ca+z*sa*cc))+c*(-y1*sa*cc-z1*cc*ca+a1*(-y*cc*ca+z*sa*cc)+c1*(y*sc*sa+z*ca*sc))-y2*sa*sc-z2*sc*ca+a2*(-y*sc*ca+z*sa*sc)+c2*(-y*cc*sa-z*ca*cc))+c*(-x*c1*cc+y*(-a1*sa*cc-c1*sc*ca)+z*(-a1*cc*ca+c1*sa*sc)+a*(-y1*sa*cc-z1*cc*ca+a1*(-y*cc*ca+z*sa*cc)+c1*(y*sc*sa+z*ca*sc))-x1*sc+y1*cc*ca-z1*sa*cc+a1*(-y*cc*sa-z*ca*cc)+c1*(-x*cc-y*sc*ca+z*sa*sc)+c*(-x1*cc-y1*sc*ca+z1*sa*sc+a1*(y*sc*sa+z*ca*sc)+c1*(x*sc-y*cc*ca+z*sa*cc))-x2*sc+y2*cc*ca-z2*sa*cc+a2*(-y*cc*sa-z*ca*cc)+c2*(-x*cc-y*sc*ca+z*sa*sc))-x2*c*sc+y2*(-a*sa*sc+c*cc*ca)+z2*(-a*sc*ca-c*sa*cc)+a2*(-y*sc*sa-z*ca*sc+a*(-y*sc*ca+z*sa*sc)+c*(-y*cc*sa-z*ca*cc))+c2*(-x*sc+y*cc*ca-z*sa*cc+a*(-y*cc*sa-z*ca*cc)+c*(-x*cc-y*sc*ca+z*sa*sc))+x3*cc+y3*sc*ca-z3*sa*sc+a3*(-y*sc*sa-z*ca*sc)+c3*(-x*sc+y*cc*ca-z*sa*cc);

	J3(2,0) = 0;
	J3(2,1) = a*(-a1*sa-a*a1*ca-a2*sa)-a2*a*sa+a3*ca;
	J3(2,2) = a*(-a1*ca+a*a1*sa-a2*ca)-a2*a*ca-a3*sa;
	J3(2,3) = y*(-a1*sa-a*a1*ca-a2*sa)+z*(-a1*ca+a*a1*sa-a2*ca)+a*(-y*a1*ca+z*a1*sa-y1*sa-z1*ca+a1*(-y*ca+z*sa)+a*(-y1*ca+z1*sa+a1*(y*sa+z*ca))-y2*sa-z2*ca+a2*(-y*ca+z*sa))-y2*a*sa-z2*a*ca+a2*(-y*sa-z*ca+a*(-y*ca+z*sa))+y3*ca-z3*sa+a3*(-y*sa-z*ca);
	J3(2,4) = 0;

	//J2 = (J1-oldJ1)/0.002;
	//J3 = (J2-oldJ2)/0.002;
	//oldJ1=J1;
	//oldJ2=J2;

}

void control3d::GenRW(double time
                      ,boost::numeric::ublas::vector<double>& wref
                      ,boost::numeric::ublas::vector<double>& wref1
                      ,boost::numeric::ublas::vector<double>& wref2)
{
    boost::numeric::ublas::vector<double>	ref(NUM_DOF),ref1(ref),ref2(ref);
    boost::numeric::ublas::matrix<double>	T(NUM_DOF,NUM_DOF),TT(NUM_DOF,2),J(T),J1(J);

	GenTWorld(time,ref,ref1,ref2);

	CalcConvertMatrixT(T,TT,ref);
	CalcJ(J,ref);
	CalcJdot(J1,ref,ref1);
	wref = prod(T,ref);
	wref1 = prod(J,ref1);
	wref2 = prod(J1,ref1) + prod(J,ref2);
}

void control3d::GenRW34(double time
                        ,boost::numeric::ublas::vector<double>& wref3
                        ,boost::numeric::ublas::vector<double>& wref4)
{
    boost::numeric::ublas::vector<double>	ref(NUM_DOF),ref1(ref),ref2(ref),ref3(ref),ref4(ref);
    boost::numeric::ublas::matrix<double>	J(NUM_DOF,NUM_DOF),J1(J),J2(J),J3(J);

	GenTWorld(time,ref,ref1,ref2);
	GenTWorld34(time,ref3,ref4);

	CalcJ(J,ref);
	CalcJdot(J1,ref,ref1);
	CalcJ23(J1,J2,J3,ref,ref1,ref2,ref3,ref4);

	wref3 = prod(J2,ref1)+2*prod(J1,ref2)+prod(J,ref3);
	wref4 = prod(J3,ref1)+3*prod(J2,ref2)+3*prod(J1,ref3)+prod(J,ref4);
}

void control3d::CalcConvertMatrixT(boost::numeric::ublas::matrix<double>& T
                                   ,boost::numeric::ublas::matrix<double>& TT
                                   ,boost::numeric::ublas::vector<double>& q)
{
	double thc = q(3),tha1 = q(4);
    double sa = sin(tha1),sc = sin(thc),ca = cos(tha1),cc = cos(thc);
	
	T(0,0) = -cc;	T(0,1) = -sc*ca;	T(0,2) = sa*sc;	T(0,3) = 0;	T(0,4) = 0;
	T(1,0) =  sc;	T(1,1) = -cc*ca;	T(1,2) = sa*cc;	T(1,3) = 0;	T(1,4) = 0;
	T(2,0) =  0;	T(2,1) =  sa;		T(2,2) = ca;	T(2,3) = 0;	T(2,4) = 0;
	T(3,0) =  0;	T(3,1) =  0;		T(3,2) = 0;		T(3,3) = 1;	T(3,4) = 0;
	T(4,0) =  0;	T(4,1) =  0;		T(4,2) = 0;		T(4,3) = 0;	T(4,4) = 1;

	TT(0,0) =  0;		TT(0,1) = -sc*sa;
	TT(1,0) =  0;		TT(1,1) = -cc*sa;
	TT(2,0) = -1;		TT(2,1) = -ca;
	TT(3,0) =  0;		TT(3,1) = 0;
	TT(4,0) =  0;		TT(4,1) = 0;
}

void control3d::CalcJ(boost::numeric::ublas::matrix<double>& J
                      ,boost::numeric::ublas::vector<double>& q)
{
	double x = q(0),y1 = q(1),z = q(2),thc = q(3),tha1 = q(4),
		   a2 = OFFSET_BETWEEN_COORDINATE;
    double sa = sin(tha1),sc = sin(thc),ca = cos(tha1),cc = cos(thc);

	J(0,0) = -cc;
	J(0,1) = -sc*ca;
	J(0,2) =  sc*sa;
	J(0,3) =  x*sc - y1*cc*ca + z*cc*sa - a2*cc*sa;
	J(0,4) =		 y1*sc*sa + z*sc*ca - a2*sc*ca;

	J(1,0) =  sc;
	J(1,1) = -cc*ca;
	J(1,2) =  cc*sa;
	J(1,3) =  x*cc + y1*sc*ca - z*sc*sa + a2*sc*sa;
	J(1,4) =		 y1*cc*sa + z*cc*ca - a2*cc*ca;

	J(2,0) = 0;
	J(2,1) = sa;
	J(2,2) = ca;
	J(2,3) = 0;
	J(2,4) = y1*ca - z*sa + a2*sa;

	J(3,0) = 0;
	J(3,1) = 0;
	J(3,2) = 0;
	J(3,3) = 1;
	J(3,4) = 0;

	J(4,0) = 0;
	J(4,1) = 0;
	J(4,2) = 0;
	J(4,3) = 0;
	J(4,4) = 1;
}

void control3d::CalcJdot(boost::numeric::ublas::matrix<double>& Jdot
                         ,boost::numeric::ublas::vector<double>& q
                         ,boost::numeric::ublas::vector<double>& qdot)
{
	double x = q(0),y = q(1),z = q(2),
		   thc = q(3),tha = q(4),
		   xdot = qdot(0),ydot = qdot(1),zdot = qdot(2),
		   thcdot = qdot(3),thadot = qdot(4),
		   a2 = OFFSET_BETWEEN_COORDINATE;
    double sa = sin(tha),sc = sin(thc),ca = cos(tha),cc = cos(thc);

	Jdot(0,0) =  thcdot*sc;
	Jdot(0,1) = -thcdot*cc*ca + thadot*sc*sa;
	Jdot(0,2) =  thadot*ca*sc + thcdot*sa*cc;
	Jdot(0,3) =  qdot(0)*sc+q(0)*thcdot*cc
				-(qdot(1)*ca*cc - q(1)*thadot*sa*cc - q(1)*ca*thcdot*sc)
				+(qdot(2)*sa*cc + q(2)*thadot*ca*cc - q(2)*sa*thcdot*sc)
				-a2*(thadot*ca*cc - sa*thcdot*sc);
	Jdot(0,4) =  (qdot(1)*sc*sa + q(1)*thcdot*cc*sa + q(1)*sc*thadot*ca)
				+(qdot(2)*sc*ca + q(2)*thcdot*cc*ca - q(2)*sc*thadot*sa)
				-a2*(thcdot*cc*ca - thadot*sc*sa);

	Jdot(1,0) =  thcdot*cc;
	Jdot(1,1) =  thcdot*sc*ca + cc*thadot*sa;
	Jdot(1,2) = -thcdot*sc*sa + cc*thadot*ca;
	Jdot(1,3) =  xdot*cc - x*thcdot*sc
				+(ydot*sc*ca + y*thcdot*cc*ca - y*sc*thadot*sa)
				-(zdot*sc*sa + z*thcdot*cc*sa + z*sc*thadot*ca)
				+a2*(thcdot*cc*sa + sc*thadot*ca);
	Jdot(1,4) =  (ydot*cc*sa - y*thcdot*sc*sa + y*cc*thadot*ca)
				+(zdot*cc*ca - z*thcdot*sc*ca - z*cc*thadot*sa)
				-a2*(-thcdot*sc*ca - cc*thadot*sa);

	Jdot(2,0) =  0;
	Jdot(2,1) =  thadot*ca;
	Jdot(2,2) = -thadot*sa;
	Jdot(2,3) =  0;
	Jdot(2,4) =  (qdot(1)*ca - q(1)*thadot*sa)
				-(qdot(2)*sa + q(2)*thadot*ca)
				+a2*thadot*ca;

	Jdot(3,0) = 0;
	Jdot(3,1) = 0;
	Jdot(3,2) = 0;
	Jdot(3,3) = 0;
	Jdot(3,4) = 0;

	Jdot(4,0) = 0;
	Jdot(4,1) = 0;
	Jdot(4,2) = 0;
	Jdot(4,3) = 0;
	Jdot(4,4) = 0;
}

boost::numeric::ublas::vector<double> control3d::CalcOrientation
(boost::numeric::ublas::vector<double>& q)
{
	double tha1 = q(4),thc = q(3);
    boost::numeric::ublas::vector<double> O(3);

	O(0) = sin(tha1) * sin(thc);
	O(1) = sin(tha1) * cos(thc);
	O(2) = cos(tha1);
	/*O(0) = cos(tha1) * sin(thc);
	O(1) = cos(tha1) * cos(thc);
	O(2) = -sin(tha1);*/

	return O;
}

void control3d::CalcJo(boost::numeric::ublas::matrix<double>& Jo
                       ,boost::numeric::ublas::vector<double>& q)
{
	double tha1 = q(4),thc = q(3);
    double sa = sin(tha1),sc = sin(thc),ca = cos(tha1),cc = cos(thc);
	
	Jo(0,0) =  ca * sc;	Jo(0,1) =  sa * cc;
	Jo(1,0) =  ca * cc;	Jo(1,1) = -sa * sc;
	Jo(2,0) = -sa;		Jo(2,1) = 0;
	/*Jo(0,0) = -sa * sc;	Jo(0,1) =  ca * cc;
	Jo(1,0) = -sa * cc;	Jo(1,1) =  ca * -sc;
	Jo(2,0) = -ca;		Jo(2,1) = 0;*/
}

void control3d::CalcJodot(boost::numeric::ublas::matrix<double>& Jodot
                          ,boost::numeric::ublas::vector<double>& q
                          ,boost::numeric::ublas::vector<double>& qdot)
{
	//x y1 z c a1 
	//0 1  2 3 4 
	double tha1,thc,tha1dot,thcdot;
	tha1 = q(4),thc = q(3);
	tha1dot = qdot(4);	thcdot = qdot(3);
    double sa = sin(tha1),sc = sin(thc),ca = cos(tha1),cc = cos(thc);
	
	Jodot(0,0) = -tha1dot*sa*sc + ca*thcdot*cc;
	Jodot(0,1) =  tha1dot*ca*cc - sa*thcdot*sc;
	Jodot(1,0) = -tha1dot*sa*cc - ca*thcdot*sc;
	Jodot(1,1) = -tha1dot*ca*sc - sa*thcdot*cc;
	Jodot(2,0) = -tha1dot*ca;
	Jodot(2,1) =  0;
	/*Jodot(0,0) = -tha1dot*ca*sc - sa*thcdot*cc;
	Jodot(0,1) =  tha1dot*-sa*cc + ca*thcdot*-sc;
	Jodot(1,0) = -tha1dot*ca*cc - sa*thcdot*-sc;
	Jodot(1,1) =  tha1dot*-sa*-sc + ca*thcdot*-cc;
	Jodot(2,0) = -tha1dot*-sa;
	Jodot(2,1) =  0;*/
}

void control3d::CalcFrenetFrame(double time
                                ,boost::numeric::ublas::matrix<double>& F
                                ,boost::numeric::ublas::matrix<double>& F1
                                ,boost::numeric::ublas::matrix<double>& F2)
{
	using namespace numeric::ublas;

    boost::numeric::ublas::vector<double>	w(NUM_DOF),w1(w),w2(w),w3(w),w4(w),
					P1d(3),P2d(P1d),P3d(P1d),P4d(P1d),
					t(3),n(t),b(t),
					t1(t),n1(n),b1(b),
					t2(t),n2(n),b2(b);
    double			s1,s2,s3,s4,
					tau,tau1,tau2,
					nn_dash,nn_dash1,nn_dash2;
    boost::numeric::ublas::vector<double>	n_dash(3),n_dash1(n_dash),n_dash2(n_dash),
					phi(3),phi1(phi),phi2(phi);
	
	//GenerateReference(time,w,w1,w2);
	//GenerateReference34(time,w3,w4);
    GenR(time,w,w1,w2);
    GenR34(time,w3,w4);

	for(unsigned int i=0;i<P1d.size();i++){
		P1d(i) = w1(i);
		P2d(i) = w2(i);
		P3d(i) = w3(i);
		P4d(i) = w4(i);
	}

	tau = inner_prod(P1d,P2d);
	tau1 = inner_prod(P2d,P2d) + inner_prod(P1d,P3d);
	tau2 = 3*inner_prod(P3d,P2d) + inner_prod(P1d,P4d);

	s1 = norm_2(P1d);
	s2 =  tau / s1;
	s3 = (tau1*s1 - tau*s2) / (s1*s1);
	s4 = (tau2*s1*s1*s1-tau1*s1*s1*s2-2*tau*tau1*s1+3*tau*tau*s2) / (s1*s1*s1*s1);

	phi = P2d*s1 - P1d*s2;
	phi1 = P3d*s1 - P1d*s3;
	phi2 = P4d*s1 + P3d*s2 - P2d*s3 - P1d*s4;

	n_dash = phi / (s1*s1*s1);
	n_dash1 = (phi1*s1 - phi*3*s2) / (s1*s1*s1*s1);
	n_dash2 = (phi2*s1*s1-6*phi1*s1*s2-3*phi*s1*s3+12*phi*s2*s2) / pow(s1,5);

	nn_dash = norm_2(n_dash);
	nn_dash1 = inner_prod(n_dash,n_dash1) / nn_dash;
	nn_dash2 = (inner_prod(n_dash1,n_dash1)+inner_prod(n_dash,n_dash2)-nn_dash1*nn_dash1) / nn_dash;

	t = P1d / s1;
	n = n_dash / nn_dash;
	b = cross_prod(t,n);

	t1 = phi / (s1*s1);
	n1 = (n_dash1 - n*nn_dash1) / nn_dash;
	b1 = cross_prod(t1,n) + cross_prod(t,n1);
	
	t2 = (phi1*s1*s1 - phi*2*s1*s2) / (s1*s1*s1*s1);
	n2 = ((n_dash2-n1*nn_dash1-n*nn_dash2)*nn_dash-(n_dash1-n*nn_dash1)*nn_dash1) / (nn_dash*nn_dash);
	b2 = cross_prod(t2,n) + 2*cross_prod(t1,n1) + cross_prod(t,n2);

	F.clear();
	F(0,0) = t(0);	F(0,1) = n(0);	F(0,2) = b(0);
	F(1,0) = t(1);	F(1,1) = n(1);	F(1,2) = b(1);
	F(2,0) = t(2);	F(2,1) = n(2);	F(2,2) = b(2);
	F(3,3) = F(4,4) = 1;
	F1.clear();
	F1(0,0) = t1(0);	F1(0,1) = n1(0);	F1(0,2) = b1(0);
	F1(1,0) = t1(1);	F1(1,1) = n1(1);	F1(1,2) = b1(1);
	F1(2,0) = t1(2);	F1(2,1) = n1(2);	F1(2,2) = b1(2);
	F2.clear();
	F2(0,0) = t2(0);	F2(0,1) = n2(0);	F2(0,2) = b2(0);
	F2(1,0) = t2(1);	F2(1,1) = n2(1);	F2(1,2) = b2(1);
	F2(2,0) = t2(2);	F2(2,1) = n2(2);	F2(2,2) = b2(2);
	
}

boost::numeric::ublas::vector<double> control3d::CalcOrientationControlSignal
(double time
 ,boost::numeric::ublas::vector<double>& pl
 ,boost::numeric::ublas::vector<double>& pldot
 ,double& phi)
{


    double	tha1,thc,
			tha1dot,thcdot,
            tha1ref,thcref,
			tha1refdot,thcrefdot,
			tha1ref2dot,thcref2dot;
	// get reference(L-system)
    boost::numeric::ublas::vector<double> prl(pl),prldot(prl),prl2dot(prl);
    GenR(time,prl,prldot,prl2dot);
    tha1		 = pl(4);		thc			 = pl(3);
    tha1dot		 = pldot(4);	thcdot		 = pldot(3);
    tha1ref		 = prl(4);		thcref		 = prl(3);
    tha1refdot	 = prldot(4);	thcrefdot	 = prldot(3);
    tha1ref2dot	 = prl2dot(4);	thcref2dot	 = prl2dot(3);

    (void)thc;
    (void)thcref;
    (void)tha1ref;


	// orientation
    boost::numeric::ublas::matrix<double>	Jo(3,2),Jodot(Jo),
					Joref(Jo),Jorefdot(Jo),
					tJo,invtJoJo;
	CalcJo(Jo,pl);
	CalcJodot(Jodot,pl,pldot);
	tJo = trans(Jo);
	math::invert(prod(tJo,Jo),invtJoJo);
	invtJoJo(0,0) = 1;invtJoJo(0,1) = 0;
	invtJoJo(1,0) = 0;invtJoJo(1,1) = 1/(sin(tha1)*sin(tha1));
	if(tha1==0)invtJoJo(1,1) = 10e16;//DBL_MAX;
	CalcJo(Joref,prl);
	CalcJodot(Jorefdot,prl,prldot);

    boost::numeric::ublas::vector<double> O(Jo.size1()),Odot(O),thodot(Jo.size2());
	O = CalcOrientation(pl);
	thodot(0) = tha1dot;
	thodot(1) = thcdot;
	Odot = prod(Jo,thodot);

    boost::numeric::ublas::vector<double>	Oref(O),Orefdot(Oref),Oref2dot(Oref),
					thorefdot(thodot),thoref2dot(thodot);
	Oref = CalcOrientation(prl);
	thorefdot(0) = tha1refdot;
	thorefdot(1) = thcrefdot;
	thoref2dot(0) = tha1ref2dot;
	thoref2dot(1) = thcref2dot;
	Orefdot = prod(Joref,thorefdot);
	Oref2dot = prod(Jorefdot,thorefdot) + prod(Joref,thoref2dot);

    boost::numeric::ublas::vector<double> eo(O),eodot(eo);
	eo = Oref - O;
	eodot = Orefdot - Odot;
		
    boost::numeric::ublas::vector<double> torque(2);
    volatile double ddd;
	torque = Oref2dot + prod(kvo,eodot) + prod(kpo,eo) - prod(Jodot,thodot);
	ddd = torque(0);
    (void)ddd;
    torque = prod(prod((boost::numeric::ublas::matrix<double>)prod(Mo,invtJoJo),tJo),torque) + prod(Co,thodot);

	
	/*torque = prod(tJo,eo);
	torque = prod(kpo,torque)-prod(kvo,thodot);
	torque = prod(Mo,torque) + prod(Co,thodot);*/

	phi = acos( inner_prod(Oref,O) );

	return torque;
}

void control3d::SetStateVal(boost::numeric::ublas::vector<double>& pos
                            ,boost::numeric::ublas::vector<double>& vel
                            ,boost::numeric::ublas::vector<double>& acc
                            ,boost::numeric::ublas::vector<double>& posall
                            ,boost::numeric::ublas::vector<double>& velall
                            ,boost::numeric::ublas::vector<double>& accall)
{
	pos(0) = posall(0);	vel(0) = velall(0);	acc(0) = accall(0);
	pos(1) = posall(1);	vel(1) = velall(1);	acc(1) = accall(1);
	pos(2) = posall(3);	vel(2) = velall(3);	acc(2) = accall(3);
	pos(3) = posall(4);	vel(3) = velall(4);	acc(3) = accall(4);
	pos(4) = posall(5);	vel(4) = velall(5);	acc(4) = accall(5);
}

void control3d::LogingData(unsigned int step)
{
	unsigned int i,j;

	// loging data
	prw_log(0) = prw(0);
	prw_log(1) = prw(1);
	prw_log(2) = rposs(0);
	prw_log(3) = prw(2);
	prw_log(4) = prw(3);
	prw_log(5) = prw(4);
	prw_log(6) = rposs(1);
	prl_log(0) = prl(0);
	prl_log(1) = prl(1);
	prl_log(2) = rposs(0);
	prl_log(3) = prl(2);
	prl_log(4) = prl(3);
	prl_log(5) = prl(4);
	prl_log(6) = rposs(1);
	prwdot_log(0) = prwdot(0);
	prwdot_log(1) = prwdot(1);
	prwdot_log(2) = rvels(0);
	prwdot_log(3) = prwdot(2);
	prwdot_log(4) = prwdot(3);
	prwdot_log(5) = prwdot(4);
	prwdot_log(6) = rvels(1);
	prw2dot_log(0) = prw2dot(0);
	prw2dot_log(1) = prw2dot(1);
	prw2dot_log(2) = raccs(0);
	prw2dot_log(3) = prw2dot(2);
	prw2dot_log(4) = prw2dot(3);
	prw2dot_log(5) = prw2dot(4);
	prw2dot_log(6) = raccs(1);
	ew_log(0) = ew(0);
	ew_log(1) = ew(1);
	ew_log(2) = prw(1) - posall(2);
	ew_log(3) = ew(2);
	ew_log(4) = ew(3);
	ew_log(5) = ew(4);
	ew_log(6) = prw(4) - posall(6);
	force_log = forceall;
	pw_log = posall;
	pl_log = posall;
	pl_log(0) = pl(0);
	pl_log(1) = pl(1);
	pl_log(3) = pl(2);
    (*datalog)[0][step] = step * SAMPLING_TIME;
    (*datalog)[1][step] = 0;								// ec
    (*datalog)[2][step] = sqrt(eF(1)*eF(1)+eF(2)*eF(2));	// en
    (*datalog)[3][step] = sqrt(eFa(1)*eFa(1)+eFa(2)*eFa(2));// enmod
    (*datalog)[4][step] = td;								// td
    (*datalog)[5][step] = eF(0);							// eF t
    (*datalog)[6][step] = eF(1);							// eF n
    (*datalog)[7][step] = eF(2);							// eF b
    (*datalog)[8][step] = es(0);							// es y
    (*datalog)[9][step] = es(1);							// es a
	for(i=0,j=0;i<NUM_ACTUATOR;i++,j+=8){
        (*datalog)[j+10][step] = prl_log(i);
        (*datalog)[j+11][step] = prwdot_log(i);
        (*datalog)[j+12][step] = prw2dot_log(i);
        (*datalog)[j+13][step] = pl_log(i);
        (*datalog)[j+14][step] = velall(i);
        (*datalog)[j+15][step] = accall(i);
        (*datalog)[j+16][step] = force_log(i);
        (*datalog)[j+17][step] = ew_log(i);
	}
}

boost::numeric::ublas::vector<double> control3d::SyncCon(double time
                   ,boost::numeric::ublas::vector<double>& posall
                    ,boost::numeric::ublas::vector<double>& velall
                    ,boost::numeric::ublas::vector<double>& pw
                    ,boost::numeric::ublas::vector<double>& pwdot)
{

    static boost::numeric::ublas::vector<double> oldes,oldesdot,oldf;
    boost::numeric::ublas::vector<double> forces(2);

	if(time==0){
		oldes.resize(2);
		oldesdot.resize(2);
		oldf.resize(2);
		oldes.clear();
		oldesdot.clear();
		oldf.clear();
	}
	poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
	poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
	rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
	rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
	es = rposs - poss;
	esdot = rvels - vels;
	esdot = 2*SAMPLING_TIME*(es-oldes)-oldesdot;
	forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);
	
	/*forces = 2*prod(kvs,es-oldes) + SAMPLING_TIME*prod(kps,es+oldes);
	forces = prod(masss,forces)/SAMPLING_TIME;
	forces = forces - 2/SAMPLING_TIME*prod(cs,es-oldes) - oldf;*/
	oldes = es;
	oldesdot = esdot;
	oldf = forces;

	return forces;
}

void control3d::IndependentCon(unsigned int max_step
                               ,bool enable_noise
                               ,bool enable_resolution
                               ,bool enable_sync)
{
(void)enable_sync;
	unsigned int step;
    plant plant;
	double time;

	for(step=0;step<max_step;step++)
	{
		time = step * SAMPLING_TIME;
		
		//x y1 y2 z c a1 a2	::	x y1 z c a1
		//0 1  2  3 4 5  6	::	0 1  2 3 4

		// get state value(W-system)
        IOcda.GetStateVariable(time,plant,enable_resolution,posall,velall,accall);

		// set state value(W-system)
		SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

		// W-systemの状態量をL-systemに変換(pw -> pl)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
		CalcConvertMatrixT(T,TT,pw);
		// オフセットの用意
        boost::numeric::ublas::vector<double> offset(TT.size2());
		double a2 = OFFSET_BETWEEN_COORDINATE,
			   d4 = DISTANCE_FROM_A_TO_C_AXIS;
		offset(0) = d4;
		offset(1) = a2;
		// W-systemの位置情報をL-systemに変換
		pl = prod(T,pw) + prod(TT,offset);
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
		CalcJ(J,pw);
		math::invert(J,invJ);
		// W-systemの速度情報をL-systemに変換
		pldot = prod(J,pwdot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jdot,pw,pwdot);
		// W-systemの加速度情報をL-systemに変換
		pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
		// get reference(L-system)
        GenR(time,prl,prldot,prl2dot);
		
		// L-systemの目標値をW-systemに変換(wref -> qref)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
		CalcConvertMatrixT(Tref,TTref,prl);
		math::invert(Tref,invTref);
		// L-systemの位置情報をW-systemに変換
		prw = prod( invTref,prl - prod(TTref,offset) );
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
		CalcJ(Jref,prw);
		math::invert(Jref,invJref);
		// L-systemの速度情報をW-systemに変換
		prwdot = prod(invJref,prldot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jrefdot,prw,prwdot);
		// L-systemの加速度情報をW-systemに変換
		prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
		
		// calculation tracking error
		// W-systemでの誤差（追従誤差）
		ew = prw - pw;
		ewdot = prwdot- pwdot;
		ew2dot = prw2dot - pw2dot;

		force = prod(mass,prw2dot + prod(kvw,ewdot) + prod(kpw,ew)) + prod(c,pwdot);

		// calculation control value(sync)
		poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
		poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
		rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
		rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
		es = rposs - poss;
		esdot = rvels - vels;
		forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);

		forceall(0) = force(0);
		forceall(1) = force(1);
		forceall(2) = force(1) + forces(0);
		forceall(3) = force(2);
		forceall(4) = force(3);
		forceall(5) = force(4);
		forceall(6) = force(4) + forces(1);		

		// output control value
        IOcda.OutputControlVariable(enable_resolution,forceall);
		
		// input control value to plantmodel
		plant.plantmodel(time,forceall,enable_noise);

		// loging data
        LogingData(step);
	}
}

void control3dExp::IndependentCon(unsigned int step
                               ,bool enable_sync)
{
    (void)enable_sync;
	double time;
	time = step * SAMPLING_TIME;
		
	//x y1 y2 z c a1 a2	::	x y1 z c a1
	//0 1  2  3 4 5  6	::	0 1  2 3 4

	// get state value(W-system)
    IOcda.GetStateVariable(time,posall,velall,accall);

	// set state value(W-system)
	SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

	// W-systemの状態量をL-systemに変換(pw -> pl)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
	CalcConvertMatrixT(T,TT,pw);
	// オフセットの用意
    boost::numeric::ublas::vector<double> offset(TT.size2());
	double a2 = OFFSET_BETWEEN_COORDINATE,
			d4 = DISTANCE_FROM_A_TO_C_AXIS;
	offset(0) = d4;
	offset(1) = a2;
	// W-systemの位置情報をL-systemに変換
	pl = prod(T,pw) + prod(TT,offset);
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
	CalcJ(J,pw);
	math::invert(J,invJ);
	// W-systemの速度情報をL-systemに変換
	pldot = prod(J,pwdot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jdot,pw,pwdot);
	// W-systemの加速度情報をL-systemに変換
	pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
	// get reference(L-system)
    GenR(time,prl,prldot,prl2dot);
		
	// L-systemの目標値をW-systemに変換(wref -> qref)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
	CalcConvertMatrixT(Tref,TTref,prl);
	math::invert(Tref,invTref);
	// L-systemの位置情報をW-systemに変換
	prw = prod( invTref,prl - prod(TTref,offset) );
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
	CalcJ(Jref,prw);
	math::invert(Jref,invJref);
	// L-systemの速度情報をW-systemに変換
	prwdot = prod(invJref,prldot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jrefdot,prw,prwdot);
	// L-systemの加速度情報をW-systemに変換
	prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
		
	// calculation tracking error
	// W-systemでの誤差（追従誤差）
	ew = prw - pw;
	ewdot = prwdot- pwdot;
	ew2dot = prw2dot - pw2dot;

	force = prod(mass,prw2dot + prod(kvw,ewdot) + prod(kpw,ew)) + prod(c,pwdot);

	// calculation control value(sync)
	forces = SyncCon(time,posall,velall,pw,pwdot);

	forceall(0) = force(0);
	forceall(1) = force(1);
	forceall(2) = -(force(1) + forces(0));
	forceall(3) = force(2);
	forceall(4) = -force(3);
	forceall(5) = force(4);
	forceall(6) = -(force(4) + forces(1));

	// output control value
    IOcda.OutputControlVariable(false,forceall);

	// loging data
	forceall(4) *= -1;
    LogingData(step);
}

void control3d::ContouringCon(unsigned int max_step
                              ,bool enable_noise
                              ,bool enable_resolution
                              ,bool enable_sync)
{
(void)enable_sync;
	unsigned int step;
    plant plant;
	double time;

	for(step=0;step<max_step;step++)
	{
		time = step * SAMPLING_TIME;
		
		//x y1 y2 z c a1 a2	::	x y1 z c a1
		//0 1  2  3 4 5  6	::	0 1  2 3 4

		// get state value(W-system)
        IOcda.GetStateVariable(time,plant,enable_resolution,posall,velall,accall);

		// set state value(W-system)
		SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

		// W-systemの状態量をL-systemに変換(pw -> pl)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
		CalcConvertMatrixT(T,TT,pw);
		// オフセットの用意
        boost::numeric::ublas::vector<double> offset(TT.size2());
		double a2 = OFFSET_BETWEEN_COORDINATE,
			   d4 = DISTANCE_FROM_A_TO_C_AXIS;
		offset(0) = d4;
		offset(1) = a2;
		// W-systemの位置情報をL-systemに変換
		pl = prod(T,pw) + prod(TT,offset);
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
		CalcJ(J,pw);
		math::invert(J,invJ);
		// W-systemの速度情報をL-systemに変換
		pldot = prod(J,pwdot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jdot,pw,pwdot);
		// W-systemの加速度情報をL-systemに変換
		pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
		// get reference(L-system)
        GenR(time,prl,prldot,prl2dot);
		
		// L-systemの目標値をW-systemに変換(wref -> qref)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
		CalcConvertMatrixT(Tref,TTref,prl);
		math::invert(Tref,invTref);
		// L-systemの位置情報をW-systemに変換
		prw = prod( invTref,prl - prod(TTref,offset) );
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
		CalcJ(Jref,prw);
		math::invert(Jref,invJref);
		// L-systemの速度情報をW-systemに変換
		prwdot = prod(invJref,prldot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jrefdot,prw,prwdot);
		// L-systemの加速度情報をW-systemに変換
		prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
		
		// calculation tracking error
		// W-systemでの誤差（追従誤差）
		ew = prw - pw;
		ewdot = prwdot- pwdot;
		ew2dot = prw2dot - pw2dot;

		// L-systemでの誤差
        boost::numeric::ublas::vector<double> el(ew),eldot(el),el2dot(el);
		el = prl - pl;
		eldot = prldot - pldot;
		el2dot = prl2dot - pl2dot;

		// Calculation Frenet-Frame
        boost::numeric::ublas::matrix<double> F(T),Fdot(F),F2dot(F),tF,tFdot,tF2dot;
		CalcFrenetFrame(time,F,Fdot,F2dot);	// get Frenet frame(current)
		tF = trans(F);
		tFdot = trans(Fdot);
		tF2dot = trans(F2dot);

        boost::numeric::ublas::vector<double> eFdot(eF);
		eF = prod(tF,el);
		eFdot = prod(tFdot,el) + prod(tF,eldot);

		force = prl2dot + prod(F,prod(kvl,eFdot) + prod(kpl,eF) + 2*prod(tFdot,eldot) + prod(tF2dot,el)) - prod(Jdot,pwdot);
		force = prod(prod(mass,invJ),force) + prod(c,pwdot);

		// calculation control value(sync)
		poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
		poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
		rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
		rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
		es = rposs - poss;
		esdot = rvels - vels;
		forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);

		forceall(0) = force(0);
		forceall(1) = force(1);
		forceall(2) = force(1) + forces(0);
		forceall(3) = force(2);
		forceall(4) = force(3);
		forceall(5) = force(4);
		forceall(6) = force(4) + forces(1);

		// output control value
        IOcda.OutputControlVariable(enable_resolution,forceall);
		
		// input control value to plantmodel
		plant.plantmodel(time,forceall,enable_noise);

		// loging data
        LogingData(step);
	}
}

void control3dExp::ContouringCon(unsigned int step
                              ,short AioId
                              ,short CntId
                              ,bool enable_sync)
{
(void)enable_sync;
	double time;

	time = step * SAMPLING_TIME;
		
	//x y1 y2 z c a1 a2	::	x y1 z c a1
	//0 1  2  3 4 5  6	::	0 1  2 3 4

	// get state value(W-system)
    IOcda.GetStateVariable(time,posall,velall,accall);

	// set state value(W-system)
	SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

	// W-systemの状態量をL-systemに変換(pw -> pl)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
	CalcConvertMatrixT(T,TT,pw);
	// オフセットの用意
    boost::numeric::ublas::vector<double> offset(TT.size2());
	double	a2 = OFFSET_BETWEEN_COORDINATE,
			d4 = DISTANCE_FROM_A_TO_C_AXIS;
	offset(0) = d4;
	offset(1) = a2;
	// W-systemの位置情報をL-systemに変換
	pl = prod(T,pw) + prod(TT,offset);
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
	CalcJ(J,pw);
	math::invert(J,invJ);
	// W-systemの速度情報をL-systemに変換
	pldot = prod(J,pwdot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jdot,pw,pwdot);
	// W-systemの加速度情報をL-systemに変換
	pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
	// get reference(L-system)
    GenR(time,prl,prldot,prl2dot);
		
	// L-systemの目標値をW-systemに変換(wref -> qref)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
	CalcConvertMatrixT(Tref,TTref,prl);
	math::invert(Tref,invTref);
	// L-systemの位置情報をW-systemに変換
	prw = prod( invTref,prl - prod(TTref,offset) );
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
	CalcJ(Jref,prw);
	math::invert(Jref,invJref);
	// L-systemの速度情報をW-systemに変換
	prwdot = prod(invJref,prldot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jrefdot,prw,prwdot);
	// L-systemの加速度情報をW-systemに変換
	prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
	
	// calculation tracking error
	// W-systemでの誤差（追従誤差）
	ew = prw - pw;
	ewdot = prwdot- pwdot;
	ew2dot = prw2dot - pw2dot;

	// L-systemでの誤差
    boost::numeric::ublas::vector<double> el(ew),eldot(el),el2dot(el);
	el = prl - pl;
	eldot = prldot - pldot;
	el2dot = prl2dot - pl2dot;

	// Calculation Frenet-Frame
    boost::numeric::ublas::matrix<double> F(T),Fdot(F),F2dot(F),tF,tFdot,tF2dot;
	CalcFrenetFrame(time,F,Fdot,F2dot);	// get Frenet frame(current)
	tF = trans(F);
	tFdot = trans(Fdot);
	tF2dot = trans(F2dot);

    boost::numeric::ublas::vector<double> eFdot(eF);
	eF = prod(tF,el);
	eFdot = prod(tFdot,el) + prod(tF,eldot);

	force = prl2dot + prod(F,prod(kvl,eFdot) + prod(kpl,eF) + 2*prod(tFdot,eldot) + prod(tF2dot,el)) - prod(Jdot,pwdot);
	force = prod(prod(mass,invJ),force) + prod(c,pwdot);

	// calculation control value(sync)
	poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
	poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
	rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
	rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
	es = rposs - poss;
	esdot = rvels - vels;
	forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);
	forces = SyncCon(time,posall,velall,pw,pwdot);

	forceall(0) = force(0);
	forceall(1) = force(1);
	forceall(2) = -(force(1) + forces(0));
	forceall(3) = force(2);
	forceall(4) = -force(3);
	forceall(5) = force(4);
	forceall(6) = -(force(4) + forces(1));

	// output control value
    IOcda.OutputControlVariable(AioId,forceall);

	// loging data
	forceall(4) *= -1;
    LogingData(step);
}

void control3d::modContouringCon(unsigned int max_step
                                 ,bool enable_noise
                                 ,bool enable_resolution
                                 ,bool enable_sync)
{
(void)enable_sync;
	unsigned int step,i;
    plant plant;
	double time;

	for(step=0;step<max_step;step++)
	{
		time = step * SAMPLING_TIME;
		
		//x y1 y2 z c a1 a2	::	x y1 z c a1
		//0 1  2  3 4 5  6	::	0 1  2 3 4

		// get state value(W-system)
        IOcda.GetStateVariable(time,plant,enable_resolution,posall,velall,accall);

		// set state value(W-system)
		SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

		// W-systemの状態量をL-systemに変換(pw -> pl)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
		CalcConvertMatrixT(T,TT,pw);
		// オフセットの用意
        boost::numeric::ublas::vector<double> offset(TT.size2());
		double a2 = OFFSET_BETWEEN_COORDINATE,
			   d4 = DISTANCE_FROM_A_TO_C_AXIS;
		offset(0) = d4;
		offset(1) = a2;
		// W-systemの位置情報をL-systemに変換
		pl = prod(T,pw) + prod(TT,offset);
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
		CalcJ(J,pw);
		math::invert(J,invJ);
		// W-systemの速度情報をL-systemに変換
		pldot = prod(J,pwdot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jdot,pw,pwdot);
		// W-systemの加速度情報をL-systemに変換
		pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
		// get reference(L-system)
        GenR(time,prl,prldot,prl2dot);
		
		// L-systemの目標値をW-systemに変換(wref -> qref)
		// 位置情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
		CalcConvertMatrixT(Tref,TTref,prl);
		math::invert(Tref,invTref);
		// L-systemの位置情報をW-systemに変換
		prw = prod( invTref,prl - prod(TTref,offset) );
		// 速度情報の変換行列の計算
        boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
		CalcJ(Jref,prw);
		math::invert(Jref,invJref);
		// L-systemの速度情報をW-systemに変換
		prwdot = prod(invJref,prldot);
		// 加速度情報の変換行列の計算
		CalcJdot(Jrefdot,prw,prwdot);
		// L-systemの加速度情報をW-systemに変換
		prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
		
		// calculation tracking error
		// W-systemでの誤差（追従誤差）
		ew = prw - pw;
		ewdot = prwdot- pwdot;
		ew2dot = prw2dot - pw2dot;

		// L-systemでの誤差
        boost::numeric::ublas::vector<double> el(ew),eldot(el),el2dot(el);
		el = prl - pl;
		eldot = prldot - pldot;
		el2dot = prl2dot - pl2dot;

		// Calculation Frenet-Frame
        boost::numeric::ublas::matrix<double> F(T),Fdot(F),F2dot(F),tF,tFdot,tF2dot;
		CalcFrenetFrame(time,F,Fdot,F2dot);	// get Frenet frame(current)
		tF = trans(F);
		tFdot = trans(Fdot);
		tF2dot = trans(F2dot);

        boost::numeric::ublas::vector<double> eFdot(eF);
		eF = prod(tF,el);
		eFdot = prod(tFdot,el) + prod(tF,eldot);

		// calculation delay time
        boost::numeric::ublas::vector<double> Prefdot(3);
		for(i=0;i<Prefdot.size();i++)
			Prefdot(i) = prldot(i);
		td = eF(0) / norm_2(Prefdot);

		// get reference(L-system,delay)
        boost::numeric::ublas::vector<double> pral(pl),praldot(pral),pral2dot(pral);
        GenR(time-td,pral,praldot,pral2dot);

        boost::numeric::ublas::matrix<double> Fa(F),Fadot(Fa),Fa2dot(Fa),tFa,tFadot,tFa2dot;
		CalcFrenetFrame(time-td,Fa,Fadot,Fa2dot);	// get Frenet frame(delay)
		tFa = trans(Fa);
		tFadot = trans(Fadot);
		tFa2dot = trans(Fa2dot);

		// adjustmented reference(L-system)
        boost::numeric::ublas::matrix<double> Q(F),Qdot(Q),Q2dot(Q),S(Q.size1(),Q.size2(),0);
		S(1,1) = S(2,2) = S(3,3) = S(4,4) = 1;
        Q = prod(boost::numeric::ublas::matrix<double>(prod(Fa,S)),tFa);
        Qdot = prod(boost::numeric::ublas::matrix<double>(prod(Fadot,S)),tFa)
                + prod(boost::numeric::ublas::matrix<double>(prod(Fa,S)),tFadot);
        Q2dot = prod(boost::numeric::ublas::matrix<double>(prod(Fa2dot,S)),tFa)
                + 2*prod(boost::numeric::ublas::matrix<double>(prod(Fadot,S)),tFadot)
                + prod(boost::numeric::ublas::matrix<double>(prod(Fa,S)),tFa2dot);
        boost::numeric::ublas::vector<double> prnl(pl),prnldot(prnl),prnl2dot(prnl);
		prnl = prl + prod(Q,pral-prl);
		prnldot = prldot + prod(Qdot,pral-prl) + prod(Q,praldot-prldot);
		prnl2dot = prl2dot + prod(Q2dot,pral-prl) + 2*prod(Qdot,praldot-prldot) + prod(Q,pral2dot-prl2dot);

        boost::numeric::ublas::vector<double> enl(el),enldot(enl);
		enl = prnl - pl;
		enldot = prnldot - pldot;

        boost::numeric::ublas::vector<double> eFadot(eFa);
		eFa = prod(tFa,enl);
		eFadot = prod(tFadot,enl) + prod(tFa,enldot);

		force = prnl2dot + prod(Fa,prod(kvl,eFadot) + prod(kpl,eFa) + 2*prod(tFadot,enldot) + prod(tFa2dot,enl)) - prod(Jdot,pwdot);
		force = prod(prod(mass,invJ),force) + prod(c,pwdot);

		// calculation control value(sync)
		poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
		poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
		rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
		rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
		es = rposs - poss;
		esdot = rvels - vels;
		forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);

		forceall(0) = force(0);
		forceall(1) = force(1);
		forceall(2) = force(1) + forces(0);
		forceall(3) = force(2);
		forceall(4) = force(3);
		forceall(5) = force(4);
		forceall(6) = force(4) + forces(1);

		// output control value
        IOcda.OutputControlVariable(enable_resolution,forceall);
		
		// input control value to plantmodel
		plant.plantmodel(time,forceall,enable_noise);

		// loging data
		eF = eFa;
        LogingData(step);
	}
}

void control3dExp::modContouringCon(unsigned int step
                                 ,short AioId
                                 ,short CntId
                                 ,bool enable_sync)
{
(void)enable_sync;
	unsigned int i;
	double time;

	time = step * SAMPLING_TIME;
		
	//x y1 y2 z c a1 a2	::	x y1 z c a1
	//0 1  2  3 4 5  6	::	0 1  2 3 4

	// get state value(W-system)
    IOcda.GetStateVariable(time,posall,velall,accall);

	// set state value(W-system)
	SetStateVal(pw,pwdot,pw2dot,posall,velall,accall);

	// W-systemの状態量をL-systemに変換(pw -> pl)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> T(pw.size(),pw.size()),TT(pw.size(),2);
	CalcConvertMatrixT(T,TT,pw);
	// オフセットの用意
    boost::numeric::ublas::vector<double> offset(TT.size2());
	double	a2 = OFFSET_BETWEEN_COORDINATE,
			d4 = DISTANCE_FROM_A_TO_C_AXIS;
	offset(0) = d4;
	offset(1) = a2;
	// W-systemの位置情報をL-systemに変換
	pl = prod(T,pw) + prod(TT,offset);
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> J(T),Jdot(J),invJ(J);
	CalcJ(J,pw);
	math::invert(J,invJ);
	// W-systemの速度情報をL-systemに変換
	pldot = prod(J,pwdot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jdot,pw,pwdot);
	// W-systemの加速度情報をL-systemに変換
	pl2dot = prod(J,pw2dot) + prod(Jdot,pwdot);
		
	// get reference(L-system)
    GenR(time,prl,prldot,prl2dot);
		
	// L-systemの目標値をW-systemに変換(wref -> qref)
	// 位置情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Tref(T),TTref(TT),invTref;
	CalcConvertMatrixT(Tref,TTref,prl);
	math::invert(Tref,invTref);
	// L-systemの位置情報をW-systemに変換
	prw = prod( invTref,prl - prod(TTref,offset) );
	// 速度情報の変換行列の計算
    boost::numeric::ublas::matrix<double> Jref(Tref),Jrefdot(Jref),invJref(Jref);
	CalcJ(Jref,prw);
	math::invert(Jref,invJref);
	// L-systemの速度情報をW-systemに変換
	prwdot = prod(invJref,prldot);
	// 加速度情報の変換行列の計算
	CalcJdot(Jrefdot,prw,prwdot);
	// L-systemの加速度情報をW-systemに変換
	prw2dot = prod(invJref,prl2dot - prod(Jrefdot,prwdot));
		
	// calculation tracking error
	// W-systemでの誤差（追従誤差）
	ew = prw - pw;
	ewdot = prwdot- pwdot;
	ew2dot = prw2dot - pw2dot;

	// L-systemでの誤差
    boost::numeric::ublas::vector<double> el(ew),eldot(el),el2dot(el);
	el = prl - pl;
	eldot = prldot - pldot;
	el2dot = prl2dot - pl2dot;

	// Calculation Frenet-Frame
    boost::numeric::ublas::matrix<double> F(T),Fdot(F),F2dot(F),tF,tFdot,tF2dot;
	CalcFrenetFrame(time,F,Fdot,F2dot);	// get Frenet frame(current)
	tF = trans(F);
	tFdot = trans(Fdot);
	tF2dot = trans(F2dot);

    boost::numeric::ublas::vector<double> eFdot(eF);
	eF = prod(tF,el);
	eFdot = prod(tFdot,el) + prod(tF,eldot);

	// calculation delay time
    boost::numeric::ublas::vector<double> Prefdot(3);
	for(i=0;i<Prefdot.size();i++)
		Prefdot(i) = prldot(i);
	td = eF(0) / norm_2(Prefdot);

	// get reference(L-system,delay)
    boost::numeric::ublas::vector<double> pral(pl),praldot(pral),pral2dot(pral);
    GenR(time-td,pral,praldot,pral2dot);

    boost::numeric::ublas::matrix<double> Fa(F),Fadot(Fa),Fa2dot(Fa),tFa,tFadot,tFa2dot;
	CalcFrenetFrame(time-td,Fa,Fadot,Fa2dot);	// get Frenet frame(delay)
	tFa = trans(Fa);
	tFadot = trans(Fadot);
	tFa2dot = trans(Fa2dot);

	// adjustmented reference(L-system)
    boost::numeric::ublas::matrix<double> Q(F),Qdot(Q),Q2dot(Q),S(Q.size1(),Q.size2(),0);
	S(1,1) = S(2,2) = S(3,3) = S(4,4) = 1;
    Q = prod(matrix<double>(prod(Fa,S)),tFa);
    Qdot = prod(boost::numeric::ublas::matrix<double>(prod(Fadot,S)),tFa
                ) + prod(boost::numeric::ublas::matrix<double>(prod(Fa,S)),tFadot);
    Q2dot = prod(boost::numeric::ublas::matrix<double>(prod(Fa2dot,S)),tFa)
            + 2*prod(matrix<double>(prod(Fadot,S)),tFadot)
            + prod(boost::numeric::ublas::matrix<double>(prod(Fa,S)),tFa2dot);
    boost::numeric::ublas::vector<double> prnl(pl),prnldot(prnl),prnl2dot(prnl);
	prnl = prl + prod(Q,pral-prl);
	prnldot = prldot + prod(Qdot,pral-prl) + prod(Q,praldot-prldot);
	prnl2dot = prl2dot + prod(Q2dot,pral-prl) + 2*prod(Qdot,praldot-prldot) + prod(Q,pral2dot-prl2dot);

    boost::numeric::ublas::vector<double> enl(el),enldot(enl);
	enl = prnl - pl;
	enldot = prnldot - pldot;

    boost::numeric::ublas::vector<double> eFadot(eFa);
	eFa = prod(tFa,enl);
	eFadot = prod(tFadot,enl) + prod(tFa,enldot);

	force = prnl2dot + prod(Fa,prod(kvl,eFadot) + prod(kpl,eFa) + 2*prod(tFadot,enldot) + prod(tFa2dot,enl)) - prod(Jdot,pwdot);
	force = prod(prod(mass,invJ),force) + prod(c,pwdot);

	// calculation control value(sync)
	poss(0) = posall(2);	vels(0) = velall(2);	accs(0) = accall(2);	// Y2
	poss(1) = posall(6);	vels(1) = velall(6);	accs(1) = accall(6);	// A2
	rposs(0) = pw(1);		rvels(0) = pwdot(1);	raccs(0) = pw2dot(1);	// Y2
	rposs(1) = pw(4);		rvels(1) = pwdot(4);	raccs(1) = pw2dot(4);	// A2
	es = rposs - poss;
	esdot = rvels - vels;
	forces = prod(masss,(prod(kvs,esdot)+prod(kps,es))) - prod(cs,esdot);
	forces = SyncCon(time,posall,velall,pw,pwdot);

	forceall(0) = force(0);
	forceall(1) = force(1);
	forceall(2) = -(force(1) + forces(0));
	forceall(3) = force(2);
	forceall(4) = -force(3);
	forceall(5) = force(4);
	forceall(6) = -(force(4) + forces(1));

	// output control value
    IOcda.OutputControlVariable(AioId,forceall);

	// loging data
	forceall(4) *= -1;
	eF = eFa;
    LogingData(step);
}
control3dExp::control3dExp(unsigned int max_step):control3d(max_step,NULL){

}
