#include "XenoReady.h"


XenoReady::XenoReady()
{

}

void XenoReady::SetParam(){

}

void XenoReady::Init(std::vector<double> *conparam
                     ,std::vector<double> *conparam2){
    con2dExpptr->SetConParam(conparam,conparam2);
    
}

void XenoReady::presetS(std::vector<double> *conparam
                        ,std::vector<double> *conparam2){
    max_step = (unsigned int)(*conparam2)[14];
    Init(conparam,conparam2);
    SetParam();

}
