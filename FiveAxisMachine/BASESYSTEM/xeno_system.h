#ifndef XENO_SYSTEM_H
#define XENO_SYSTEM_H
#include "IO/linuxio.h"
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include "CONTROL/control2D.h"
#include "CONTROL/control3D.h"
#include "mThread.h"

class xeno_func{
public:
     boost::shared_ptr<control2dExp> con2dExp;
     boost::shared_ptr<control3dExp> con3dExp;
     mThread *mThreadPtr;

     bool stop;
    // boost::shared_ptr<IOboard> IOboardptr;
     unsigned int Dim;
};

class xeno_system : public QObject
{
    Q_OBJECT

public:
    xeno_system(QObject* parent=0);
    boost::numeric::ublas::matrix<double> XenoDatalog;
    boost::numeric::ublas::matrix<double> XenoDatalog2;

    linuxio io;
    xeno_func xeno_var;

    void Init(std::vector<double> *conparam
              ,std::vector<double> *conparam2);
    void start();
signals :
    void textFunc(QString);

};

/*
namespace xenoFunc{
extern boost::shared_ptr<control2dExp> con2dExp;
extern boost::shared_ptr<control3dExp> con3dExp;
extern mThread *mThreadPtr;

//extern boost::shared_ptr<IOboard> IOboardptr;
extern unsigned int Dim;
}*/

#endif // XENO_SYSTEM_H
