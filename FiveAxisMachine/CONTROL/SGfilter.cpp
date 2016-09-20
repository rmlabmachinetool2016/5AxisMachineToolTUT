//Savitzky-golay アルゴリズム　08/2016
//多項式近似
//用途　ノイズ除去、微分

#include "SGfilter.h"
#include <iostream>
#include <stdio.h>
#include "LIB/mass.cpp"
#include <QCoreApplication>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <string.h>
#include "define.h"


SGfilter::SGfilter()
{
    targetsampleN = 11;
    mean =(targetsampleN-1)/2;
    order = 4;//order
    sampleN = 80000;
    sampling = define::SAMPLING_TIME;

    sample.resize(sampleN);
    X.resize(order,order);
    invX.resize(order,order);
    B.resize(order,targetsampleN);
    approA.resize(sampleN,order);
    multiA.resize(order);

    for(unsigned int i = 0;i<order;i++){
        for(unsigned int j=0;j<order;j++){
            X(i,j) =0;
        }
        for(unsigned int j=0;j<targetsampleN;j++){
            B(i,j) =0;
        }
    }

    load_sample();

    this->calcX();
    math::invert(X,invX);
    //std::cout<<"invX"<<std::endl<<invX<<std::endl;
    this->calcB();
    //std::cout<<sample<<std::endl;
}

void SGfilter::start(){


/*
    unsigned int target_step;
    for(target_step = mean;target_step<=sampleN-mean;target_step++){
             this->calcA(target_step,approA);

    }

    this->outputfile();
    //std::cout<<"finished"<<std::endl;*/
}

void SGfilter::calcX(){


    for(unsigned int i = 0;i<order;i++){
        for(unsigned int j=0;j<order;j++){
            for(unsigned int count=0
                ;count<targetsampleN;count++){
                x = count-mean;
                X(i,j)+=pow(x*sampling,i+j);
            }
        }
    }
    //std::cout<<"X"<<std::endl
    //        <<X<<std::endl<<std::endl;
}

void SGfilter::calcB(){


    for(unsigned int i = 0;i<order;i++){
        for(unsigned int j=0;j<targetsampleN;j++){
            for(unsigned int count=0 ;count<order;count++){
                x = j - mean;
                B(i,j)+=invX(count,i)*pow(x*sampling ,count);
                //std::cout<<x<<std::endl;
            }
        }
    }

    //std::cout<<"B"<<std::endl
    //        <<B<<std::endl<<std::endl;
}
double SGfilter::calcA(unsigned int target_step
                       ,bstmatrix*datalog
                       ,bstvector&posall
                       ,bstvector&velall
                       ,bstvector&accall){
    double hat_a;
    unsigned int count2;

    for(unsigned int i=0;i<define::NUM_COUNTER;i++)
    {
        for(unsigned int coefA = 0;coefA<order;coefA++){
            hat_a = 0;
            count2 = 0;
            for(unsigned int count=target_step-mean;count<target_step+mean;count++){
                hat_a+=B(coefA,count2)*((*datalog)(8*i+13,count)
                                        -(*datalog)(8*i+13,target_step));
                count2++;
            }
            hat_a +=B(coefA,count2)*(posall(i)
                                     -(*datalog)(8*i+13,target_step));

            if (coefA==2){
                (*datalog)(8*i+15,target_step)=2*hat_a;
            }
            else if (coefA==1){
                (*datalog)(8*i+14,target_step)=hat_a;
            }

            //Ap(target_step,coefA) = hat_a;
        }
    }
    return hat_a;

}

void SGfilter::load_sample(){
    double  para;
    unsigned int i;


    // reading config data
    std::string path;
    path =QCoreApplication::applicationDirPath().toStdString();

    std::ifstream ifs(path+"/sample2.csv");

    i = 0;
    for(i = 0;i < sampleN;i++){
        ifs >> para ;
        sample(i) = para;
    }
}

void SGfilter::outputfile(){
    std::string path;
    path =QCoreApplication::applicationDirPath().toStdString();
    std::ofstream ofs(path+"/outputfile.csv");
    std::string line;
    line = "";
    for(unsigned col = 0;col<sampleN;col++)
    {
    line += boost::lexical_cast<std::string>(sample(col))+",";
    for(unsigned int i=0;i<order;i++){
    line += boost::lexical_cast<std::string>(approA(col,i))+",";
    }

    ofs << line << std::endl;
    line = "";

    }

    ofs.close();
}
