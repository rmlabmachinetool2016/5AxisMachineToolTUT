#include "AdaptiveControl.h"
#include "define.h"
#include "iostream"
#include "LIB/math.hpp"
typedef boost::numeric::ublas::vector<double> bstvector;
typedef boost::numeric::ublas::matrix<double> bstmatrix;
typedef boost::numeric::ublas::matrix_column<bstmatrix> matcol;
typedef boost::numeric::ublas::matrix_row<bstmatrix> matrow;
using namespace boost::numeric::ublas;
AdaptiveControl::AdaptiveControl()
{

    r_c.resize(2);
    y_c.resize(2);

    vare1.resize(2);
    vare2.resize(2);
}
void AdaptiveControl::SetProfile(bstmatrix *preprofile, bstmatrix *profile1, bstmatrix *profile2){
    preprofileptr = preprofile;
    datalog = profile1;
    datalog2 = profile2;

}

void AdaptiveControl::MRACS_LZ(int step,bstvector &force
                                , bstvector &current_pos){
    //limiting zero ---> L(z^-1)

        this->CalcXi(m,step,current_pos);

    //Variable Gain
        //this->LSmethod(Gain1,Gain2);//Least-squares Algorithm
        this->Trmethod(GainX1,xiX1,traceX1);//Fixied Trace Algorithm
        this->Trmethod(GainX2,xiX2,traceX2);//Fixied Trace Algorithm
        this->Trmethod(GainY1,xiY1,traceY1);//Fixied Trace Algorithm
        this->Trmethod(GainY2,xiY2,traceY2);//Fixied Trace Algorithm


        this->AdapY1(r_c,y_c,step,current_pos);

            vare1(0) = (r_c(0)-inner_prod(theta_X1,xiX1))/(1+inner_prod(prod(GainX1,xiX1),xiX1));
            vare2(0) = (y_c(0)-inner_prod(theta_X2,xiX2))/(1+inner_prod(prod(GainX2,xiX2),xiX2));

            vare1(1) = (r_c(1)-inner_prod(theta_Y1,xiY1))/(1+inner_prod(prod(GainY1,xiY1),xiY1));
            vare2(1) = (y_c(1)-inner_prod(theta_Y2,xiY2))/(1+inner_prod(prod(GainY2,xiY2),xiY2));



            theta_X1 = theta_X1+prod(GainX1,xiX1)*vare1(0);//gyaku
            test = theta_X2+prod(GainX2,xiX2)*vare2(0);
            if(test(0)>0)
            theta_X2 = test;//gyaku

            theta_Y1 = theta_Y1+prod(GainY1,xiY1)*vare1(1);//gyaku
            test = theta_Y2+prod(GainY2,xiY2)*vare2(1);
            if(test(0)>0)
            theta_Y2 = test;//gyaku


    /////////////test code   ///////////////////////////////////
            (*datalog2)(0,step)=theta_X2(0);
            //(*datalog2)(1,step)=vare2(1);
            (*datalog2)(1,step)=theta_X2(1);
            (*datalog2)(2,step)=theta_X2(2);
            (*datalog2)(3,step)=theta_X2(3);
            (*datalog2)(4,step)=theta_X2(4);
            (*datalog2)(5,step)=theta_X2(5);

    //std::cout<<vare2(1)<<std::endl;
    /////////////test code   ///////////////////////////////////
        this->CalcXi(0,step,current_pos);

                force(0) = (inner_prod(xiX1,theta_X1)
                                -inner_prod(subrange(xiX2,1,ns+np+2)
                                            ,subrange(theta_X2,1,ns+np+2)))/theta_X2(0);

                force(1) = (inner_prod(xiY1,theta_Y1)
                                -inner_prod(subrange(xiY2,1,ns+np+2)
                                            ,subrange(theta_Y2,1,ns+np+2)))/theta_Y2(0);

}

void AdaptiveControl::LSmethod(bstmatrix &Gain1, bstmatrix &Gain2){

    double traceR;
    double ramda = 0.85;
    traceR = numeric::ublas::trace(Gain2);
    x = prod(Gain1,outer_prod(xiX1,xiX1));
    Gain1 = (Gain1 - (prod(x,Gain1))
                            /(ramda+inner_prod(prod(Gain1,xiX1),xiX1)))/ramda;

    x = prod(Gain2,outer_prod(xiX2,xiX2));
    Gain2 = (Gain2 - (prod(x,Gain2))
                            /(ramda+inner_prod(prod(Gain2,xiX2),xiX2)))/ramda;

}
void AdaptiveControl::Trmethod(bstmatrix &Gain,bstvector &xi,double trace){

    //double traceR;
    //double sigma1=1,sigma2=1;//preinput

    rambda = 1-numeric::ublas::norm_2_sq(prod(Gain,xi))
                /((1+inner_prod(prod(Gain,xi),xi))*trace);



    x = prod(Gain,outer_prod(xi,xi));
    Gain = (Gain - (prod(x,Gain))
                            /(1+inner_prod(prod(Gain,xi),xi)))/rambda;
}
void AdaptiveControl::AdapY1(bstvector &r_c, bstvector &y_c, int &step, bstvector &current_pos){
    //C(z^-1)r(k)-----> r_c
    //C(z^-1)y(k)-----> y_c

    switch (nc) {
        case 0:
        /*
            r_c = (*preprofileptr)(0,step);
            y_c =  current_pos(0);*/
            break;

        case 3:
            r_c(0) = inner_prod(C_pole,subrange(row((*preprofileptr),0),step-3,step+1));
            y_c(0) = inner_prod(subrange(C_pole,0,nc),subrange(row((*datalog),13),step-3,step));
            y_c(0) += current_pos(0);

            r_c(1) = inner_prod(C_pole,subrange(row((*preprofileptr),1),step-3,step+1));
            y_c(1) = inner_prod(subrange(C_pole,0,nc),subrange(row((*datalog),21),step-3,step));
            y_c(1) += current_pos(1);

            break;


        case 4 :
        /*
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
                r_c += C(i)*(*preprofileptr)(0,step-nc+i);
                if(i<nc)y_c += C(i)*(*datalog)(13,step-nc+i);//pos
            }
            y_c += C(nc)*current_pos(0);*/
            break;


    }
}


