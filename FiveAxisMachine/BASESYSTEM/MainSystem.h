#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H
#include <QThread>
#include <boost/shared_ptr.hpp>


class DesktopMachineToolSystem;
class mThread;
class xeno_system;

class MainSystem: public QObject
{
    Q_OBJECT
public:
    MainSystem(QObject *parent = 0);

    boost::shared_ptr<DesktopMachineToolSystem> w;
    boost::shared_ptr<mThread>  SubController;
    boost::shared_ptr<QThread>  SubThread;  // I dont know A SubThread from Qt
    boost::shared_ptr<xeno_system>  xeno;

    std::vector<double> *conparam;
    std::vector<double> *conparam2;

    bool multTh;
    ~MainSystem();
private :

public slots:
    void ThreadStop();
    void ThreadStart(bool flug_per);
    void ExpReady();
};

#endif // MAINSYSTEM_H
