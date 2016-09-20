#ifndef CONTROL2D_H
#define CONTROL2D_H

#include <vector>
#include "define.h"
#include "IO/io.h"
#include "SGfilter.h"
#include "plant.h"
#include "AdaptiveControl.h"
typedef boost::numeric::ublas::vector<double> bstvector;
typedef boost::numeric::ublas::matrix<double> bstmatrix;


class coordi2D{

    public:
        coordi2D();
        vector<double>  rpos,rvel,racc,ew,ew1,ew2,pos,vel,acc;

};

class MotionPara{

    public:
        double  My_L
                ,My_T,My_T1,My_T3
                ,My_a1,My_a2,My_a3
                ,My_x0,My_x1,My_v;
        bstmatrix preprofile;

};

class AdapPara{

    public:
        bstvector alpha,toro,ReqAcc,alpha2,toro2,ReqAcc2;
        bstvector theta,theta2; // bstvector theta,xi,theta2,xi2;
        bstmatrix AdaGain;

        bstmatrix estimated_val;
        bstvector Outpara1;

        //uchiyama sensei kara-
        bstvector xi1,xi2,theta_1,theta_2;
        bstvector input,output,ref;
        bstmatrix Gain1,Gain2;
};

class ControllerPara{

    public:
        bstmatrix K,mass,invmass,c,kpw,kvw,kpl,kvl;
        bool AdapFlag;

};

class con2dvariable{

    public:
        int stepcount;
        unsigned int max_step;
        double latency;
        unsigned int control_type;
        boost::numeric::ublas::matrix<double> *datalog;
        boost::numeric::ublas::matrix<double> *datalog2;

        SGfilter SGfil;

        int    d //muda
                        ,n //A(z^-1) dim
                        ,nb //B(z^-1) dim
                        ,nf//F(z^-1)r(k) = 0
                        ,nd//ramp dist
                        ,m //zero point
                        ,nc//C(z^-1)e(k)---->0
                        ,nq//max (nf-1,nc-m-d)
                        ,np//max()
                        ,ns
                        ,nr;

    protected:
        con2dvariable();
        iocda           IOcda;
        MotionPara      MP;
        AdapPara        AP;
        ControllerPara  CP;
        coordi2D coordi;
        AdaptiveControl AdapCon;
        plant           plant1;
        static const unsigned int INDEPENDENT		= 0;
        static const unsigned int CONTOURING		= 1;
        static const unsigned int MOD_CONTOURING	= 2;

        double masss,cs,kvs,kps;
        double global_theta,global_theta2,global_theta3;
        int	 trajectory_num;
        double tool_radius;
        double axis_rotation=0;//[rad]
        bool enable_datalog;
        std::vector<double> code_accx;


};

class control2d:public con2dvariable{
public :
    void SetConParam(std::vector<double> *conparam
                     ,std::vector<double> *conparam2);
    void load_mat();
protected:
    control2d();
    bool SW1;
    double simpsonL(double x1);
    double f(double x);
    void GenRef(double time,coordi2D &coordi);

    void CalcRotationMat(double time
                         ,bstmatrix& Rot
                         ,bstmatrix& Rot1
                         ,bstmatrix& Rot2);

    double CalcContouringError(bstvector &pos
                               ,bool Reverse);
    bool IsReachPoint(double time,double max_angle);
    void cubic_equation_solve(double p,double q,double r);

    void eq_tool(double time,coordi2D &coordi);
    void eq_xaxis(double time,coordi2D &coordi);
    void eq_yaxis(double time,coordi2D &coordi);
    void eq_mat(double time,coordi2D &coordi);
    void eq_cxaxis(double time,coordi2D &coordi);

    void diff_rear(unsigned int step, vector<double> &pos
                   , vector<double> &vel
                   , vector<double> &acc);

    void MRACon(int step, bstvector &force
                        , bstvector &m_acc
                        , bstvector &ReqAcc);
    void MRACon2(int step, bstvector &force
                        , bstvector &m_acc
                        , bstvector &next_pos);
    void MRACon3(int step, bstvector &force
                        , bstvector &current_pos
                        , bstvector &next_pos);
    void MRACon4(int step, bstvector &force
                        , bstvector &current_pos
                        );

    void ICon(coordi2D &coordi,vector<double> &u1);
    void ContouringController(coordi2D &coordi
                        , vector<double> &ReqAcc
                        , double time);
    void MCCon(coordi2D& coordinate
                                 ,vector<double> &ReqAcc
                                 ,double time);
    void SynthForce(bstvector &force
                    , bstvector &FfAcc
                    , bstvector &FbAcc);

    void Ready();

    void LSmethod(bstmatrix &Gain1, bstmatrix &Gain2);
    void Trmethod(bstmatrix &Gain1, bstmatrix &Gain2);
    void AdapY1(double &r_c, double &y_c, int &step, bstvector &current_pos);
};

class control2dSim : public control2d{

    public:
        void ControlSim2D(unsigned int control_type_,
                            unsigned int max_step,
                            bool enable_noise,
                            bool enable_resolution
                            );
         control2dSim(unsigned int max_step
                      ,bstmatrix *datalogptr);

private:

        void ControlAll(unsigned int max_step
                              , bool enable_noise
                              , bool enable_resolution
                              , int controlType);
       bstvector force,u1,
                        posall,velall,accall
                        ,posall_raw,velall_raw,accall_raw
                        ,forceall,
                        ew_log,
                        pos_log,vel_log,acc_log,
                        rpos_log,rvel_log,racc_log,
                        rpos_c,rvel_c,racc_c;//current state
        double			es,es1,es2,
                        forces,time;

};


class control2dExp: public control2d{

    public:
        void test();
        void ControlAll(unsigned int step);
        control2dExp(unsigned int max_step,bool *stopptr);
    private:
        vector<double> force,u1,Force
                        ,posall_raw,velall_raw,accall_raw
                        ,posall,velall,accall,
                        forceall,
                        ew_log,
                        pos_log,vel_log,acc_log,
                        rpos_log,rvel_log,racc_log,
                        rpos_c,rvel_c,racc_c;//current state
        double			es,es1,es2,
                        poss,vels,accs,
                        forces,time;
};

#endif
