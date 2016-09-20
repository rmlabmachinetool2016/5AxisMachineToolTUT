#include "stdafx.h"
#include "control2D.h"
#include "LIB/math.hpp"
#include <cmath>
#include <fstream>
#include <QApplication>
//#include "LIB/numeric.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>


typedef boost::numeric::ublas::vector<double> bstvector;
typedef boost::numeric::ublas::matrix<double> bstmatrix;
typedef boost::numeric::ublas::matrix_column<bstmatrix> matcol;
typedef boost::numeric::ublas::matrix_row<bstmatrix> matrow;

con2dvariable::con2dvariable(){

}

control2d::control2d(){


    AP.theta.resize(5);
    AP.theta2.resize(4);

    //AP.xi.resize(5);
    //AP.xi2.resize(4);

    AP.AdaGain.resize(5,5);
    AP.AdaGain.clear();


    ///////////////////////////////////



    ///////////////////////////////////



    AP.theta(0) = 0.04;

    AP.AdaGain = identity_matrix<double>(5);
    AP.AdaGain = 0.01*AP.AdaGain;
    AP.alpha.resize(9);
    AP.toro.resize(2);
    AP.ReqAcc.resize(2);
    AP.alpha2.resize(10);
    AP.toro2.resize(10);
    AP.ReqAcc2.resize(2);

    AP.alpha(0)= 0.9;
    AP.alpha2(0)= 0.9;
    coordi.ew.resize(6);
    coordi.rpos.resize(2);
    coordi.rvel.resize(2);
    coordi.racc.resize(2);
    coordi.pos.resize(2);
    coordi.vel.resize(2);
    coordi.acc.resize(2);



}

void control2dSim::ControlSim2D(unsigned int control_type_,
						unsigned int max_step,
						bool enable_noise,
                        bool enable_resolution
                        )
{

control_type=control_type_;

ControlAll(max_step,enable_noise,enable_resolution,control_type_);



}


void control2d::SetConParam(std::vector<double> *conparam
                            , std::vector<double> *conparam2)
{
    this->load_mat();
    int controlType = (*conparam2)[11];

    max_step = (unsigned int)(*conparam2)[14];
    //pole_y2	= (*conparam)[16]; //not use

    MP.My_L		= (*conparam2)[0];
    MP.My_T		= (*conparam2)[1];
    MP.My_T1		= (*conparam2)[2];
    MP.My_T3       = MP.My_T1;
    MP.My_a1		= (*conparam2)[3];
    MP.My_a2		= (*conparam2)[4];
    MP.My_a3		= (*conparam2)[5];
    MP.My_x0		= (*conparam2)[6];
    MP.My_x1		= (*conparam2)[7];
    MP.My_v		= (*conparam2)[8];
    trajectory_num = (int)(*conparam2)[9];
    axis_rotation = (*conparam2)[10]*2*PI/360;
    control_type = (int)(*conparam2)[11];
    enable_datalog = true;

    CP.mass.resize(2,2);
    CP.c.resize(2,2);
    CP.kpw.resize(2,2);
    CP.kvw.resize(2,2);
    CP.kpl.resize(2,2);
    CP.kvl.resize(2,2);
    CP.mass.clear();
    CP.c.clear();
    CP.kpw.clear();
    CP.kvw.clear();
    CP.kpl.clear();
    CP.kvl.clear();
    CP.K.resize(2,4);
    CP.mass(0,0) = (*conparam)[0];
    CP.mass(1,1) = (*conparam)[1];
    CP.c(0,0) = (*conparam)[7];
    CP.c(1,1) = (*conparam)[8];
    math::invert(CP.mass,CP.invmass);

    CP.kpw(0,0) = pow((*conparam)[14],2);
    CP.kpw(1,1) = pow((*conparam)[15],2);
    CP.kvw(0,0) = 2 * (*conparam)[14];
    CP.kvw(1,1) = 2 * (*conparam)[15];

    CP.kpl(0,0) = pow((*conparam)[21],2);
    CP.kpl(1,1) = pow((*conparam)[22],2);
    CP.kvl(0,0) = 2 * (*conparam)[21];
    CP.kvl(1,1) = 2 * (*conparam)[22];

    masss = (*conparam)[2];
    cs = (*conparam)[9];
    kvs = 2 * (*conparam)[27];
    kps = pow((*conparam)[27],2);
	
    stepcount = 0;

    switch(controlType){
        case INDEPENDENT:
        case 3:
        case 6:
            subrange(CP.K,0,2,0,2)= -1.0*CP.kpw;
            subrange(CP.K,0,2,2,4)= -1.0*CP.kvw;
        break;

        case CONTOURING:
        case 4:
            subrange(CP.K,0,2,0,2)= -1.0*CP.kpl;
            subrange(CP.K,0,2,2,4)= -1.0*CP.kvl;

        break;

        case MOD_CONTOURING:
        case 5:
            /*modContouringController(coordi,u1,time);
            FfAcc = u1;
            if(time == 0)ReqAcc(0)=0;ReqAcc(1)=0;*/
        break;

    }

    if(controlType<3)CP.AdapFlag = false;
    else CP.AdapFlag = true;

    Ready();

    coordi.rpos(0)=0;
    coordi.rvel(0)=0;
    coordi.rvel(0)=0;


    //AP Param
    int n=1,m=0;
    AP.Outpara1.resize(max_step);
    AP.Outpara1.clear();

    AP.estimated_val.resize(m+n+1,max_step);
    AP.estimated_val.clear();

    AP.estimated_val(0,0)=1.0;//0.0000094/25.175;
    AP.estimated_val(1,0)=0;//0.0000094/25.175;
    //AP.estimated_val(2,0)=2;//1.99059794920982;
    //AP.estimated_val(3,0)=-1;-0.990597949209822;


AdapCon.SetProfile(&MP.preprofile,datalog,datalog2);

SW1 = false;
    //Uchiyama sensei kara-
    d  = 1;//muda
    n  = 2;//A(z^-1) dim
    nb = 0;//B(z^-1) dim
    nf = 5;//F(z^-1)r(k) = 0
    nd = 2;//bias dist
    m  = 1;//zero point
    nc = 3;//C(z^-1)e(k)---->0


    nr = m+d-1;
    np = nb+nd+nr;



    if(nf-1<=nc-m-d)nq = nc-m-d;
    else            nq = nf-1;

    if(n+nd-1<=nc-m-d)ns = nc-m-d;
    else            ns = n+nd-1;

std::cout<<"nr   "<<nr<<"   np    "<<np<<"     nq     "
        <<nq<<"    ns      "<<ns<<std::endl;

    AP.xi1.resize(nq+1);
    AP.xi2.resize(ns+np+2);
    AP.xi2.clear();


    AP.theta_1.resize(nq+1);
    AP.theta_2.resize(ns+np+2);

    AP.input.resize(np);
    AP.output.resize(ns+1);
    AP.ref.resize(nq+1);

    AP.theta_1.clear();
    AP.theta_2.clear();
    AP.theta_2(0) = pow(0.1,8);
    AP.theta_2(1) = 0.0;
    AP.theta_2(2) = 0;
    AP.theta_2(3) = 0;


    AP.Gain1 = identity_matrix<double>(nq+1);
    AP.Gain2 = identity_matrix<double>(ns+np+2);
/*
    AP.Gain1 = 100000*AP.Gain1;
    AP.Gain2 = 10*AP.Gain2;*/
if(define::SAMPLING_TIME==0.0002){
    AP.Gain1 = 100000000*AP.Gain1;
    AP.Gain2 = 100000*AP.Gain2;
}
else {
    AP.Gain1 = 100000000*AP.Gain1;
    AP.Gain2 = 1000000*AP.Gain2;
}

AdapCon.LoadFormParameter(conparam,conparam2);

}

bool control2d::IsReachPoint(double time,double max_angle)
{
	volatile double sdot,rlength,rangle,
					x,y,xdot,ydot;
	volatile static double len,total_angle,oldsdot;
	unsigned int step = static_cast<unsigned int>(time/SAMPLING_TIME);

	rlength = max_angle/360.*2.*RADIUS*PI;
	rangle = max_angle * PI/180.;

	if(time == 0){
		oldsdot = 0;
		len = 0;
		total_angle = 0;
	}

    xdot = (*datalog)(14,step);
    ydot = (*datalog)(22,step);

	sdot = sqrt(xdot*xdot + ydot*ydot);
	if(time==0)
		len=0;
	else
		len += (sdot+oldsdot)*SAMPLING_TIME/2;
	oldsdot = sdot;
	total_angle = len / RADIUS;

	bool is_angle;
    is_angle = (rangle*0.99<total_angle)?true:false;
    x = (*datalog)(13,step);
    y = (*datalog)(21,step);

	volatile bool is_time;
	is_time = time>(rangle/2/PI)?true:false;

	if(is_angle && x>0 && y<0 && is_time)
		return true;
	else
		return false;
}

void control2d::GenRef(double time,coordi2D &coordi)
{

    switch (trajectory_num){
        case 0:
            eq_tool(time,coordi);
			break;
		case 1:
            eq_xaxis(time,coordi);
			break;
		case 2:
            //  empty slot
			break;
		case 3:
            //eq_yaxis(time,coordi,rvel,racc);
			break;
		case 4:
            eq_mat(time,coordi);
			break;
		case 5:
            //eq_cxaxisvel(time,coordi,rvel,racc);
            break;
	}


}







double control2d::CalcContouringError(bstvector &pos, bool Reverse)
{
(void)Reverse;
    double x1,x2,y1;

    double L,ec;
    x1 = 0;ec = 1000;

///極地付近局所的収束怖い
    for(int i=0;i<1000;i++){
        x1 += MP.My_x1/1000;
        y1 = MP.My_a3*pow(x1,3)+MP.My_a2*pow(x1,2)+MP.My_a1*x1;
        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }
    x1 = x2-MP.My_x1/1000*3;
    for(int i=0;i<1000;i++){
        x1 += MP.My_x1/pow(10,5);
        y1 = MP.My_a3*pow(x1,3)+MP.My_a2*pow(x1,2)+MP.My_a1*x1;
        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }
    x1 = x2-MP.My_x1/100000*3;
    for(int i=0;i<1000;i++){
        x1 += MP.My_x1/pow(10,7);
        y1 = MP.My_a3*pow(x1,3)+MP.My_a2*pow(x1,2)+MP.My_a1*x1;
        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }
    x1 = x2-MP.My_x1/10000000*3;
    for(int i=0;i<1000;i++){
        x1 += MP.My_x1/pow(10,9);
        y1 = MP.My_a3*pow(x1,3)+MP.My_a2*pow(x1,2)+MP.My_a1*x1;
        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }
    return ec;
/*    double ec,x,y;

    x = pos(0);
    y = pos(1);
    ec = sqrt( x*x+y*y ) - RADIUS;*/


    //return ec;
}


