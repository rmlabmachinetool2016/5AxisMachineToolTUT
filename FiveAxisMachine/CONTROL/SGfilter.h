#ifndef SGFILTER_H
#define SGFILTER_H

#include <boost/numeric/ublas/io.hpp>
#include "boost/numeric/ublas/matrix.hpp"


typedef boost::numeric::ublas::vector<double> bstvector;
typedef boost::numeric::ublas::matrix<double> bstmatrix;

class SGfilter
{
public:

    unsigned int targetsampleN ;
    double  mean;
    unsigned int sampleN;//data
    unsigned int order;
    double sampling;


    double x;
    bstmatrix X,invX,B;
    bstmatrix approA;//approximate
    bstvector sample;
    bstvector multiA;
    bstvector invdatalog;

    SGfilter();
    void start();
    void calcX();
    void calcB();
    double calcA(unsigned int target_step, bstmatrix *datalog, bstvector &posall, bstvector &velall, bstvector &accall);
    void load_sample();
    void outputfile();
};

#endif // SGFILTER_H
