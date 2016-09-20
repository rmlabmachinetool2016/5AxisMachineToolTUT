#ifndef CONTROL3D_H
#define CONTROL3D_H
#undef BOOST_UBLAS_TYPE_CHECK
#define BOOST_UBLAS_TYPE_CHECK 0
//#define REF_WORLD
#include "stdafx.h"
#include "boost/numeric/ublas/matrix.hpp"
#include "IO/io.h"
class control3d{
    public:
     const unsigned int INDEPENDENT		= 0;
     const unsigned int CONTOURING		= 1;
     const unsigned int MOD_CONTOURING	= 2;
		
         double			pole_x,pole_y1,pole_y2,pole_z,pole_c,pole_a1,pole_a2;
         double			pole_t,pole_n,pole_b,pole_i,pole_j,pole_k;
         double			pole_sync_y,pole_sync_a;
         double			mass_x,mass_y1,mass_y2,mass_z,mass_c,mass_a1,mass_a2;
         double			c_x,c_y1,c_y2,c_z,c_c,c_a1,c_a2;
         unsigned int         stepcount,max_step;
         boost::numeric::ublas::matrix<double>	mass,invmass,c,kpw,kvw,kpl,kvl;
         boost::numeric::ublas::matrix<double>	masss,cs,kvs,kps;
         boost::numeric::ublas::matrix<double>	kvo,kpo,Mo,Co;

        boost::numeric::ublas::vector<double>	force,forceall,
								ew_log,el_log,
								pw_log,pwdot_log,pw2dot_log,
								pl_log,pldot_log,pl2dot_log,
								prw_log,prwdot_log,prw2dot_log,
								prl_log,prldot_log,prl2dot_log,
								force_log;
         boost::numeric::ublas::vector<double>	posall,velall,accall;
         boost::numeric::ublas::vector<double>	pl,pldot,pl2dot,pw,pwdot,pw2dot;
         boost::numeric::ublas::vector<double>	prl,prldot,prl2dot,prw,prwdot,prw2dot;
         boost::numeric::ublas::vector<double>	ew,ewdot,ew2dot;
         boost::numeric::ublas::vector<double>	es,esdot,forces,
								poss,vels,accs,
								rposs,rvels,raccs;
         boost::numeric::ublas::vector<double>	eF,eFa;
         double			td;

    void ControlSim3D(	int control_type,
						unsigned int max_step,
						bool enable_noise,
                        bool enable_resolution);
    std::vector<std::vector<double>> *datalog;
    iocda IOcda;
    void SetConParam(std::vector<double> *conparam);
    control3d(unsigned int max_step,std::vector<std::vector<double>> *datalogptr);
    void GenTWorld(double time
                   ,boost::numeric::ublas::vector<double>& wref
                   ,boost::numeric::ublas::vector<double>& wref1
                   ,boost::numeric::ublas::vector<double>& wref2);
    void GenTLocal(double time
                   ,boost::numeric::ublas::vector<double>& lref
                   ,boost::numeric::ublas::vector<double>& lref1
                   ,boost::numeric::ublas::vector<double>& lref2);
    void GenTWorld34(double time
                     ,boost::numeric::ublas::vector<double>& wref3
                     ,boost::numeric::ublas::vector<double>& wref4);
    void GenTLocal34(double time
                     ,boost::numeric::ublas::vector<double>& lref3
                     ,boost::numeric::ublas::vector<double>& lref4);
    void GenRW(double time
               ,boost::numeric::ublas::vector<double>& wref
               ,boost::numeric::ublas::vector<double>& wref1
               ,boost::numeric::ublas::vector<double>& wref2);
    void GenRW34(double time
                 ,boost::numeric::ublas::vector<double>& wref3
                 ,boost::numeric::ublas::vector<double>& wref4);
    void GenRL(double time
               ,boost::numeric::ublas::vector<double>& wref
               ,boost::numeric::ublas::vector<double>& wref1
               ,boost::numeric::ublas::vector<double>& wref2);
    void GenRL34(double time
                 ,boost::numeric::ublas::vector<double>& wref3
                 ,boost::numeric::ublas::vector<double>& wref4);
    void GenR(double time
                        ,boost::numeric::ublas::vector<double>& wref
                        ,boost::numeric::ublas::vector<double>& wref1
                        ,boost::numeric::ublas::vector<double>& wref2);