void control2d::CalcRotationMat(double time
                                , bstmatrix &Rot
                                , bstmatrix &Rot1
                                , bstmatrix &Rot2)
{
    (void)time;/* circle
    double theta = OMG * time;

    Rot(0,0) =  cos(theta);
    Rot(0,1) = -sin(theta);
    Rot(1,0) =  sin(theta);
    Rot(1,1) =  cos(theta);

    Rot1(0,0) = -OMG * sin(theta);
    Rot1(0,1) = -OMG * cos(theta);
    Rot1(1,0) =  OMG * cos(theta);
    Rot1(1,1) = -OMG * sin(theta);

    Rot2(0,0) = -OMG * OMG * cos(theta);
    Rot2(0,1) =  OMG * OMG * sin(theta);
    Rot2(1,0) = -OMG * OMG * sin(theta);
    Rot2(1,1) = -OMG * OMG * cos(theta);*/
    double theta = global_theta;
    double theta2 = global_theta2;
    double theta3 = global_theta3;

    Rot(0,0) =  cos(theta);
    Rot(0,1) = -sin(theta);
    Rot(1,0) =  sin(theta);
    Rot(1,1) =  cos(theta);

    Rot1(0,0) = -theta2 * sin(theta);
    Rot1(0,1) = -theta2 * cos(theta);
    Rot1(1,0) =  theta2 * cos(theta);
    Rot1(1,1) = -theta2 * sin(theta);

    Rot2(0,0) = -theta3 * sin(theta) - pow(theta2,2)*cos(theta);
    Rot2(0,1) = -theta3 * cos(theta) + pow(theta2,2)*sin(theta);
    Rot2(1,0) =  theta3 * cos(theta) - pow(theta2,2)*sin(theta);
    Rot2(1,1) = -theta3 * sin(theta) - pow(theta2,2)*cos(theta);

}



void control2dSim::ControlAll(unsigned int max_step
                              ,bool enable_noise
                              ,bool enable_resolution
                              ,int controlType){

    unsigned int step,i,j;

    plant1.datalog = datalog;

    for(step = 0;step < max_step;step++)
    {
        time = step * SAMPLING_TIME;

        rpos_c = coordi.rpos;
        rvel_c = coordi.rvel;
        racc_c = coordi.racc;

        IOcda.GetStateVariable(time,plant1,enable_resolution,posall,velall,accall);
        IOcda.LPF(posall,velall,accall);

        posall_raw = posall;
        velall_raw = velall;
        accall_raw = accall;

        diff_rear(step,posall,velall,accall);
        //if(step>6)SGfil.calcA(step-5,datalog,posall,velall,accall);//high cost

        coordi.pos = subrange(posall,0,2);
        coordi.vel = subrange(velall,0,2);
        coordi.acc = subrange(accall,0,2);

        subrange(coordi.ew,0,2) = coordi.pos - coordi.rpos;
        subrange(coordi.ew,2,4) = coordi.vel - coordi.rvel;
        subrange(coordi.ew,4,6) = coordi.acc - coordi.racc;

        es = posall(2) -coordi.pos(1);
        es1 = velall(2) - coordi.vel(1);
        es2 = accall(2) - coordi.acc(1);

    if(step<max_step-1){
            coordi.rpos = subrange(column(MP.preprofile,step+1),0,2);
            coordi.rvel = subrange(column(MP.preprofile,step+1),2,4);
            coordi.racc = subrange(column(MP.preprofile,step+1),4,6);
    }
        switch(controlType){
            case INDEPENDENT:
            case 3:
                ICon(coordi,u1);
            break;

            case CONTOURING:
            case 4:
                ContouringController(coordi,u1,time);
            break;

            case MOD_CONTOURING:
            case 5:
                MCCon(coordi,u1,time);
                if(time == 0){u1(0)=0;u1(1)=0;}
            break;
            case 6:
                //gomi //MRACon2(step,force,coordi.pos,coordi.rpos);
                //if(step>0&&step<max_step-2)MRACon3(step,force,coordi.pos,coordi.rpos);

                //if(step>15&&step<max_step-2)MRACon4(step,force,coordi.pos);
                if(step>15&&step<max_step-2)AdapCon.MRACS_LZ(step,force,coordi.pos);
            break;
        }


/*
        if (CP.AdapFlag){
            u1 += coordi.racc;
            MRACon(step-5,force,coordi.acc,u1);
        }*/
        //else force = prod(CP.mass,u1+racc_c)+prod(CP.c,coordi.vel);

        if(step<20000){
            ICon(coordi,u1);
            force = prod(CP.mass,u1+racc_c)+prod(CP.c,coordi.vel);}//rinzi


        subrange(forceall,0,2)=force;

        forceall(2) = force(1)+masss*( -kvs*es1-kps*es ) + cs*es1; //sync

        IOcda.OutputControlVariable(enable_resolution,forceall);


        //ec = CalcContouringError(pos,false);//debug
        subrange(rpos_log,0,2)=rpos_c;
        subrange(rvel_log,0,2)=rvel_c;
        subrange(racc_log,0,2)=racc_c;
        subrange(pos_log,0,2)=coordi.pos;
        subrange(racc_log,0,2)=racc_c;
        subrange(vel_log,0,2)=coordi.vel;
        subrange(acc_log,0,2)=coordi.acc;
        subrange(ew_log,0,2)=coordi.pos-rpos_c;

        rpos_log(2) = coordi.rpos(1);
        rvel_log(2) = coordi.rvel(1);
        racc_log(2) = coordi.racc(1);
        pos_log(2) = posall_raw(2);
        vel_log(2) = velall_raw(2);
        acc_log(2) = accall_raw(2);
        ew_log(2) = posall_raw(2) - rpos_c(1);



        (*datalog)(0,step) = time;
        (*datalog)(1,step) = forces;
        //(*datalog)(2,step) = 0;	//ec-en
        //(*datalog)(3,step) = AP.Outpara1(step);	//ec-enmod

        (*datalog)(4,step) =AP.theta_2(0);	//td
        (*datalog)(5,step) =AP.theta_2(1);	//el t
        (*datalog)(6,step) =AP.theta_2(2);	//el n
        (*datalog)(7,step) =AP.theta_2(3);	//el b
        //(*datalog)(8,step) =AP.theta_1(4);	//el b
        //(*datalog)(9,step) =AP.theta_1(5);
        /*
        (*datalog)(4,step) = AP.estimated_val(0,step);	//td
        (*datalog)(5,step) = AP.estimated_val(1,step);	//el t
        (*datalog)(6,step) =AP.estimated_val(2,step);	//el n
        (*datalog)(7,step) =AP.estimated_val(3,step);	//el b
*/
        //(*datalog)(9,step) = AP.theta(5);	//es a*/
        for(i=0,j=0;i<NUM_ACTUATOR;i++,j+=8){
            (*datalog)(j+10,step) = rpos_log(i);
            (*datalog)(j+11,step) = rvel_log(i);
            (*datalog)(j+12,step) = racc_log(i);
            (*datalog)(j+13,step) = pos_log(i);
            (*datalog)(j+14,step) = vel_log(i);
            (*datalog)(j+15,step) = acc_log(i);
            (*datalog)(j+16,step) = forceall(i);
            (*datalog)(j+17,step) = ew_log(i);
        }
           plant1.plantmodel(step,forceall,enable_noise);
    }


        //std::cout<<AP.estimated_val<<std::endl;
   // std::cout<<AP.AdaGain<<std::endl;

}

void control2d::ICon(coordi2D &coordi,vector<double> &u1){

    u1 = prod(CP.K,subrange(coordi.ew,0,4));
}

void control2d::ContouringController(coordi2D &coordi
                                        ,vector<double> &ReqAcc
                                        ,double time){
    matrix<double>	Rot(2,2),Rot1(Rot),Rot2(Rot),
                    tRot,tRot1,tRot2;
    vector<double>	el(4);

    // transform error
    CalcRotationMat(time,Rot,Rot1,Rot2);
    tRot = trans(Rot);
    tRot1 = trans(Rot1);
    tRot2 = trans(Rot2);

    subrange(el,0,2) = prod(tRot,subrange(coordi.ew,0,2));
    subrange(el,2,4) = prod(tRot1,subrange(coordi.ew,0,2)) + prod(tRot,subrange(coordi.ew,2,4));

    ReqAcc = prod(Rot,prod(CP.K,el) + prod(tRot2,subrange(coordi.ew,0,2))
                   + 2*prod(tRot1,subrange(coordi.ew,2,4)));
}

void control2d::SynthForce(bstvector &force
                            ,bstvector &FfAcc
                            ,bstvector &FbAcc){
    (void)force;
    (void)FfAcc;
    (void)FbAcc;
/*
    bstvector FbForce(force),FfForce(force);

    FbForce = prod(mass,FbAcc) + prod(c,coordi.ew1);

    if (Adaptive) AdaptiveController(step,FfForce,accraw,FfAcc);
        else FfForce = prod(mass,FfAcc) + prod(c,coordi.rvel);

    if(step<50)FfForce = prod(mass,FfAcc) + prod(c,coordi.rvel);

    force = FfForce + FbForce;*/


}


