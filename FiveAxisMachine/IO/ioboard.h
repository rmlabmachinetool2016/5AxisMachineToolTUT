#ifndef IOBOARD_H
#define IOBOARD_H
#include <QThread>
#include "define.h"
#include "linuxio.h"

class mThread;

class IOboard : public QThread
{
    Q_OBJECT
public:
    IOboard(QObject *parent = 0
            );
    mThread *Threadptr;
    linuxio io;
    void ExitIOboard();
    bool InitIOboard(unsigned int mode);
    short AioId,CntId;
private:
    long Aioret,CNTret;
    short CntRet2;
    char *AIONoptr ;

    char *CNTNoptr;

    char AIONo[7];
    char CNTNo[7];
signals:
    void Extextfunc(QString);
    void Datalogupdate(unsigned int);
};
void XenoCallBackProc(void *arg);
void catch_signalb(int sig);
#endif // IOBOARD_H