    void GenR34(double time
                          ,boost::numeric::ublas::vector<double>& wref3
                          ,boost::numeric::ublas::vector<double>& wref4);


    void CalcConvertMatrixT(boost::numeric::ublas::matrix<double>& T
                            ,boost::numeric::ublas::matrix<double>& TT
                            ,boost::numeric::ublas::vector<double>& q);
    void CalcJ(boost::numeric::ublas::matrix<double>& J
               ,boost::numeric::ublas::vector<double>& q);
    void CalcJdot(boost::numeric::ublas::matrix<double>& Jdot
                  ,boost::numeric::ublas::vector<double>& q
                  ,boost::numeric::ublas::vector<double>& qdot);

    boost::numeric::ublas::vector<double> CalcOrientation(boost::numeric::ublas::vector<double>& q);
    void CalcJo(boost::numeric::ublas::matrix<double>& Jo
                ,boost::numeric::ublas::vector<double>& q);
    void CalcJodot(boost::numeric::ublas::matrix<double>& Jodot
                   ,boost::numeric::ublas::vector<double>& q
                   ,boost::numeric::ublas::vector<double>& qdot);
	
    void CalcFrenetFrame(double time
                         ,boost::numeric::ublas::matrix<double>& F
                         ,boost::numeric::ublas::matrix<double>& F1
                         ,boost::numeric::ublas::matrix<double>& F2);

    boost::numeric::ublas::vector<double> CalcOrientationControlSignal(double time
                                                ,boost::numeric::ublas::vector<double>& pl
                                                ,boost::numeric::ublas::vector<double>& pldot
                                                ,double& phi);

    void SetStateVal(boost::numeric::ublas::vector<double>& pos
                     ,boost::numeric::ublas::vector<double>& vel
                     ,boost::numeric::ublas::vector<double>& acc
                     ,boost::numeric::ublas::vector<double>& posall
                     ,boost::numeric::ublas::vector<double>& velall
                     ,boost::numeric::ublas::vector<double>& accall);
    void LogingData(unsigned int step);
    void CalcJ23(boost::numeric::ublas::matrix<double>& J1
                 ,boost::numeric::ublas::matrix<double>& J2
                 ,boost::numeric::ublas::matrix<double>& J3
                 ,boost::numeric::ublas::vector<double>& q
                 ,boost::numeric::ublas::vector<double>& q1
                 ,boost::numeric::ublas::vector<double>& q2
                 ,boost::numeric::ublas::vector<double>& q3
                 ,boost::numeric::ublas::vector<double>& q4);

    boost::numeric::ublas::vector<double> SyncCon(double time
                           ,boost::numeric::ublas::vector<double>& posall
                           ,boost::numeric::ublas::vector<double>& velall
                           ,boost::numeric::ublas::vector<double>& pw
                           ,boost::numeric::ublas::vector<double>& pwdot);

    void IndependentCon(unsigned int max_step
                        ,bool enable_noise
                        ,bool enable_resolution
                        ,bool enable_sync);


    void ContouringCon(unsigned int max_step
                       ,bool enable_noise
                       ,bool enable_resolution
                       ,bool enable_sync);

    void modContouringCon(unsigned int max_step
                          ,bool enable_noise
                          ,bool enable_resolution
                          ,bool enable_sync);
};
class control3dExp:public control3d{
public:
    control3dExp(unsigned int max_step);
    void IndependentCon(unsigned int step
                        , bool enable_sync);
    void ContouringCon(unsigned int step
                       ,short AioId
                       ,short CntId
                       ,bool enable_sync);
    void modContouringCon(unsigned int step
                          ,short AioId
                          ,short CntId
                          ,bool enable_sync);

};

#endif