void control2d::MCCon(coordi2D& coordinate
                                           ,vector<double> &ReqAcc
                                           ,double time){

    matrix<double>	Rot(2,2),Rot1(Rot),Rot2(Rot),
            tRot,tRot1,tRot2,
            Rota(Rot),Rota1(Rota),Rota2(Rota),
            tRota,tRota1,tRota2,

            Q(Rot),Q1(Q),Q2(Q),S(Q);
    vector<double>	el(2),el1(el),el2(el),
            ewn(2),ewn1(ewn),ewn2(ewn),
            ela(2),ela1(ela),ela2(ela),
            rposa(2),rvela(rposa),racca(rposa),
            rposn(rposa),rveln(rposn),raccn(rposn);
    coordi2D *p;
    p = &coordinate;
    double			td,dv,step;
    step = time / SAMPLING_TIME;



    // transform error
    CalcRotationMat(time,Rot,Rot1,Rot2);
    tRot = trans(Rot);
    tRot1 = trans(Rot1);
    tRot2 = trans(Rot2);
    el = prod(tRot,p->ew);
    el1 = prod(tRot1,p->ew) + prod(tRot,p->ew1);
    el2 = prod(tRot2,p->ew) + 2*prod(tRot1,p->ew1) + prod(tRot,p->ew2);

    // calculation delay time
    dv = norm_2(p->rvel);	//OMG * RADIUS;
    if(dv==0)td=0;
    else td = -el(0) / dv;

    // calculation r^a
    //GenerateReference(time-td,rposa,rvela,racca);
    if(step > 0){
    rposa(0) = (*datalog)(10,step-1) + ((*datalog)(10,step-1)-p->rpos(0))*(SAMPLING_TIME-td)/SAMPLING_TIME;
    rposa(1) = (*datalog)(18,step-1) + ((*datalog)(18,step-1)-p->rpos(1))*(SAMPLING_TIME-td)/SAMPLING_TIME;

    rvela(0) = (*datalog)(11,step-1) + ((*datalog)(11,step-1)-p->rvel(0))*(SAMPLING_TIME-td)/SAMPLING_TIME;
    rvela(1) = (*datalog)(19,step-1) + ((*datalog)(19,step-1)-p->rvel(1))*(SAMPLING_TIME-td)/SAMPLING_TIME;

    racca(0) = (*datalog)(12,step-1) + ((*datalog)(12,step-1)-ReqAcc(0))*(SAMPLING_TIME-td)/SAMPLING_TIME;
    racca(1) = (*datalog)(20,step-1) + ((*datalog)(20,step-1)-ReqAcc(1))*(SAMPLING_TIME-td)/SAMPLING_TIME;
}
    // calculation rn
    CalcRotationMat(time-td,Rota,Rota1,Rota2);
    tRota = trans(Rota);
    tRota1 = trans(Rota1);
    tRota2 = trans(Rota2);

    S.clear();
    S(1,1) = 1;
    Q = prod((matrix<double>)prod(Rota,S),tRota);
    Q1 = prod((matrix<double>)prod(Rota1,S),tRota)
            + prod((matrix<double>)prod(Rota,S),tRota1);
    Q2 = prod((matrix<double>)prod(Rota2,S),tRota)
            + 2 * prod((matrix<double>)prod(Rota1,S),tRota1)
            + prod((matrix<double>)prod(Rota,S),tRota2);

    rposn = p->rpos + prod(Q,(rposa - p->rpos));
    rveln = p->rvel + prod(Q1,(rposa - p->rpos))
            + prod(Q,(rvela - p->rvel));
    raccn = p->racc + prod(Q2,(rposa - p->rpos))
            + 2*prod(Q1,(rvela - p->rvel)) + prod(Q,(racca - p->racc));

    ewn = p->pos - rposn;
    ewn1 = p->vel - rveln;
    ewn2 = p->acc - raccn;

    ela = prod(tRota,ewn);
    ela1 = prod(tRota1,ewn) + prod(tRota,ewn1);
    ela2 = prod(tRota2,ewn) + 2*prod(tRota1,ewn1) + prod(tRota,ewn2);

    // calculation control value
    ReqAcc = prod(Rota,-prod(CP.kvl,ela1) - prod(CP.kpl,ela)
                  + prod(tRota2,ewn) + 2*prod(tRota1,ewn1));
}


void control2d::eq_tool(double time,coordi2D &coordi)
{


                    double T  = MP.My_T;
                    double L = MP.My_L;
                    double My_T2 = T - 2 * MP.My_T1;
                    double x1 = MP.My_x1;
                    double rposx_,rvelx_,raccx_;
                    double count;
                    count = floor(time/T);
                    /*
                    double logrposx = (*datalog)rposx;
                    double logrvelx = (*datalog)rvelx;
                    double lograccx = (*datalog)raccx;
                    */

                    double logrposx = coordi.rpos(0);
                    double logrvelx = coordi.rvel(0);
                    double lograccx = coordi.racc(0);


                    if(fmod(count,2.0)==1){
                        logrposx = x1-coordi.rpos(0);
                        logrvelx = -coordi.rvel(0);
                        lograccx = -coordi.racc(0);}


                    double theta,vel,Dx_y,Dx2_y,Dx3_y,Dt_vel,Dx_theta,dt_x,dt2_x
                            ,dt_theta,d2x_theta,dt2_theta;
                    double v ;
                    double cosRot,sinRot;
                    double pretime = time - count*T;

                    if(fmod(time,T)==0){logrposx=0;logrvelx = 0;}
                    if (MP.My_v >0){v = MP.My_v;}
                    else v = L / (T - MP.My_T1);



                    if (pretime<MP.My_T1)
                    {
                        vel = v/MP.My_T1*pretime;
                        Dt_vel = v/MP.My_T1;

                    }
                    else{
                        if (pretime<MP.My_T1 + My_T2)
                        {
                            vel = v;
                            Dt_vel = 0;
                        }
                        else{
                            if (pretime<MP.My_T1 + My_T2 + MP.My_T3){
                                vel = v/MP.My_T3*(MP.My_T1+My_T2+MP.My_T3-pretime);
                                Dt_vel = -v/MP.My_T3;
                            }

                        }
                    }


                    /*

                    if (pretime<t1)
                    {
                        vel = v*0.5*(1 - cos(OMG1*pretime));
                        Dt_vel = v*0.5*OMG1*sin(OMG1*pretime);

                    }
                    else{
                        if (pretime<t1 + t2)
                        {
                            vel = v;
                            Dt_vel = 0;
                        }
                        else{
                            if (pretime<t1 + t2 + t3){
                                vel = v*0.5*(1 + cos(OMG3*(pretime - t1 - t2)));
                                Dt_vel = -v*0.5*OMG3*sin(OMG3*(pretime-t1-t2));
                            }

                        }
                    }

                    */

                    //if (time <=0){coordi.rpos(0)=0;coordi.rpos(1)=0;}//initialize
                    dt_x = (logrvelx + 0.5*SAMPLING_TIME*lograccx);///
                    coordi.rpos(0) = logrposx + dt_x*SAMPLING_TIME;

                    //if ( coordi.rpos(0)==logrposx){coordi.rpos(0)+=0.00001;}//停止防止

                    coordi.rpos(1) = MP.My_a3*coordi.rpos(0)*coordi.rpos(0)*coordi.rpos(0) + MP.My_a2*coordi.rpos(0)*coordi.rpos(0) + MP.My_a1*coordi.rpos(0);

                    Dx_y = 3 * MP.My_a3*coordi.rpos(0)*coordi.rpos(0) + 2 * MP.My_a2*coordi.rpos(0) + MP.My_a1;//radian　katamuki
                    Dx2_y = 6*MP.My_a3*coordi.rpos(0)+2*MP.My_a2;
                    Dx3_y = 6*MP.My_a3;

                    theta = atan(Dx_y);

                    Dx_theta = Dx2_y/(1+pow(Dx_y,2));
                    dt_x = vel*cos(theta);
                    dt_theta = Dx_theta*dt_x;

                    dt2_x = Dt_vel*cos(theta);//acc

                    //d2x_theta = Dx3_y*(-2)*Dx_y/pow(1+pow(Dx_y,2),2);//error
                    d2x_theta = Dx3_y/(1+pow(Dx_y,2))-2*Dx_y*Dx2_y/pow(1+pow(Dx_y,2),2);//dxtheta no bibun
                    dt2_theta = d2x_theta*dt2_x;


                    global_theta = theta;
                    global_theta2 = dt_theta;
                    global_theta3 = dt2_theta;

                        coordi.rvel(0) = vel*cos(theta);

                    //coordi.rvel(0) =logrvelx + 0.5*SAMPLING_TIME*lograccx;

                        coordi.racc(0) = Dt_vel*cos(theta) - vel*dt_theta*sin(theta);
                    //theory
                        //coordi.racc(0) = vel*(cos(theta+dt_theta)-cos(theta))/0.002;not_theory
                        coordi.rvel(1) = tan(theta)*coordi.rvel(0);
                        coordi.racc(1) = tan(theta)*coordi.racc(0) + dt_theta/pow(cos(theta),2)*coordi.rvel(0);


                        if(fmod(count,2.0)==1){
                            coordi.rpos(0) = x1-coordi.rpos(0);coordi.rvel(0)=-coordi.rvel(0);coordi.racc(0)=-coordi.racc(0);

                            global_theta = PI-theta;
                            global_theta2 = -dt_theta;
                            global_theta3 = -dt2_theta;}

                        rposx_ = coordi.rpos(0);
                        cosRot=cos(axis_rotation);
                        sinRot=sin(axis_rotation);
                        coordi.rpos(0) = coordi.rpos(0)*cosRot+coordi.rpos(1)*sinRot;
                        coordi.rpos(1) = -rposx_*sinRot+coordi.rpos(1)*cosRot;

                        rvelx_ = coordi.rvel(0);
                        coordi.rvel(0) = coordi.rvel(0)*cosRot+coordi.rvel(1)*sinRot;
                        coordi.rvel(1) = -rvelx_*sinRot+coordi.rvel(1)*cosRot;

                        raccx_ = coordi.racc(0);
                        coordi.racc(0) = coordi.racc(0)*cosRot+coordi.racc(1)*sinRot;
                        coordi.racc(1) = -raccx_*sinRot+coordi.racc(1)*cosRot;

                        //(*datalog)theta = theta;
                        //(*datalog)v = v;

                        //if (time >0.40){Debug::WriteLine(theta);}
                        //Debug::WriteLine(a1);
                        //data = dt_theta;///3rd line
                        //data1 = vel*dt_theta*sin(theta);//4th line


}