void AdaptiveControl::LoadFormParameter(std::vector<double> *conparam, std::vector<double> *conparam2){

    L0 = (*conparam2)[16] ;
    L1 = (*conparam2)[17];
    //(*conparam2)[18] = ui->lineEdit_AdaCon_L2_X->text().toDouble();
    d = (*conparam2)[19] ;
    n = (*conparam2)[20] ;
    nb = (*conparam2)[21] ;
    nf = (*conparam2)[22] ;
    nd = (*conparam2)[23] ;
    m = (*conparam2)[24] ;
    nc = (*conparam2)[25] ;
    nr = (*conparam2)[26];
    np = (*conparam2)[27];
    nq = (*conparam2)[28];
    ns = (*conparam2)[29];

    std::cout<<"LoadFormParameter          nr   "<<nr<<"   np    "<<np<<"     nq     "
            <<nq<<"    ns      "<<ns<<std::endl;

    xiX1.resize(nq+1);
    xiX2.resize(ns+np+2);
    xiX2.clear();

    xiY1.resize(nq+1);
    xiY2.resize(ns+np+2);
    xiY2.clear();



    theta_X1.resize(nq+1);
    theta_X2.resize(ns+np+2);

    input.resize(np);
    output.resize(ns+1);
    ref.resize(nq+1);

    theta_X1.clear();
    theta_X2.clear();
    theta_X2(0) = pow(0.1,8);
    theta_X2(1) = 0.0;
    theta_X2(2) = 0;
    theta_X2(3) = 0;
    std::cout<<"theta_X2 size    "<<ns+np+2<<std::endl;
    theta_Y1 = theta_X1;
    theta_Y2 = theta_X2;


    GainX1 = identity_matrix<double>(nq+1);
    GainX2 = identity_matrix<double>(ns+np+2);
    /*
        Gain1 = 100000*Gain1;
        Gain2 = 10*Gain2;*/
    if(define::SAMPLING_TIME==0.0002){
        GainX1 = 100000000*GainX1;
        GainX2 = 5000*GainX2;//5000
    }
    else {
        GainX1 = 100000000*GainX1;
        GainX2 = 1000000*GainX2;
    }


    GainY1 = identity_matrix<double>(nq+1);
    GainY2 = identity_matrix<double>(ns+np+2);

    GainY1 = 100000000*GainY1;
    GainY2 = 100000*GainY2;


    traceX1 = numeric::ublas::trace(GainX1);
    traceX2 = numeric::ublas::trace(GainX2);
    traceY1 = numeric::ublas::trace(GainY1);
    traceY2 = numeric::ublas::trace(GainY2);


    //set C(z^-1)
    double beta = -0.6;

    switch (nc){
        case 3:
            C_pole.resize(nc+1);

            /*C_pole(0) = -0.0001;
            C_pole(1) = 0.05;
            C_pole(2) = -0.9;
            C_pole(3) = 1.0;*/
            C_pole(0) = pow(beta,3);
            C_pole(1) = 3*pow(beta,2);
            C_pole(2) = 3*beta;
            C_pole(3) = 1.0;
    }

/*
    (*conparam2)[30] = ui->lineEdit_AdaCon_L0_Y1->text().toDouble();
    (*conparam2)[31] = ui->lineEdit_AdaCon_L1_Y1->text().toDouble();
    (*conparam2)[32] = ui->lineEdit_AdaCon_L2_Y1->text().toDouble();
    (*conparam2)[33] = ui->lineEdit_AdaCon_d_Y1->text().toDouble();
    (*conparam2)[34] = ui->lineEdit_AdaCon_n_Y1->text().toDouble();
    (*conparam2)[35] = ui->lineEdit_AdaCon_nb_Y1->text().toDouble();
    (*conparam2)[36] = ui->lineEdit_AdaCon_nf_Y1->text().toDouble();
    (*conparam2)[37] = ui->lineEdit_AdaCon_nd_Y1->text().toDouble();
    (*conparam2)[38] = ui->lineEdit_AdaCon_m_Y1->text().toDouble();
    (*conparam2)[39] = ui->lineEdit_AdaCon_nc_Y1->text().toDouble();
    (*conparam2)[40] = ui->lineEdit_AdaCon_nr_Y1->text().toDouble();
    (*conparam2)[41] = ui->lineEdit_AdaCon_np_Y1->text().toDouble();
    (*conparam2)[42] = ui->lineEdit_AdaCon_nq_Y1->text().toDouble();
    (*conparam2)[43] = ui->lineEdit_AdaCon_ns_Y1->text().toDouble();*/

}
void AdaptiveControl::CalcXi(int Dim,int step,bstvector &current_pos){
    switch(Dim){
        case 0:
        //xiX1 k-d
            for(int i = 0;i<nq+1;i++){
                xiX1(i) = (*preprofileptr)(0,step-i);//ref
            }
        //xiX2 k-d
            for(int i = 0;i<np+1;i++){
                xiX2(i)       = (*datalog)(16,step-i) ;//force
            }
            xiX2(np+1) = current_pos(0);
            for(int i = 1;i<ns+1;i++){
                xiX2(i+np+1)  =  (*datalog)(13,step-i);//pos
            }

        //xiX1 k-d
            for(int i = 0;i<nq+1;i++){
                xiY1(i) = (*preprofileptr)(1,step-i);//ref
            }
        //xiX2 k-d
            for(int i = 0;i<np+1;i++){
                xiY2(i)       = (*datalog)(24,step-i) ;//force
            }
            xiY2(np+1) = current_pos(1);
            for(int i = 1;i<ns+1;i++){
                xiY2(i+np+1)  =  (*datalog)(21,step-i);//pos
            }
        break;
        case 1:
        //xiX1 k-d
            for(int i = 0;i<nq+1;i++)   xiX1(i)       = (*preprofileptr)(0,step-d-i)
                                                            + (*preprofileptr)(0,step-d-1-i);//ref

        //xiX2 k-d
            for(int i = 0;i<np+1;i++)   xiX2(i)       = (*datalog)(16,step-d-i)
                                                            + (*datalog)(16,step-d-1-i);//force

            for(int i = 0;i<ns+1;i++)   xiX2(i+np+1)  = (*datalog)(13,step-d-i)
                                                            + (*datalog)(13,step-d-1-i);//pos


        //xiY1 k-d
            for(int i = 0;i<nq+1;i++)   xiY1(i)       = (*preprofileptr)(1,step-d-i)
                                                            + (*preprofileptr)(1,step-d-1-i);//ref
        //xiY2 k-d
            for(int i = 0;i<np+1;i++)   xiY2(i)       = L0*(*datalog)(24,step-d-i)
                                                            + (*datalog)(24,step-d-1-i);//force

            for(int i = 0;i<ns+1;i++)   xiY2(i+np+1)  = L0*(*datalog)(21,step-d-i)
                                                            + (*datalog)(21,step-d-1-i);//pos
        break;

        case 3:
        //xiX1 k-d
            for(int i = 0;i<nq+1;i++)   xiX1(i)       = (*preprofileptr)(0,step-d-i)
                                                            + 11*(*preprofileptr)(0,step-d-1-i)
                                                            + 11*(*preprofileptr)(0,step-d-2-i)
                                                            + (*preprofileptr)(0,step-d-3-i);//ref
        //xiX2 k-d
            for(int i = 0;i<np+1;i++)   xiX2(i)       = (*datalog)(16,step-d-i)
                                                            + 11*(*datalog)(16,step-d-1-i)
                                                            + 11*(*datalog)(16,step-d-2-i)
                                                            + (*datalog)(16,step-d-3-i);//force

            for(int i = 0;i<ns+1;i++)   xiX2(i+np+1)  = (*datalog)(13,step-d-i)
                                                            + 11*(*datalog)(13,step-d-1-i)
                                                            + 11*(*datalog)(13,step-d-2-i)
                                                            + (*datalog)(13,step-d-3-i);//pos

        //xiY1 k-d
            for(int i = 0;i<nq+1;i++)   xiY1(i)       = (*preprofileptr)(1,step-d-i)
                                                            + 11*(*preprofileptr)(1,step-d-1-i)
                                                            + 11*(*preprofileptr)(1,step-d-2-i)
                                                            + (*preprofileptr)(1,step-d-3-i);//ref
        //xiY2 k-d
            for(int i = 0;i<np+1;i++)   xiY2(i)       = L0*(*datalog)(24,step-d-i)
                                                            + 11*(*datalog)(24,step-d-1-i)
                                                            + 11*(*datalog)(24,step-d-2-i)
                                                            + (*datalog)(24,step-d-3-i);//force

            for(int i = 0;i<ns+1;i++)   xiY2(i+np+1)  = L0*(*datalog)(21,step-d-i)
                                                            + 11*(*datalog)(21,step-d-1-i)
                                                            + 11*(*datalog)(21,step-d-2-i)
                                                            + (*datalog)(21,step-d-3-i);//pos
        break;




    }
}
