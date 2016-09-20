//#include "stdafx.h"
#include "io.h"
//#include "Caio.h"
//#include "CCnt.h"
//#include "CIoLib.h"

#if basesystem == 0
    #include <native/task.h>
#endif

#include "LIB/math.hpp"
////#include "xeno_system.h"
#include "CONTROL/control2D.h"


using namespace define;

typedef boost::numeric::ublas::vector<double> bstvector;

void iocda::GetStateVariable(double time,vector<double>& pos,vector<double>& vel,vector<double>& acc)
{


    //unsigned long CntDat[NUM_COUNTER];
    //short ChNo[NUM_COUNTER] = {0,1,2,3,4,5,6};

    if(time == 0){
        oldpos.resize(NUM_COUNTER);
        oldvel.resize(NUM_COUNTER);
        oldpos.clear();
        oldvel.clear();
    }
    // reading values from encorder
#if DeviceReady == 1
    CntRet = CntReadCount ( CntId , ChNo , NUM_COUNTER , CntDat );
#else
    io.ReadCount(cnt);
#endif
    // convert right-hand system
    cnt2 = element_prod(cnt,dir);


    // convert position(meter)
    pos = element_prod(cnt2,resolution);

    double a,b;

    for(unsigned int i=0;i<NUM_COUNTER;i++)
    {
        if(cut[i] != 0){
            // lpf(z convert)
            a = 2*cut[i] / (cut[i]*SAMPLING_TIME+2);
            b = (cut[i]*SAMPLING_TIME-2) / (cut[i]*SAMPLING_TIME+2);
            vel(i) = a * (pos(i)-oldpos(i)) - b * oldvel(i);
            //acc(i) = a * (vel(i)-oldvel(i)) - b * oldacc(i);
            acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;
        }else{
            // diff
            vel(i) = (pos(i) - oldpos(i)) / SAMPLING_TIME;
            acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;
            if(time == 0){
                vel(i) = 0;
                acc(i) = 0;
            }
            else if(time == SAMPLING_TIME)
                acc(i) = 0;
        }
    }

    oldpos = pos;
    oldvel = vel;
    //oldacc = acc;
}

void iocda::GetStateVariable(double time,plant& plant
                             ,bool enable_resolution
                             ,vector<double>& pos
                             ,vector<double>& vel
                             ,vector<double>& acc)
{

    oldpos = pos;
    oldvel = vel;
    plant.getstate(pos,vel,acc);// non-delay


}


void iocda::OutputControlVariable(vector<double>& f)
{

	int i;
	vector<double> force(f);
    //float outputf[NUM_ACTUATOR];
    vector<double> outputf;
    double max_force[NUM_LINEAR_ACTUATOR] = {MAX_FORCE_X,MAX_FORCE_Y1,MAX_FORCE_Y2,MAX_FORCE_Z};
	double max_torque[NUM_ROTATION_ACTUATOR] = {MAX_TORQUE_C,MAX_TORQUE_A1,MAX_TORQUE_A2};
    outputf.resize(NUM_ACTUATOR);
    for(unsigned int i=0;i<NUM_LINEAR_ACTUATOR;i++)
	{
        if(force[i] > max_force[i]){
			force(i) = max_force[i];
            if(i == 0)(*stopptr)=true;
        }
        else if(force(i) < -max_force[i]){
			force(i) = -max_force[i];
            if(i == 0)(*stopptr)=true;
        }
        //outputf[i] = static_cast<float>(force(i)/max_force[i]*DA_MAX_VOLT);
        outputf[i] = force[i]/max_force[i]*DA_MAX_VOLT;
	}
	for(i=0;i<NUM_ROTATION_ACTUATOR;i++)
	{
		if(force(i+NUM_LINEAR_ACTUATOR) > max_torque[i])
			force(i+NUM_LINEAR_ACTUATOR) = max_torque[i];
		else if(force(i+NUM_LINEAR_ACTUATOR) < -max_torque[i])
			force(i+NUM_LINEAR_ACTUATOR) = -max_torque[i];
        //outputf[i+NUM_LINEAR_ACTUATOR] = static_cast<float>(force(i+NUM_LINEAR_ACTUATOR)/max_torque[i]*DA_MAX_VOLT);
        outputf[i+NUM_LINEAR_ACTUATOR] = (force(i+NUM_LINEAR_ACTUATOR)/max_torque[i]*DA_MAX_VOLT);

    }

	f = force;
    #if DeviceReady == 1
	for(i=0;i<NUM_ACTUATOR;i++)
        AioSingleAoEx ( AioId , i , outputf[i] );
    #else
    io.OutputDA(outputf);
    #endif
}

