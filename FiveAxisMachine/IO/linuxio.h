#ifndef LINUXIO_H
#define LINUXIO_H
#include "boost/numeric/ublas/matrix.hpp"

typedef boost::numeric::ublas::vector<double> bstvector;

class linuxio
{
public:
    linuxio();
    bool Init();
    bool Exit();
    bool OutputDA (bstvector &DAdata);
    bool ReadCount(bstvector &CNTdata);
};

#endif // LINUXIO_H