void control2d::eq_xaxis(double time,coordi2D &coordi)
{



                double rposx_,rvelx_,raccx_;
                double T = MP.My_T;
                double t1 = MP.My_T1;

//                double t3 = MP.My_T3;
                double t3 = t1;
                double t2 = T -t1-t3;
                double a1 = MP.My_a1;
                double a2 = MP.My_a2;
                double a3 = MP.My_a3;
                double x1 = MP.My_x1;
                double count;
                count = floor(time/T);
                double D_y,D2_y;//vel 工具速度

                //double OMG1 = PI / t1;
                //double OMG3 = PI / t3;
                double v ;
                double pretime = time - count*T;
                v = x1 / (T -(t1+t3)/2);
                //Debug::WriteLine(x1);




                    if (pretime<MP.My_T1)
                    {
                        coordi.racc(0) = v/MP.My_T1;
                        coordi.rvel(0) = coordi.racc(0)*pretime;
                        coordi.rpos(0) = 0.5*pretime*coordi.rvel(0);
                    }
                    else
                        if (pretime<MP.My_T1 + t2)
                        {
                            coordi.rpos(0) = (0.5*MP.My_T1+(pretime-MP.My_T1))*v;
                            coordi.rvel(0) = v;
                            coordi.racc(0) = 0;
                        }
                        else{
                            if (pretime<T){
                                coordi.racc(0) = -v/t3;
                                coordi.rvel(0) =v+coordi.racc(0)*(pretime-MP.My_T1-t2);
                                coordi.rpos(0) = v*t2+0.5*((t3+t1)*v-(T-pretime)*coordi.rvel(0));
                            }

                        }


                /*
                //S字速度軌道
                if (pretime<t1)
                {
                    coordi.rpos(0) = v*0.5*(pretime-sin(OMG1*pretime)/OMG1);
                    coordi.rvel(0) = v*0.5*(1-cos(OMG1*pretime));
                    coordi.racc(0) = v*0.5*OMG1*sin(OMG1*pretime);

                }
                else{
                    if (pretime<t1 + t2)
                    {
                        coordi.rpos(0) = 0.5*v*t1 + v*(pretime-t1) ;
                        coordi.rvel(0)= v;
                        coordi.racc(0) = 0;

                    }
                    else{
                        if (pretime<t1 + t2 + t3){
                            coordi.rpos(0) = 0.5*v*t1 + v*t2 + 0.5*v*( (pretime-t1-t2) + ( sin(OMG3*( pretime-t1-t2 )) )/ OMG3);
                            coordi.rvel(0) = v*0.5*(1 + cos(OMG3*(pretime - t1 - t2)));
                            coordi.racc(0) = -v*0.5*OMG3*sin(OMG3*(pretime-t1-t2));
                        }

                    }
                }*/

                    D_y = 3 * a3*coordi.rpos(0)*coordi.rpos(0) + 2 * a2*coordi.rpos(0) + a1;
                    D2_y = 6*a3*coordi.rpos(0)+2*a2;

                    coordi.rpos(1) = a3*coordi.rpos(0)*coordi.rpos(0)*coordi.rpos(0) + a2*coordi.rpos(0)*coordi.rpos(0) + a1*coordi.rpos(0);
                    coordi.rvel(1) = D_y*coordi.rvel(0);
                    coordi.racc(1) = D_y*coordi.racc(0) + D2_y*coordi.rvel(0)*coordi.rvel(0);
                    if(fmod(count,2.0)==1){coordi.rpos(0) = x1-coordi.rpos(0);coordi.rvel(0)=-coordi.rvel(0);coordi.racc(0)=-coordi.racc(0);}

                        rposx_ = coordi.rpos(0);
                        coordi.rpos(0) = coordi.rpos(0)*cos(axis_rotation)+coordi.rpos(1)*sin(axis_rotation);
                        coordi.rpos(1) = -rposx_*sin(axis_rotation)+coordi.rpos(1)*cos(axis_rotation);

                        rvelx_ = coordi.rvel(0);
                        coordi.rvel(0) = coordi.rvel(0)*cos(axis_rotation)+coordi.rvel(1)*sin(axis_rotation);
                        coordi.rvel(1) = -rvelx_*sin(axis_rotation)+coordi.rvel(1)*cos(axis_rotation);

                        raccx_ = coordi.racc(0);
                        coordi.racc(0) = coordi.racc(0)*cos(axis_rotation)+coordi.racc(1)*sin(axis_rotation);
                        coordi.racc(1) = -raccx_*sin(axis_rotation)+coordi.racc(1)*cos(axis_rotation);
                    //if (time >0.40){Debug::WriteLine(theta);}


}