void iocda::OutputControlVariable(bool enable_resolution,vector<double>& f)
{

	int i;
	short output[NUM_ACTUATOR];
	double max_force[NUM_LINEAR_ACTUATOR] = {MAX_FORCE_X,MAX_FORCE_Y1,MAX_FORCE_Y2,MAX_FORCE_Z};
	double max_torque[NUM_ROTATION_ACTUATOR] = {MAX_TORQUE_C,MAX_TORQUE_A1,MAX_TORQUE_A2};
	double convert_coefficient[NUM_ACTUATOR],convert_offset;
	
	convert_offset = RESOLUTION_DA / 2;
	for(i=0;i<NUM_LINEAR_ACTUATOR;i++)
		convert_coefficient[i] = RESOLUTION_DA / (max_force[i] * 2);
	for(i=0;i<NUM_ROTATION_ACTUATOR;i++)
		convert_coefficient[i+NUM_LINEAR_ACTUATOR] = RESOLUTION_DA / (max_torque[i] * 2);

	for(i=0;i<NUM_LINEAR_ACTUATOR;i++)
	{
		if(f(i) > max_force[i])
			f(i) = max_force[i];
		else if(f(i) < -max_force[i])
			f(i) = -max_force[i];
		output[i] = static_cast<short>(f(i) * convert_coefficient[i] + convert_offset);
	}
	for(i=0;i<NUM_ROTATION_ACTUATOR;i++)
	{
		if(f(i+NUM_LINEAR_ACTUATOR) > max_torque[i])
			f(i+NUM_LINEAR_ACTUATOR) = max_torque[i];
		else if(f(i+NUM_LINEAR_ACTUATOR) < -max_torque[i])
			f(i+NUM_LINEAR_ACTUATOR) = -max_torque[i];
		output[i+NUM_LINEAR_ACTUATOR] = static_cast<short>(f(i+NUM_LINEAR_ACTUATOR) * convert_coefficient[i+NUM_LINEAR_ACTUATOR] + convert_offset);
	}

	if(enable_resolution){
		for(i=0;i<NUM_LINEAR_ACTUATOR;i++)
			f(i) = (output[i] - convert_offset) / convert_coefficient[i];
		for(i=0;i<NUM_ROTATION_ACTUATOR;i++)
			f(i+NUM_LINEAR_ACTUATOR) = (output[i+NUM_LINEAR_ACTUATOR] - convert_offset) / convert_coefficient[i+NUM_LINEAR_ACTUATOR];
	}

}

