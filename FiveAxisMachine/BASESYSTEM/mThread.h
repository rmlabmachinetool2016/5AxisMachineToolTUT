#ifndef MTHREAD_H
#define MTHREAD_H
#include <QThread>
#include "IO/ioboard.h"
#include "CONTROL/control2D.h"
#include "CONTROL/control3D.h"
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>


class DesktopMachineToolSystem;

//extern control2dExp *con2dExp;
class mThread : public QObject
{
    Q_OBJECT
public:
    mThread(QObject *parent = 0);
    void softlimitchecker();
    unsigned int controlType,max_step;
    control2dSim *conClass2Dptr;

    boost::shared_ptr<control2dSim> con2dSim;
    boost::shared_ptr<control3d> con3d;

    control2dExp *con2dExp;
    control3dExp *con3dExp;
    mThread *mThreadPtr;
    IOboard *IOboardptr;
    unsigned int *Dim;


    DesktopMachineToolSystem *GUIptr;
    bool con2dSim_,con2dExp_,con3d_,IOboard_,EnableNoise;

    boost::numeric::ublas::matrix<double> datalog;
    boost::numeric::ublas::matrix<double> datalog2;

    IOboard io;
    bool Stopfunc;
    ~mThread();
private :
    int dimention;
    int select_DOF,selectWork,selectControl;

signals :
    void Extextfunc(QString);
    void finished();
public slots:
    void start();
    void getData(std::vector<double> *conparam, std::vector<double> *conparam2);
    void IOtext(QString);
};



#endif // MTHREAD_H