void control2d::eq_yaxis(double time,coordi2D &coordi)
{


            double extime1,extime2;//極値に達する時間
            //    double extime_kyoyou = 0.25;
            double n_extime,n_t1,count;//精度
            double nowtime;
            double t1_1,t2_1,t3_1;//加速時間
            double T = MP.My_T;
            //double L = MP.My_L;
            double t1 = MP.My_T1;
            double t2 = T - 2 * t1;
            double t3 = MP.My_T1;
            double a1 = MP.My_a1;
            double a2 = MP.My_a2;
            double a3 = MP.My_a3;
            //double x0 = MP.My_x0;
            double x1 = MP.My_x1;
            double D_y,D2_y;//vel 工具速度
            double OMG1 = PI / t1;
            double OMG3 = PI / t3;
            double v=x1 / (T - t1) ;
            double theta;
            double rposx,rvelx,raccx,rposy,rvely,raccy,nextrposy
                    ,nextrvely,nextraccy,nextrposx,re_nextrposy,maxrposx,minrposx;
            double dt_dx;
            double next_rvelx,next_D_y;
            //double ex_interval=1;//極値における停止時間（ステップ数）
    extime1 = 0.5;extime2 = 1.4;t1_1 = 0.2;t2_1 = 0.3;t3_1 = 0.25;
    nowtime = time;rposx = coordi.rpos(0);

    if(nowtime == 0){rposx = 0;rposy = 0;rvelx=0;raccx = 0;
                        rposx = 0;rvelx = 0;raccx = 0;nextrposx=0;
                        rposy = 0;rvely=0;raccy = 0;}//初期化

if(time == 0){rposx = 0;rvelx = 0;raccx = 0;nextrposx=0;}
    n_extime= 0.002;n_t1=0.002;
    T=MP.My_T;
    double ex1_posx,ex2_posx,ex1_posy,ex2_posy;
    ex1_posx = 1.0;
    ex2_posx = 2.0;
    ex1_posy = MP.My_a1*ex1_posx+MP.My_a2*pow(ex1_posx,2)
            +MP.My_a3*pow(ex1_posx,3);

    ex2_posy = MP.My_a1*ex2_posx+MP.My_a2*pow(ex2_posx,2)
            +MP.My_a3*pow(ex2_posx,3);

 //一つ目 rposx < ex1_posx

            if (nowtime < extime1){
                OMG1 = PI / t1_1;OMG3 = PI/t1_1;
                v = ex1_posy/(extime1-t1_1);
                t2 = extime1-2*t1_1;
                    if (nowtime<t1_1)
                {
                    rposy = v*0.5*(nowtime-sin(OMG1*nowtime)/OMG1);
                    rvely = v*0.5*(1-cos(OMG1*nowtime));
                    raccy = v*0.5*OMG1*sin(OMG1*nowtime);

                }
                else{
                    if (nowtime<t1_1+t2)
                    {
                        rposy = 0.5*v*t1_1 + v*(nowtime-t1_1) ;
                        rvely= v;
                        raccy = 0;

                    }
                    else{
                        if (nowtime<extime1){
                            rposy = 0.5*v*t1_1 + v*t2 + 0.5*v*(( (nowtime-t1_1-t2) + ( sin(OMG3*(nowtime-t1_1-t2) )) / OMG3));
                            rvely = v*0.5*(1 + cos(OMG3*(nowtime-t1_1-t2)));
                            raccy = -v*0.5*OMG3*sin(OMG3*(nowtime-t1_1-t2));


                        }

                    }
                }}


 //二つ目　ex1_posx <= rposx&& ex2_posx > rposx
            if (nowtime>=extime1 &&nowtime<extime2 ){
                OMG1 = PI / t2_1;OMG3 = PI/t2_1;
                v = (ex1_posy-ex2_posy)/(extime2-extime1-t2_1);
                t2 = extime2-extime1-2*t2_1;
                    if (nowtime<extime1+t2_1)
                {
                    rposy = ex1_posy-v*0.5*(nowtime-extime1-sin(OMG1*(nowtime-extime1))/OMG1);
                    rvely = -v*0.5*(1-cos(OMG1*(nowtime-extime1)));
                    raccy = -v*0.5*OMG1*sin(OMG1*(nowtime-extime1));


                }
                else{
                    if (nowtime<extime2-t2_1)
                    {
                        rposy = ex1_posy-(0.5*v*t2_1 + v*(nowtime-extime1-t2_1)) ;
                        rvely= -v;
                        raccy = 0;

                    }
                    else{
                        if (nowtime<extime2){
                            rposy = ex1_posy-(0.5*v*t2_1 + v*t2 + 0.5*v*( (nowtime-extime1-t2_1-t2) + ( sin(OMG3*( nowtime-extime1-t2_1-t2 )) )/ OMG3));
                            rvely = -v*0.5*(1 + cos(OMG3*(nowtime -extime1- t2_1-t2)));
                            raccy = v*0.5*OMG3*sin(OMG3*(nowtime-extime1-t2_1-t2));
                        }

                    }
                }}



 //三つ目 ex2_posx <rposx

            if (nowtime >= extime2 ){
                OMG1 = PI / t3_1;OMG3 = PI/t3_1;
                v = -ex2_posy/(T-extime2-t3_1);
                t2 = T-extime2-2*t3_1;
            if (nowtime<extime2+t3_1)
                {
                    rposy = ex2_posy+v*0.5*(nowtime-extime2-sin(OMG1*(nowtime-extime2))/OMG1);
                    rvely = v*0.5*(1-cos(OMG1*(nowtime-extime2)));
                    raccy = v*0.5*OMG1*sin(OMG1*(nowtime-extime2));

                }
                else{
                    if (nowtime<T-t3_1)
                    {
                        rposy = ex2_posy+0.5*v*t3_1 + v*(nowtime-extime2-t3_1) ;
                        rvely= v;
                        raccy = 0;

                    }
                    else{
                        if (nowtime<T){
                            rposy = ex2_posy+0.5*v*t3_1 + v*t2 + 0.5*v*( (nowtime-extime2-t3_1-t2) + ( sin(OMG3*( nowtime-extime2-t3_1-t2 )) )/ OMG3);
                            rvely = v*0.5*(1 + cos(OMG3*(nowtime-extime2- t3_1-t2)));
                            raccy = -v*0.5*OMG3*sin(OMG3*(nowtime-extime2- t3_1-t2));
                        }

                    }
                }}


nowtime+=SAMPLING_TIME;
 //一つ目 rposx < ex1_posx

            if (nowtime < extime1){
                OMG1 = PI / t1_1;OMG3 = PI/t1_1;
                v = ex1_posy/(extime1-t1_1);
                t2 = extime1-2*t1_1;
                    if (nowtime<t1_1)
                {
                    nextrposy = v*0.5*(nowtime-sin(OMG1*nowtime)/OMG1);
                    nextrvely = v*0.5*(1-cos(OMG1*nowtime));
                    nextraccy = v*0.5*OMG1*sin(OMG1*nowtime);

                }
                else{
                    if (nowtime<t1_1+t2)
                    {
                        nextrposy = 0.5*v*t1_1 + v*(nowtime-t1_1) ;
                        nextrvely= v;
                        nextraccy = 0;

                    }
                    else{
                        if (nowtime<extime1){
                            nextrposy = 0.5*v*t1_1 + v*t2 + 0.5*v*(( (nowtime-t1_1-t2) + ( sin(OMG3*( nowtime-t1_1-t2) )) / OMG3));
                            nextrvely = v*0.5*(1 + cos(OMG3*(nowtime-t1_1-t2)));
                            nextraccy = -v*0.5*OMG3*sin(OMG3*(nowtime-t1_1-t2));

                        }

                    }
                }}


 //二つ目　ex1_posx <= rposx&& ex2_posx > rposx
            if (nowtime>=extime1 &&nowtime<extime2 ){
                OMG1 = PI / t2_1;OMG3 = PI/t2_1;
                v = (ex1_posy-ex2_posy)/(extime2-extime1-t2_1);
                t2 = extime2-extime1-2*t2_1;
                    if (nowtime<extime1+t2_1)
                {
                    nextrposy = ex1_posy-v*0.5*(nowtime-extime1-sin(OMG1*(nowtime-extime1))/OMG1);
                    nextrvely = -v*0.5*(1-cos(OMG1*(nowtime-extime1)));
                    nextraccy = -v*0.5*OMG1*sin(OMG1*(nowtime-extime1));


                }
                else{
                    if (nowtime<extime2-t2_1)
                    {
                        nextrposy = ex1_posy-(0.5*v*t2_1 + v*(nowtime-extime1-t2_1)) ;
                        nextrvely= -v;
                        nextraccy = 0;

                    }
                    else{
                        if (nowtime<extime2){
                            nextrposy = ex1_posy-(0.5*v*t2_1 + v*t2 + 0.5*v*( (nowtime-extime1-t2_1-t2) + ( sin(OMG3*( nowtime-extime1-t2_1-t2 )) )/ OMG3));
                            nextrvely = -v*0.5*(1 + cos(OMG3*(nowtime -extime1- t2_1-t2)));
                            nextraccy = v*0.5*OMG3*sin(OMG3*(nowtime-extime1-t2_1-t2));
                        }

                    }
                }}



 //三つ目 ex2_posx <rposx

            if (nowtime >= extime2 ){
                OMG1 = PI / t3_1;OMG3 = PI/t3_1;
                v = -ex2_posy/(T-extime2-t3_1);
                t2 = T-extime2-2*t3_1;
            if (nowtime<extime2+t3_1)
                {
                    nextrposy = ex2_posy+v*0.5*(nowtime-extime2-sin(OMG1*(nowtime-extime2))/OMG1);
                    nextrvely = v*0.5*(1-cos(OMG1*(nowtime-extime2)));
                    nextraccy = v*0.5*OMG1*sin(OMG1*(nowtime-extime2));

                }
                else{
                    if (nowtime<T-t3_1)
                    {
                        nextrposy = ex2_posy+(0.5*v*t3_1 + v*(nowtime-extime2-t3_1)) ;
                        nextrvely= v;
                        nextraccy = 0;

                    }
                    else{
                        if (nowtime<T){
                            nextrposy = ex2_posy+0.5*v*t3_1 + v*t2 + 0.5*v*( (nowtime-extime2-t3_1-t2) + ( sin(OMG3*( nowtime-extime2-t3_1-t2 )) )/ OMG3);
                            nextrvely = v*0.5*(1 + cos(OMG3*(nowtime-extime2- t3_1-t2)));
                            nextraccy = -v*0.5*OMG3*sin(OMG3*(nowtime-extime2- t3_1-t2));
                        }

                    }
                }}

            if(nowtime < extime1){minrposx=0;maxrposx = ex1_posx;}
            else if(nowtime >= extime1&&nowtime <extime2){minrposx = ex1_posx;maxrposx =ex2_posx;}
            else if(nowtime >= extime2&&nowtime <=T){minrposx = ex1_posx;maxrposx = x1;}
nowtime-=SAMPLING_TIME;

nextrposx =  rposx ;
re_nextrposy = a3*nextrposx*nextrposx*nextrposx + a2*nextrposx*nextrposx + a1*nextrposx;

 //Ｘ座標算出 nowtime < extime1    or nowtime >=extime2
                if(nowtime <extime1||nowtime >=extime2){
                for (count = 6; count < 18; count++){
                    if (re_nextrposy < nextrposy){
                        while (re_nextrposy < nextrposy){
                            nextrposx += pow(0.1, count);
                            if(nextrposx >maxrposx){nextrposx -=pow(0.1,count);break;}
                            re_nextrposy = a3*nextrposx*nextrposx*nextrposx + a2*nextrposx*nextrposx + a1*nextrposx;
                        }

                    }
                    else if (re_nextrposy > nextrposy){
                        while (re_nextrposy > nextrposy){
                            nextrposx -= pow(0.1, count);
                            if(nextrposx <minrposx){nextrposx +=pow(0.1,count);break;}
                            re_nextrposy = a3*pow(nextrposx,3) + a2*pow(nextrposx,2) + a1*nextrposx;
                        }

                    }
                    else if (re_nextrposy == nextrposy){  break; }
                    else {  }

                }

                }

 //Ｘ座標算出 extime1<= nowtime < extime2
                if(nowtime >= extime1 &&nowtime < extime2){
                nextrposx = minrposx ;
                re_nextrposy = a3*nextrposx*nextrposx*nextrposx + a2*nextrposx*nextrposx + a1*nextrposx;
                for (count = 6; count < 18; count++){
                    if (re_nextrposy < nextrposy){
                        while (re_nextrposy < nextrposy){
                            nextrposx -= pow(0.1, count);
                            if(nextrposx <=minrposx){nextrposx +=pow(0.1,count);break;}
                            re_nextrposy = a3*nextrposx*nextrposx*nextrposx + a2*nextrposx*nextrposx + a1*nextrposx;
                        }

                    }
                    else if (re_nextrposy > nextrposy){
                        while (re_nextrposy > nextrposy){
                            nextrposx += pow(0.1, count);

                            if(nextrposx >=maxrposx){nextrposx -=pow(0.1,count);break;}
                            re_nextrposy = a3*pow(nextrposx,3) + a2*pow(nextrposx,2) + a1*nextrposx;
                        }

                    }
                    else if (re_nextrposy == nextrposy){  break; }
                    else {  }
                }
                //Debug::WriteLine("on");
                }

                //if(rvely == 0){rposx =  }
            D_y =  3 * a3*rposx*rposx+ 2 * a2*rposx + a1;
            D2_y = 6*a3*rposx+2*a2;
            dt_dx = ( nextrposx - rposx ) /SAMPLING_TIME;
            theta = atan(dt_dx);
            //rvelx = (*datalog)rvelx + (*datalog)raccx * SAMPLING_TIME;

            rvelx = rvely/D_y;
            if(D_y==0){rvelx = 0;}
            next_D_y = 3*a3*pow(nextrposx,2)+2*a2*nextrposx+a1;
            next_rvelx = nextrvely/next_D_y;
            if(next_D_y==0){next_rvelx = 0;}

            raccx = (next_rvelx-rvelx)/SAMPLING_TIME;
            //raccx = (nextrposx-rposx-rvelx*SAMPLING_TIME)*2/pow(SAMPLING_TIME,2);
            /*
            if( nowtime < T-t3_1&&nowtime > t1_1){
            if ( rvelx  <  0.004  ){rvelx = 0.004;raccx = 0;}
            }
            */
            if(rposx>nextrposx){}
            coordi.rpos(0) = rposx ;coordi.rvel(0) = rvelx;coordi.racc(0) = raccx;
            coordi.rpos(1) = rposy;coordi.rvel(1) = rvely;coordi.racc(1) = raccy;
            if(nextrvely !=0){
           // datalogrposx = nextrposx ;
            }


}

void control2d::eq_mat(double time,coordi2D &coordi)
{

        double seido = 1000;
        double &T = MP.My_T;
        double amari;


                double a1 = MP.My_a1;
                double a2 = MP.My_a2;
                double a3 = MP.My_a3;
                //double x0 = MP.My_x0;
                double x1 = MP.My_x1;
                double code_dt,grid;
                double code_count;
                double D_y,D2_y;
                double count;
                count = floor(time / T);
            double logrposx = coordi.rpos(0);
            double logrvelx = coordi.rvel(0);
            double lograccx = coordi.racc(0);


            if(fmod(count,2.0)==1){
                logrposx = x1-coordi.rpos(0);
                logrvelx = -coordi.rvel(0);
                lograccx = -coordi.racc(0);}

            double pretime = time - count*T;

            double theta,Dx3_y,Dx_theta,dt_x,dt2_x
                    ,dt_theta,d2x_theta,dt2_theta;



    code_dt = T/(seido);
    code_count = floor(pretime/code_dt);
    grid = code_dt/SAMPLING_TIME;
    amari = fmod(pretime,code_dt);


    if (fmod(pretime, SAMPLING_TIME) < 0.0005){
        coordi.racc(0) = code_accx[static_cast<unsigned int>((pretime / SAMPLING_TIME))];
    }
    else{ coordi.racc(0) = code_accx[static_cast<unsigned int>(((pretime+0.001) / SAMPLING_TIME))]; }

    coordi.rvel(0) = logrvelx+SAMPLING_TIME*lograccx;
    coordi.rpos(0) = logrposx + 0.5*(logrvelx+coordi.rvel(0))*SAMPLING_TIME;
    if(pretime == 0){coordi.rvel(0) = 0;coordi.rpos(0)=0;}

                    D_y = 3 * a3*coordi.rpos(0)*coordi.rpos(0) + 2 * a2*coordi.rpos(0) + a1;
                    D2_y = 6*a3*coordi.rpos(0)+2*a2;
                    Dx3_y = 6*MP.My_a3;

                    theta = atan(D_y);
                    Dx_theta = D2_y/(1+pow(D_y,2));
                    dt_x = coordi.rvel(0);
                    dt_theta = Dx_theta*coordi.rvel(0);

                    dt2_x = coordi.racc(0);
                    d2x_theta = Dx3_y*(-2)*D_y/pow(1+pow(D_y,2),2);
                    dt2_theta = d2x_theta*dt2_x;

                    global_theta = theta;
                    global_theta2 = dt_theta;
                    global_theta3 = dt2_theta;


                    coordi.rpos(1) = a3*coordi.rpos(0)*coordi.rpos(0)*coordi.rpos(0)
                            + a2*coordi.rpos(0)*coordi.rpos(0) + a1*coordi.rpos(0);
                    coordi.rvel(1) = D_y*coordi.rvel(0);
                    coordi.racc(1) = D_y*coordi.racc(0) + D2_y*coordi.rvel(0)*coordi.rvel(0);
/*
                    datalogrposx = coordi.rpos(0);
                    datalogrvelx = coordi.rvel(0);
                    datalograccx = coordi.racc(0);*/
                    if (fmod(count, 2.0) == 1){ coordi.rpos(0) = x1 - coordi.rpos(0);
                        coordi.rvel(0) = -coordi.rvel(0);
                        coordi.racc(0) = -coordi.racc(0);
                        global_theta = PI-theta;
                        global_theta2 = -dt_theta;
                        global_theta3 = -dt2_theta;}
                    double rposx_, rvelx_, raccx_;
                    rposx_ = coordi.rpos(0);
                    coordi.rpos(0) = coordi.rpos(0)*cos(axis_rotation)
                            + coordi.rpos(1)*sin(axis_rotation);
                    coordi.rpos(1) = -rposx_*sin(axis_rotation)
                            + coordi.rpos(1)*cos(axis_rotation);

                    rvelx_ =coordi.rvel(0);
                    coordi.rvel(0) = coordi.rvel(0)*cos(axis_rotation)
                            + coordi.rvel(1)*sin(axis_rotation);
                    coordi.rvel(1) = -rvelx_*sin(axis_rotation)
                            + coordi.rvel(1)*cos(axis_rotation);

                    raccx_ = coordi.racc(0);
                    coordi.racc(0) = coordi.racc(0)*cos(axis_rotation)
                            + coordi.racc(1)*sin(axis_rotation);
                    coordi.racc(1) = -raccx_*sin(axis_rotation) + coordi.racc(1)*cos(axis_rotation);


    //if (time > 2){ Debug::WriteLine(pretime); }

}