void iocda::LPF(vector<double> &pos,vector<double> &vel,vector<double> &acc){


    vector<short> cnt(NUM_COUNTER);

    int temp[NUM_COUNTER];
    double cut[NUM_COUNTER] = {CUTOFF_FREC_X,CUTOFF_FREC_Y1,CUTOFF_FREC_Y2,CUTOFF_FREC_Z,CUTOFF_FREC_C,CUTOFF_FREC_A1,CUTOFF_FREC_A2};

        temp[0] = static_cast<int>(pos(0) / RESONATE_LINER_ENC_X);
        temp[1] = static_cast<int>(pos(1) / RESONATE_LINER_ENC_Y1);
        temp[2] = static_cast<int>(pos(2) / RESONATE_LINER_ENC_Y2);
        temp[3] = static_cast<int>(pos(3) / RESONATE_LINER_ENC_Z);
        temp[4] = static_cast<int>(pos(4) / RESONATE_ROTATION_ENC_C);
        temp[5] = static_cast<int>(pos(5) / RESONATE_ROTATION_ENC_A1);
        temp[6] = static_cast<int>(pos(6) / RESONATE_ROTATION_ENC_A2);

        pos(0) = static_cast<double>(temp[0]) * RESONATE_LINER_ENC_X;
        pos(1) = static_cast<double>(temp[1]) * RESONATE_LINER_ENC_Y1;
        pos(2) = static_cast<double>(temp[2]) * RESONATE_LINER_ENC_Y2;
        pos(3) = static_cast<double>(temp[3]) * RESONATE_LINER_ENC_Z;
        pos(4) = static_cast<double>(temp[4]) * RESONATE_ROTATION_ENC_C;
        pos(5) = static_cast<double>(temp[5]) * RESONATE_ROTATION_ENC_A1;
        pos(6) = static_cast<double>(temp[6]) * RESONATE_ROTATION_ENC_A2;
return;
       for(unsigned int i=0;i<NUM_COUNTER;i++)
       {
            if(cut[i] != 0){

//RC lpf
                double a = 1.0/(2.0*PI*cut[i]);
                double  b = a/(a+SAMPLING_TIME);
                pos(i) = b*oldpos(i)+(1.0-b)*pos(i);
                vel(i) = (pos(i) - oldpos(i)) / SAMPLING_TIME;
                acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;
                /*
                pos(i) = oldpos(i) + (pos(i)-oldpos(i))*cut[i]*SAMPLING_TIME;
                vel(i) = (pos(i) - oldpos(i)) / SAMPLING_TIME;
                acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;*/

/*                // lpf(z convert)
                double a = 2*cut[i] / (cut[i]*SAMPLING_TIME+2),


                b = (cut[i]*SAMPLING_TIME-2) / (cut[i]*SAMPLING_TIME+2);
                vel(i) = a * (pos(i)-oldpos(i)) - b * oldvel(i);
                //acc(i) = a * (vel(i)-oldvel(i)) - b * oldacc(i);
                acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;
                //*/
/*
                // lpf(z convert,second)
                matrix<double> A(2,2),I=identity_matrix<double>(A.size1()),A_inv;
                vector<double> X(A.size1()),oldX(X),B(X);
                static matrix<double> oldXs(NUM_ACTUATOR,A.size1());

                if(time==0)
                    oldXs.clear();
                A(0,0) = 0;
                A(0,1) = 1;
                A(1,0) = -cut[i] * cut[i];
                A(1,1) = -2 * cut[i];
                B(0) = 0;
                B(1) = cut[i] * cut[i];
                math::invert(I-SAMPLING_TIME/2*A,A_inv);
                oldX(0) = oldXs(i,0);
                oldX(1) = oldXs(i,1);
                X = prod(prod(A_inv,(I+SAMPLING_TIME/2*A)),oldX)+SAMPLING_TIME/2*prod(A_inv,B)*(pos(i)+oldpos(i));
                oldXs(i,0) = X(0);
                oldXs(i,1) = X(1);
                pos(i) = X(0);
                vel(i) = X(1);
                acc(i) = A(1,0)*X(0) + A(1,1)*X(1) + cut[i]*cut[i]*pos(i);*/
            }else{
                // diff
                vel(i) = (pos(i) - oldpos(i)) / SAMPLING_TIME;
                acc(i) = (vel(i) - oldvel(i)) / SAMPLING_TIME;

            }

    }

}

iocda::iocda(){
    oldpos.resize(NUM_ACTUATOR);
    oldvel.resize(NUM_ACTUATOR);
    cnt.resize(NUM_COUNTER);
    cnt2.resize(NUM_ACTUATOR);
    resolution.resize(NUM_COUNTER);
    dir.resize(NUM_COUNTER);
    cut.resize(NUM_COUNTER);

    resolution(0)=RESONATE_LINER_ENC_X;
    resolution(1)=RESONATE_LINER_ENC_Y1;
    resolution(2)=RESONATE_LINER_ENC_Y2;
    resolution(3)=RESONATE_LINER_ENC_Z;
    resolution(4)=RESONATE_ROTATION_ENC_C;
    resolution(5)=RESONATE_ROTATION_ENC_A1;
    resolution(6)=RESONATE_ROTATION_ENC_A2;

    cut(0)=CUTOFF_FREC_X;
    cut(1)=CUTOFF_FREC_Y1;
    cut(2)=CUTOFF_FREC_Y2;
    cut(3)=CUTOFF_FREC_Z;
    cut(4)=CUTOFF_FREC_C;
    cut(5)=CUTOFF_FREC_A1;
    cut(6)=CUTOFF_FREC_A2;

    dir(0)=-1;
    dir(1)= 1;
    dir(2)=-1;
    dir(3)=-1;
    dir(4)= 1;
    dir(5)= 1;
    dir(6)=-1;
}
