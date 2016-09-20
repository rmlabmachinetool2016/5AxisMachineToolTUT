#ifndef XENOREADY_H
#define XENOREADY_H
#include <QThread>
#include "control2D.h"

class XenoReady : public QObject
{
    Q_OBJECT
public:
    XenoReady();
    void SetParam();
    void Init(std::vector<double> *conparam, std::vector<double> *conparam2);

    control2dExp *con2dExpptr;

private:
    unsigned int max_step;
signals:

public slots:
    void presetS(std::vector<double> *conparam
                 , std::vector<double> *conparam2);
};

#endif // XENOREADY_H