void control2d::eq_cxaxis(double time
                                        , coordi2D &coordi)
{


                    double r1,r2;
                    r1=0.075;r2=0.0175;

                    double T  = MP.My_T;
                    double L = MP.My_L;
                    double t1 = MP.My_T1;
                    double t2 = T - 2 * t1;
                    double t3 = MP.My_T3;

                    double a1 = MP.My_a1;
                    double a2 = MP.My_a2;
                    double a3 = MP.My_a3;
                    //double x0 = MP.My_x0;
                    double x1 = MP.My_x1;

                    double rposx_,rvelx_,raccx_;
                    double count;
                    count = floor(time/T);
                    double logrposx = coordi.rpos(0);
                    double logrvelx = coordi.rvel(0);
                    double lograccx = coordi.racc(0);

                    double theta,vel,Dx_y,Dx2_y,Dt_vel,Dx_theta,dt_x,dt_theta;

                    double OMG1 = PI / t1;
                    double OMG3 = PI / t3;
                    double v ;
                    double pretime = time - count*T;

                    if(fmod(time,T)==0){logrposx=0;logrvelx = 0;}


                    if (MP.My_v >0){v = MP.My_v;}
                    else{
                             v = L / (T - t1);
                            }

                    if (pretime<t1)
                    {
                        vel = v*0.5*(1 - cos(OMG1*pretime));
                        Dt_vel = v*0.5*OMG1*sin(OMG1*pretime);

                    }
                    else{
                        if (pretime<t1 + t2)
                        {
                            vel = v;
                            Dt_vel = 0;
                        }
                        else{
                            if (pretime<t1 + t2 + t3){
                                vel = v*0.5*(1 + cos(OMG3*(pretime - t1 - t2)));
                                Dt_vel = -v*0.5*OMG3*sin(OMG3*(pretime-t1-t2));
                            }

                        }
                    }


                    //if (time <=0){rpos(0)=0;rpos(1)=0;}//initialize
                    dt_x = (logrvelx + 0.5*SAMPLING_TIME*lograccx);///

                    coordi.rpos(0) = logrposx + dt_x*SAMPLING_TIME;

                    //if ( rpos(0)==logrposx){rpos(0)+=0.00001;}//停止防止

                    coordi.rpos(1) = a3*coordi.rpos(0)*coordi.rpos(0)*coordi.rpos(0)
                            + a2*coordi.rpos(0)*coordi.rpos(0) + a1*coordi.rpos(0);

                    Dx_y = 3 * a3*coordi.rpos(0)*coordi.rpos(0) + 2 * a2*coordi.rpos(0) + a1;//radian
                    Dx2_y = 6*a3*coordi.rpos(0)+2*a2;


                    theta = atan(Dx_y);
                    Dx_theta = Dx2_y/(1+pow(Dx_y,2));
                    dt_x = vel*cos(theta);
                    dt_theta = Dx_theta*dt_x;



                        coordi.rvel(0) = vel*cos(theta);

                    //rvel(0) =logrvelx + 0.5*SAMPLING_TIME*lograccx;

                        coordi.racc(0) = Dt_vel*cos(theta) - vel*dt_theta*sin(theta);
                    //theory
                        //racc(0) = vel*(cos(theta+dt_theta)-cos(theta))/0.002;not_theory
                        coordi.rvel(1) = tan(theta)*coordi.rvel(0);
                        coordi.racc(1) = tan(theta)*coordi.racc(0) + dt_theta/pow(cos(theta),2)*coordi.rvel(0);



                        if(fmod(count,2.0)==1){coordi.rpos(0) = x1-coordi.rpos(0);
                            coordi.rvel(0)=-coordi.rvel(0);coordi.racc(0)=-coordi.racc(0);}

                        rposx_ = coordi.rpos(0);
                        coordi.rpos(0) = coordi.rpos(0)*cos(axis_rotation)+coordi.rpos(1)*sin(axis_rotation);
                        coordi.rpos(1) = -rposx_*sin(axis_rotation)+coordi.rpos(1)*cos(axis_rotation);

                        rvelx_ = coordi.rvel(0);
                        coordi.rvel(0) = coordi.rvel(0)*cos(axis_rotation)
                                +coordi.rvel(1)*sin(axis_rotation);
                        coordi.rvel(1) = -rvelx_*sin(axis_rotation)
                                +coordi.rvel(1)*cos(axis_rotation);

                        raccx_ = coordi.racc(0);
                        coordi.racc(0) = coordi.racc(0)*cos(axis_rotation)
                                +coordi.racc(1)*sin(axis_rotation);
                        coordi.racc(1) = -raccx_*sin(axis_rotation)+coordi.racc(1)*cos(axis_rotation);
}



double  control2d::simpsonL(double re_x1){
    double L,deltax,a,x0,x1;
    const int n = 100000;	//精度

    x0 = MP.My_x0;
    x1 = re_x1;


    //if (x0 = 0){ x0 = x0 + 0.0000001; }
    deltax = (x1 - x0 )/ n;
    a = control2d::f(x0);
    a += control2d::f(x0 + deltax * n);
    int counter;

    for (counter = 1; counter<n; counter += 2){
        a += 4.0 * fabs(control2d::f(x0 + deltax * counter));
    }
    for (counter = 2; counter<n; counter += 2){
        a += 2.0 * fabs(control2d::f(x0 + deltax * counter));
    }
    L = a*deltax / 3.0;
    return L;
}

double control2d::f(double x){
    double dl;		//dx区間における曲線距離
    dl = sqrt(1 + (3 * MP.My_a3*x*x + 2 * MP.My_a2*x + MP.My_a1)
              *(3 * MP.My_a3*x*x + 2 * MP.My_a2*x + MP.My_a1));
    return dl;
    //return MP.My_a3*x^3+ MP.My_a2*x^2 + MP.My_a1*x^3;
}
void control2dExp::test(){

}
void control2d::load_mat(){
    double  para;
    unsigned int i;
    code_accx.resize(2000);

    // reading config data
    std::string path;
    path =QCoreApplication::applicationDirPath().toStdString();

    std::ifstream ifs(path+"/code.csv");
    i = 0;
    ifs >> para;//一段目切り捨て
    code_accx[i] =1;
    for(i = 0;i < 1000;i++){
    ifs >> para ;
    code_accx[i] = para;
}
}
 control2dSim::control2dSim(unsigned int max_step, bstmatrix *datalogptr):control2d(){
    datalog = datalogptr;

    force.resize(2);
    u1.resize(2);
    posall.resize(NUM_ACTUATOR);
    velall.resize(NUM_ACTUATOR);
    accall.resize(NUM_ACTUATOR);
    posall_raw.resize(NUM_ACTUATOR);
    velall_raw.resize(NUM_ACTUATOR);
    accall_raw.resize(NUM_ACTUATOR);
    forceall.resize(NUM_ACTUATOR);
    ew_log.resize(NUM_ACTUATOR);
    pos_log.resize(NUM_ACTUATOR);
    vel_log.resize(NUM_ACTUATOR);
    acc_log.resize(NUM_ACTUATOR);
    rpos_log.resize(NUM_ACTUATOR);
    rvel_log.resize(NUM_ACTUATOR);
    racc_log.resize(NUM_ACTUATOR);
    rpos_c.resize(2);
    rvel_c.resize(2);
    racc_c.resize(2);
}
 control2dExp::control2dExp(unsigned int max_step, bool *stopptr):control2d(){

    IOcda.stopptr = stopptr;

    force.resize(2);
    u1.resize(2);
    Force.resize(2);
    posall.resize(define::NUM_ACTUATOR);
    velall.resize(define::NUM_ACTUATOR);
    accall.resize(define::NUM_ACTUATOR);
    forceall.resize(define::NUM_ACTUATOR);
    pos_log.resize(NUM_ACTUATOR);
    vel_log.resize(NUM_ACTUATOR);
    acc_log.resize(NUM_ACTUATOR);
    ew_log.resize(NUM_ACTUATOR);
    rpos_log.resize(NUM_ACTUATOR);
    rvel_log.resize(NUM_ACTUATOR);
    racc_log.resize(NUM_ACTUATOR);
    rpos_c.resize(2);
    rvel_c.resize(2);
    racc_c.resize(2);


 }



