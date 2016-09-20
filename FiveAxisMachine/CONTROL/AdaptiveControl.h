#ifndef ADAPTIVECONTROL_H
#define ADAPTIVECONTROL_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

typedef boost::numeric::ublas::vector<double> bstvector;
typedef boost::numeric::ublas::matrix<double> bstmatrix;
typedef boost::numeric::ublas::matrix_column<bstmatrix> matcol;
typedef boost::numeric::ublas::matrix_row<bstmatrix> matrow;

class AdaptiveControl
{
public:
    AdaptiveControl();
    void MRACS_LZ(int step, bstvector &force, bstvector &current_pos);
    void SetProfile(bstmatrix *preprofile,bstmatrix *profile1,bstmatrix *profile2);
    void LoadFormParameter(std::vector<double> *conparam
                           , std::vector<double> *conparam2);
    bstmatrix *preprofileptr;
    boost::numeric::ublas::matrix<double> *datalog;
    boost::numeric::ublas::matrix<double> *datalog2;

private:
    int count;
    double L0,L1;

    int             d //muda
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
    //uchiyama sensei kara-
    bstvector xiX1,xiX2,xiY1,xiY2,theta_X1,theta_X2,theta_Y1,theta_Y2;
    bstvector input,output,ref;
    bstvector test,r_c,y_c,vare1,vare2;
    bstmatrix GainX1,GainX2,GainY1,GainY2;
    bstmatrix x;

    //Intermediate calculation for boost

    double rambda;
    bstvector prod1,prod2,C_pole;

    double traceX1,traceX2,traceY1,traceY2;


    void LSmethod(bstmatrix &Gain1, bstmatrix &Gain2);
    void Trmethod(bstmatrix &Gain,bstvector &xi,double trace);
    void AdapY1(bstvector &r_c, bstvector &y_c, int &step, bstvector &current_pos);
    void CalcXi(int Dim, int step, bstvector &current_pos);
};

#endif // ADAPTIVECONTROL_H