void control2d::MRACon(int step,bstvector &force
                               , bstvector &m_acc
                               , bstvector &ReqAcc){

    if(step > 20){

        AP.toro(0)=(*datalog)(16,step-1);//force
        AP.toro(1)=(*datalog)(16,step-2);
        AP.toro(2)=(*datalog)(16,step-3);
        AP.toro(3)=(*datalog)(16,step-4);
        AP.toro(4)=(*datalog)(16,step-5);

        AP.toro(5)=(*datalog)(15,step-1);//acc_log
        AP.toro(6)=(*datalog)(15,step-2);
        AP.toro(7)=(*datalog)(15,step-3);
        AP.toro(8)=(*datalog)(15,step-4);

        AP.toro2(0)=(*datalog)(24,step-1);
        AP.toro2(1)=(*datalog)(24,step-2);
        AP.toro2(2)=(*datalog)(24,step-3);
        AP.toro2(3)=(*datalog)(24,step-4);
        AP.toro2(4)=(*datalog)(24,step-5);

        AP.toro2(5)=(*datalog)(23,step-1);
        AP.toro2(6)=(*datalog)(23,step-2);
        AP.toro2(7)=(*datalog)(23,step-3);
        AP.toro2(8)=(*datalog)(23,step-4);
        //AP.toro2(9)=(*datalog)(23,step-5);

        bstvector alpha_n,alpha2_n;

        alpha_n = AP.alpha;
        alpha2_n = AP.alpha2;


        AP.alpha =AP.alpha - 0.1*AP.toro/(1+0.1*inner_prod(AP.toro,AP.toro))
                *(inner_prod(AP.alpha,AP.toro)-(*datalog)(15,step));
        AP.alpha2 =AP.alpha2 - 0.1*AP.toro2/(1+0.1*inner_prod(AP.toro2,AP.toro2))
                *(inner_prod(AP.alpha2,AP.toro2)-(*datalog)(23,step));



        /*
        AP.alpha =AP.alpha - 1*AP.toro/(1+1*inner_prod(AP.toro,AP.toro))
                *(inner_prod(AP.alpha,AP.toro)-m_acc(0));
        AP.alpha2 =AP.alpha2 - 1*AP.toro2/(1+1*inner_prod(AP.toro2,AP.toro2))
                *(inner_prod(AP.alpha2,AP.toro2)-m_acc(1));
        */


        if(AP.alpha(0)<= 0.3)AP.alpha(0)=0.3;
        if(AP.alpha2(0)< 0.4)AP.alpha2(0)=0.4;

        force(0)=(ReqAcc(0)-inner_prod(subrange(AP.alpha,1,9),subrange(AP.toro,1,9)))
                    /AP.alpha(0);
        force(1)=(ReqAcc(1)-inner_prod(subrange(AP.alpha2,1,9),subrange(AP.toro2,1,9)))
                  /AP.alpha2(0);
    }
    else {
        //force = prod(mass,ReqAcc) + prod(c,vel);
        force = prod(CP.mass,ReqAcc);
    }
}

void control2d::MRACon2(int step,bstvector &force
                               , bstvector &current_pos
                               , bstvector &next_pos){
//terao method
    //d=1 n = 5 m=4
    if(step > 20){

        //k-1
        AP.xi1(0)=(*datalog)(16,step-1);//force
        AP.xi1(1)=(*datalog)(16,step-2);
        AP.xi1(2)=(*datalog)(16,step-3);
        AP.xi1(3)=(*datalog)(16,step-4);


        AP.xi1(4)=(*datalog)(13,step-1);//pos






        AP.xi2(0)=(*datalog)(24,step-1);//force
        AP.xi2(1)=(*datalog)(24,step-2);
        AP.xi2(2)=(*datalog)(21,step-1);//pos
        AP.xi2(3)=(*datalog)(21,step-2);

        double vare,vare2;
        double gain = 5;


        vare = (    -(current_pos(0)+AP.xi1(4))
                                            +inner_prod(AP.theta,AP.xi1)         )
                        /(1+inner_prod(trans(prod(trans(AP.xi1),AP.AdaGain)),trans(AP.xi1)));

        vare2 = (-(current_pos(1)+AP.xi2(2))+inner_prod(AP.theta2,AP.xi2))
                        /(1+gain*inner_prod(AP.xi2,AP.xi2));



        AP.theta=AP.theta-vare*prod(AP.AdaGain,AP.xi1);
        AP.theta2=AP.theta2-gain*vare2*AP.xi2;




        matrix<double> x1,x2;
        double ramda = 1;
        x1 = outer_prod(AP.xi1,AP.xi1);
        x2 = prod(AP.AdaGain,x1);
/*
        AP.AdaGain = (AP.AdaGain
                    -(prod(x2,AP.AdaGain))
                        /(ramda+inner_prod(trans(prod(trans(AP.xi),AP.AdaGain)),AP.xi)))/ramda;*/


        AP.xi1(1)=(*datalog)(16,step-1);//force
        AP.xi1(2)=(*datalog)(16,step-2);
        AP.xi1(3)=(*datalog)(16,step-3);

        AP.xi1(4)=current_pos(0);




        if(AP.theta(0)<0.001)AP.theta(0)=0.001;

        force(0)= (next_pos(0)+AP.xi1(4)
                   -inner_prod(subrange(AP.theta,1,5),subrange(AP.xi1,1,5)))
                                                            /AP.theta(0);
        force(1)= (current_pos(1)+next_pos(1)-inner_prod(AP.theta2,AP.xi2))/AP.theta2(0);


        (*datalog)(2,step) =vare;

    }
    else {
        //force = prod(mass,ReqAcc) + prod(c,vel);
        //force = prod(CP.mass,ReqAcc);
    }
}

void control2d::MRACon3(int step,bstvector &force
                        , bstvector &current_pos
                        , bstvector &next_pos){
//n=1 m=0 d=1 v = 0 F=1
double k1 =-1.98; //-1.8;
double k2 = 0.81;//0.81;
double beta = -0.7;
k1 = beta;
k2 = pow(beta,2);


    if(step > 20){
double Dy = current_pos(0)+k1*(*datalog)(13,step-1)+k2*(*datalog)(13,step-2);
        //k
        AP.toro(0)=(*datalog)(16,step-1)+k1*(*datalog)(16,step-2)+k2*(*datalog)(16,step-3);//force
        //AP.toro(1)=(*datalog)(16,step-2);
        AP.toro(1)=(*datalog)(13,step-1)+k1*(*datalog)(13,step-2)+k2*(*datalog)(13,step-3);//pos
        //AP.toro(3)=(*datalog)(13,step-2);

        double gain=5;
        double vare;
        vare = (inner_prod(column(AP.estimated_val,step-1),AP.toro)-Dy)
                                            /(1+gain*inner_prod(AP.toro,AP.toro));

(*datalog)(8,step) =vare;

if((AP.estimated_val(0,step-1)-gain*AP.toro(0)*vare)<0)column(AP.estimated_val,step) = column(AP.estimated_val,step-1);
else column(AP.estimated_val,step) =column(AP.estimated_val,step-1) - gain*AP.toro *vare;

//std::cout<<(inner_prod(column(AP.estimated_val,step-1),AP.toro)/Dy)<<std::endl;
//std::cout<<matcol(AP.estimated_val,step)<<std::endl;

        ////if(AP.estimated_val(0,step)<0.003)AP.estimated_val(0,step)=0.003;

        AP.toro(0)=0;//force
        //AP.toro(1)=(*datalog)(16,step-1);
        AP.toro(1)=current_pos(0);//pos
        //AP.toro(3)=(*datalog)(13,step-1);

        force(0)=(MP.preprofile(0,step+1)+k1*MP.preprofile(0,step)+k2*MP.preprofile(0,step-1)//+k1*current_pos(0)+k2*MP.preprofile(0,step-1)
                  -inner_prod(subrange(matcol(AP.estimated_val,step),1,2),subrange(AP.toro,1,2)))
                    /AP.estimated_val(0,step);
        force(1) = (-inner_prod(subrange(matcol(AP.estimated_val,step),1,2),subrange(AP.toro,1,2)))
                    /AP.estimated_val(0,step);

        /*
        force(1)=(next_pos(1)-inner_prod(subrange(AP.alpha2,1,9),subrange(AP.toro2,1,9)))
                  /AP.alpha2(0);*/
    }

}

void control2d::MRACon4(int step,bstvector &force
                        , bstvector &current_pos){

    double L0 = 1;
    double L1 = 1;

//xi1 k-d
    for(int i = 0;i<nq+1;i++)   AP.xi1(i)       = L0*MP.preprofile(0,step-d-i)
                                                    + L1*MP.preprofile(0,step-d-1-i);//ref

//xi2 k-d
    for(int i = 0;i<np+1;i++)   AP.xi2(i)       = L0*(*datalog)(16,step-d-i)
                                                    + L1*(*datalog)(16,step-d-1-i);//force

    for(int i = 0;i<ns+1;i++)   AP.xi2(i+np+1)  = L0*(*datalog)(13,step-d-i)
                                                    + L1*(*datalog)(13,step-d-1-i);//pos



    //this->LSmethod(AP.Gain1,AP.Gain2);
    this->Trmethod(AP.Gain1,AP.Gain2);
    double r_c,y_c;
    this->AdapY1(r_c,y_c,step,current_pos);

        double vare1,vare2;//extended error
        bstvector test;

        vare1 = (r_c-inner_prod(AP.theta_1,AP.xi1))/(1+inner_prod(prod(AP.Gain1,AP.xi1),AP.xi1));
        vare2 = (y_c-inner_prod(AP.theta_2,AP.xi2))/(1+inner_prod(prod(AP.Gain2,AP.xi2),AP.xi2));


        AP.theta_1 = AP.theta_1+prod(AP.Gain1,AP.xi1)*vare1;//gyaku
        test = AP.theta_2+prod(AP.Gain2,AP.xi2)*vare2;
  // if(step<200000){
        if(test(0)>0)
        //if(pow(0.1,6)<abs(vare2))//不感帯
        AP.theta_2 = AP.theta_2+prod(AP.Gain2,AP.xi2)*vare2;//gyaku

/////////////test code   ///////////////////////////////////

        (*datalog2)(0,step)=AP.theta_2(0);
        (*datalog2)(1,step)=AP.theta_2(1);
        (*datalog2)(2,step)=y_c/inner_prod(AP.theta_2,AP.xi2);

//std::cout<<vare2<<std::endl;
/////////////test code   ///////////////////////////////////

            //xi1 k-d
                for(int i = 0;i<nq+1;i++){
                    AP.xi1(i) = MP.preprofile(0,step-i);//ref
                }
            //xi2 k-d
                for(int i = 0;i<np+1;i++){
                    AP.xi2(i)       = (*datalog)(16,step-i) ;//force
                }
                AP.xi2(np+1) = current_pos(0);
                for(int i = 1;i<ns+1;i++){
                    AP.xi2(i+np+1)  =  (*datalog)(13,step-i);//pos
                }

            force(0) = (inner_prod(AP.xi1,AP.theta_1)
                            -inner_prod(subrange(AP.xi2,1,ns+np+2)
                                        ,subrange(AP.theta_2,1,ns+np+2)))/AP.theta_2(0);




/*
    //xi1 k-d
        for(int i = 0;i<nq+1;i++){
            AP.xi1(i) = L0*MP.preprofile(0,step-i)+L0*MP.preprofile(0,step-1-i);//ref
        }
    //xi2 k-d
        for(int i = 0;i<np+1;i++){
            AP.xi2(i)       = L0*(*datalog)(16,step-i) + L0*(*datalog)(16,step-1-i);//force
        }
            AP.xi2(np+1) = L0*current_pos(0)+ L0*(*datalog)(13,step-1);
        for(int i = 1;i<ns+1;i++){
            AP.xi2(i+np+1)  = L0*(*datalog)(13,step-i) + L0*(*datalog)(13,step-1-i);//pos
        }

        force(0) = (inner_prod(AP.xi1,AP.theta_1)
                        -inner_prod(subrange(AP.xi2,1,ns+np+2)
                                    ,subrange(AP.theta_2,1,ns+np+2)))/AP.theta_2(0)/L0-(*datalog)(16,step-1);
*/
        //std::cout<<AP.theta_2<<std::endl;
            //std::cout<<MP.preprofile(0,step)<<std::endl;
}
void control2dExp::ControlAll(unsigned int step)
{
    using namespace boost::numeric::ublas;

    unsigned int i,j;


    time = step * define::SAMPLING_TIME;

    rpos_c = coordi.rpos;
    rvel_c = coordi.rvel;
    racc_c = coordi.racc;

    IOcda.GetStateVariable(time,posall,velall,accall);

    posall_raw = posall;
    velall_raw = velall;
    accall_raw = accall;

    if(step>6)SGfil.calcA(step-5,datalog,posall,velall,accall);
    else     diff_rear(step,posall,velall,accall);


    coordi.pos = subrange(posall,0,2);
    coordi.vel = subrange(velall,0,2);
    coordi.acc = subrange(accall,0,2);

    subrange(coordi.ew,0,2) = coordi.pos - coordi.rpos;
    subrange(coordi.ew,2,4) = coordi.vel - coordi.rvel;
    subrange(coordi.ew,4,6) = coordi.acc - coordi.racc;

    es = posall(2) -coordi.pos(1);
    es1 = velall(2) - coordi.vel(1);
    es2 = accall(2) - coordi.acc(1);

    if(step<max_step-1){
            coordi.rpos = subrange(column(MP.preprofile,step+1),0,2);
            coordi.rvel = subrange(column(MP.preprofile,step+1),2,4);
            coordi.racc = subrange(column(MP.preprofile,step+1),4,6);
    }

    switch(control_type){
    case INDEPENDENT:
    case 3:
        ICon(coordi,u1);
    break;

    case CONTOURING:
    case 4:
        ContouringController(coordi,u1,time);
    break;

    case MOD_CONTOURING:
    case 5:
        MCCon(coordi,u1,time);
        if(time == 0)u1(0)=0;u1(1)=0;
    break;
    case 6:
        //gomi //MRACon2(step,force,coordi.pos,coordi.rpos);
        //if(step>0&&step<max_step-2)MRACon3(step,force,coordi.pos,coordi.rpos);

        //if(step>15&&step<max_step-2)MRACon4(step,force,coordi.pos);
        if(step>15&&step<max_step-2)AdapCon.MRACS_LZ(step,force,coordi.pos);
    break;
    }

/*
    if (CP.AdapFlag){
        u1 += coordi.racc;
        MRACon(step,Force,coordi.acc,u1);
    }
    else Force = prod(CP.mass,u1+racc_c)+prod(CP.c,coordi.vel);
*/
if(!SW1){
if(step>15000&&abs(coordi.ew(0))<pow(0.1,7))SW1=true;
else SW1 = false;
}

    if(!SW1){
        ICon(coordi,u1);
        force = prod(CP.mass,u1+racc_c)+prod(CP.c,coordi.vel);}//rinzi



    subrange(forceall,0,2)=force;

    forceall(2) = force(1)+masss*( -kvs*es1-kps*es ) + cs*es1; //sync

    IOcda.OutputControlVariable(forceall);

    if(enable_datalog){

        subrange(rpos_log,0,2)=rpos_c;
        subrange(rvel_log,0,2)=rvel_c;
        subrange(racc_log,0,2)=racc_c;
        subrange(pos_log,0,2)=coordi.pos;
        subrange(racc_log,0,2)=racc_c;
        subrange(vel_log,0,2)=coordi.vel;
        subrange(acc_log,0,2)=coordi.acc;
        subrange(ew_log,0,2)=coordi.pos-rpos_c;

        rpos_log(2) = coordi.rpos(1);
        rvel_log(2) = coordi.rvel(1);
        racc_log(2) = coordi.racc(1);
        pos_log(2) = posall_raw(2);
        vel_log(2) = velall_raw(2);
        acc_log(2) = accall_raw(2);
        ew_log(2) = posall_raw(2) - rpos_c(1);


        (*datalog)(0,step) = time;
        (*datalog)(1,step) = 0;
        //(*datalog)(2,step) = latency;	//ec-en
        (*datalog)(3,step) = CP.mass(1,1);	//ec-enmod
        (*datalog)(4,step) = AP.alpha(0);	//td
        (*datalog)(5,step) = AP.alpha(1);	//el t
        (*datalog)(6,step) = AP.alpha(2);	//el n
        (*datalog)(7,step) = AP.alpha(3);	//el b
        (*datalog)(8,step) = AP.alpha(4);	//es y
        (*datalog)(9,step) = AP.alpha(5);	//es a
        for(i=0,j=0;i<NUM_ACTUATOR;i++,j+=8){
            (*datalog)(j+10,step) = rpos_log(i);
            (*datalog)(j+11,step) = rvel_log(i);
            (*datalog)(j+12,step) = racc_log(i);
            (*datalog)(j+13,step) = pos_log(i);
            (*datalog)(j+14,step) = vel_log(i);
            (*datalog)(j+15,step) = acc_log(i);
            (*datalog)(j+16,step) = forceall(i);
            (*datalog)(j+17,step) = ew_log(i);
        }
    }
}
coordi2D::coordi2D(){
    rpos.resize(2);
    rvel.resize(2);
    racc.resize(2);
    ew.resize(2);
    ew1.resize(2);
    ew2.resize(2);
    vel.resize(2);
}

void control2d::diff_rear(unsigned int step
                          , vector<double>& pos
                          , vector<double>& vel
                          , vector<double>& acc){

    for(unsigned int i=0;i<NUM_COUNTER;i++)
    {
        if(step > 1){

            vel(i) = (pos(i) - (*datalog)(8*i+13,step-1)) / SAMPLING_TIME;
            acc(i) = (vel(i) - (*datalog)(8*i+14,step-1)) / SAMPLING_TIME;

        }

        else if(step == 0){

            vel(i) = 0;
            acc(i) = 0;

        }

        else if(step == 1){

            acc(i) = 0;

        }

    }

}

void control2d::Ready(){

    unsigned int step,i,j;
    double time;
    MP.preprofile.resize(6,max_step); //x y1
    for(step = 0;step < max_step;step++){

        time = step * SAMPLING_TIME;
        GenRef(time,coordi);

        for(i=0;i<2;i++){
            MP.preprofile(0+i,step) = coordi.rpos(i);
            MP.preprofile(2+i,step) = coordi.rvel(i);
            MP.preprofile(4+i,step) = coordi.racc(i);
        }

    }

}
void control2d::LSmethod(bstmatrix &Gain1, bstmatrix &Gain2){
    bstmatrix x;
    double traceR;
    double ramda = 0.85;
    traceR = numeric::ublas::trace(Gain2);
    x = prod(Gain1,outer_prod(AP.xi1,AP.xi1));
    Gain1 = (Gain1 - (prod(x,Gain1))
                            /(ramda+inner_prod(prod(Gain1,AP.xi1),AP.xi1)))/ramda;
    std::cout<<traceR<<std::endl;
    x = prod(Gain2,outer_prod(AP.xi2,AP.xi2));
    Gain2 = (Gain2 - (prod(x,Gain2))
                            /(ramda+inner_prod(prod(Gain2,AP.xi2),AP.xi2)))/ramda;

}
void control2d::Trmethod(bstmatrix &Gain1, bstmatrix &Gain2){
    bstmatrix x;
    double traceR;
    double ramda = 0.85;
    double sigma1=1,sigma2=1;
    double ramda1_1,ramda2_1;
    traceR = numeric::ublas::trace(Gain1);
    ramda1_1 = 1-numeric::ublas::norm_2_sq(prod(Gain1,AP.xi1))
                /((sigma1+inner_prod(prod(Gain1,AP.xi1),AP.xi1))*traceR);
    traceR = numeric::ublas::trace(Gain2);
    ramda2_1 = 1-numeric::ublas::norm_2_sq(prod(Gain2,AP.xi2))
                /((sigma2+inner_prod(prod(Gain2,AP.xi2),AP.xi2))*traceR);



    x = prod(Gain1,outer_prod(AP.xi1,AP.xi1));
    Gain1 = (Gain1 - (prod(x,Gain1))
                            /(sigma1+inner_prod(prod(Gain1,AP.xi1),AP.xi1)))/ramda1_1;

    x = prod(Gain2,outer_prod(AP.xi2,AP.xi2));
    Gain2 = (Gain2 - (prod(x,Gain2))
                            /(sigma2+inner_prod(prod(Gain2,AP.xi2),AP.xi2)))/ramda2_1;

}
void control2d::AdapY1(double &r_c,double &y_c,int &step,bstvector &current_pos){
    //C(z^-1)r(k)-----> r_c
    //C(z^-1)y(k)-----> y_c
    double pole1,pole2,pole3;

if(nc==0){
r_c = MP.preprofile(0,step);
y_c =  current_pos(0);
}
else if(nc==3){
    double c1,c2,c3;
     pole1 = -0.70;
     pole2 = -0.70;
     pole3 = -0.70;

     c1 = (pole1+pole2+pole3);
     c2 = pole1*pole2+pole2*pole3+pole3*pole1;
     c3 = pole1*pole2*pole3;
     r_c = MP.preprofile(0,step)+c1*MP.preprofile(0,step-1)
                  +c2*MP.preprofile(0,step-2)+c3*MP.preprofile(0,step-3);
      y_c =  current_pos(0)+c1*(*datalog)(13,step-1)
              +c2*(*datalog)(13,step-2)+c3*(*datalog)(13,step-3);
}

else if(nc ==4){
    //重解
double beta = -0.5;//mainasu
    bstvector C;
    C.resize(nc+1);
    C(0) = pow(beta,4);
    C(1) = 4.0*pow(beta,3);
    C(2) = 6.0*pow(beta,2);
    C(3) = 4.0*beta;
    C(4) = 1;
    r_c = 0;
    y_c = 0;
    for(int i =0;i<nc+1;i++){
        r_c += C(i)*MP.preprofile(0,step-nc+i);
        if(i<nc)y_c += C(i)*(*datalog)(13,step-nc+i);//pos
    }
    y_c += C(nc)*current_pos(0);

}
}
