#include "stdafx.h"
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include "OutputFile.h"
#include <math.h>
#include <QApplication>
#include "define.h"


#if basesystem == 0
#include <boost/date_time/posix_time/posix_time.hpp>
#endif

#include "optimization.h"
#include <ctime>
#include <locale>
#include <string>

ExpeOutputFile::ExpeOutputFile
    (boost::numeric::ublas::matrix<double> &datalog)
    :datalogptr(&datalog){
    MparaAxis.clear();
}

std::string ExpeOutputFile::DataDumpfunc(std::string *filename
                                  ,const std::string *filepath
                                  ,const unsigned int *typeNo
                                  ,const bool *energySim){
//CalcOptContouringError();
(void)filepath;
if(*filename == "default")(*filename)=this->defaultNamegenerator();


    std::string path;
    path =QCoreApplication::applicationDirPath().toStdString();
    if((*typeNo)==0)
    path += "/outputfile/Simulation/";
    else if ((*typeNo)==1)
    path += "/outputfile/Experiment/";
    path += *filename;
    path+= ".csv";
    unsigned long maxstep;
    maxstep = (long)datalogptr->size2();
    std::vector <std::vector< double>> Energycons;
    std::vector <double>EnergyconsAll;

    Energycons.resize(7);
    EnergyconsAll.resize(7);
    for(auto &n : Energycons)n.resize(maxstep);

    CalcContouringError(maxstep);
    std::ofstream ofs(path);
        std::string line="";

    unsigned int  MaxdataCount=  define::NUM_DUMPDATA;

    if(!*energySim){
                    for (int i = 0; i < define::NUM_DUMPDATA; i++){
                        line += define::label[i];
                        line += ",";
                    }
                    ofs << line << std::endl;
                    line="";
                for (unsigned long j = 0; j < maxstep;j++){
                    for (unsigned long i = 0; i < MaxdataCount; i++)
                        line += boost::lexical_cast<std::string>
                                ((*datalogptr)(i,j))+",";
                                ofs << line << std::endl;
                                line = "";
    }}

    else {
                for (int i = 0; i < define::NUM_DUMPDATA; i++){
                    line += define::label[i];
                    line += ",";
                    if(i == 17)line+="XaxisEnergy,Sum,";
                    else if(i == 25)line+="YaxisEnergy,Sum,";
                }
                ofs << line << std::endl;
                line="";
                for (unsigned long j = 1,jj=0; j < maxstep;j++,jj=0){
                    for(auto &n :define::energycol){
                    if(!(*datalogptr)(n-6,j)==0)
                        Energycons[jj][j]=abs((MparaAxis[jj*4]*(*datalogptr)(n-5,j)
                            +MparaAxis[jj*4+1]*(*datalogptr)(n-6,j)
                            /abs((*datalogptr)(n-6,j)))
                            *(*datalogptr)(n-6,j));
                            jj++;
}
                }
double para1,para2;
para1=0;para2=0;
for(unsigned long i=1;i<maxstep;i++){
    para1+=Energycons[0][i];
    para2+=Energycons[1][i];
}

        for (unsigned long j = 0; j < maxstep;j++){
            for (unsigned long i = 0; i < MaxdataCount; i++){
                line += boost::lexical_cast<std::string>
                        ((*datalogptr)(i,j))+",";
                        if(i==17){
                            line += boost::lexical_cast<std::string>
                                    (Energycons[0][j])+",";
                            if(j==0)line+=boost::lexical_cast<std::string>
                                    (para1)+",";
                            else line+=",";
                        }
                        else if(i==25){
                            line += boost::lexical_cast<std::string>
                                    (Energycons[1][j])+",";
                            if(j==0)line+=boost::lexical_cast<std::string>
                                    (para2)+",";
                            else line+=",";
                        }
            }
                        ofs << line << std::endl;
                        line = "";
        }
}
    ofs.close();
    path+=".xml";
return path;
}

void ExpeOutputFile::CalcContouringError(unsigned long max_step){
vector<double> pos(2);
double x1,x2,y1,x1_r,y1_r,count;
double L,ec;
bool reverse;

double limit = My_T / define::SAMPLING_TIME;


for (unsigned long j = 0; j < max_step;j++){
    x1=0; ec=1000;
    count = floor(j/limit);
    if(fmod(count,2.0)==1) reverse = true;
    else reverse = false;
    pos (0) = (*datalogptr)(13,j);
    pos (1) = (*datalogptr)(21,j);

    if(reverse) pos(0) = 0.05-pos(0);

///極地付近局所的収束怖い
    for(int i=0;i<1000;i++){
        x1 += My_x1/1000;
        y1 = My_a3*pow(x1,3)+My_a2*pow(x1,2)+My_a1*x1;

        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }

    x1 = x2-My_x1/1000*3;
    for(int i=0;i<1000;i++){
        x1 += My_x1/pow(10,5);
        y1 = My_a3*pow(x1,3)+My_a2*pow(x1,2)+My_a1*x1;

        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }


    x1 = x2-My_x1/100000*3;
    for(int i=0;i<1000;i++){
        x1 += My_x1/pow(10,7);
        y1 = My_a3*pow(x1,3)+My_a2*pow(x1,2)+My_a1*x1;


        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));
        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }


    x1 = x2-My_x1/10000000*3;
    for(int i=0;i<1000;i++){
        x1 += My_x1/pow(10,9);
        y1 = My_a3*pow(x1,3)+My_a2*pow(x1,2)+My_a1*x1;


        L =  sqrt(pow(pos(0)-x1,2)+pow(pos(1)-y1,2));

        if(ec>L ){
            ec = L;
            x2 = x1;
        }
    }

    (*datalogptr)(1,j) = ec;


}
}

void ExpeOutputFile::SetParameter(std::vector<double> GcodeParam){

    GcodeSampling = GcodeParam[0];
    AccTime = GcodeParam[1];
    MotionCount = GcodeParam[2];
    option = GcodeParam[3];
    MparaAxis.resize(13);
    for(unsigned int i = 4,j=0;i<16;i++,j++){
    MparaAxis[j]=GcodeParam[i];
    }
}


std::string ExpeOutputFile::ModeSelect(int mode_num, std::string  filename, unsigned long max_step, std::string filepath){
std::string path;
	switch (mode_num){
		case 0:
            path=HighPrecision(filename,filepath);
			break;
		case 1:
            path=G01AutoContouringMotion(filename,max_step,filepath);//fairing
			break;

		case 2:
            //G01ManualContouringMotion(filename);
			break;
	}
    return path;
}

std::string ExpeOutputFile::HighPrecision(std::string filename, std::string filepath){

	using namespace std;
	double x, y, v, x1 = 0, y1 = 0, v1 = 0, theta;
    double maxstep;
    maxstep =  datalogptr->size2()
                /sizeof((*datalogptr)(0,0));


    std::ofstream ofs(filename);
	ofs << std::endl;
	ofs << "G90" << std::flush;

    for (unsigned long i = 0; i<maxstep - 1; i++)
	{
        x = -(*datalogptr)(10,i + 1) * pow(10.0, 3.0);
        y = -(*datalogptr)(18,i + 1) * pow(10.0, 3.0);

        theta = atan(((*datalogptr)(18, i + 1) - (*datalogptr)(18,i))
                    / ((*datalogptr)(10, i + 1) - (*datalogptr)(10,i)));

        v = (*datalogptr)(11, i) / cos(theta)*pow(10.0, 3.0) * 60;


		if (x1 != x&&y1 != y){ ofs << fixed << setprecision(6) 
			<< "G01X"	<< x 
			<< "Y"		<< y 
			<< "F"		<< v 
			<< std::endl; 
		}

		x1 = x; y1 = y; v1 = v;
	}

	ofs << "%" << std::endl;
	
	ofs.close();

return filename;
}



std::string ExpeOutputFile::G01AutoContouringMotion
(std::string filename
 ,unsigned long max_step
 ,std::string filepath){

	using namespace std;
    using namespace define;

    if(filename == "default")filename=this->defaultNamegenerator();
    std::string path;
        path =QCoreApplication::applicationDirPath().toStdString();
        path += "/outputfile/Gcode/"+filename+".csv";
//////

    double B_time,delta,dl;
    unsigned long  MaxBlockCount,block_w;
    double DatalogCount;
    size_t a = datalogptr->size2();
    std::vector<double> Xpos,Ypos,F;
    Xpos.resize(a);Ypos.resize(a);F.resize(a);
    MaxBlockCount = (unsigned long)floor(max_step*SAMPLING_TIME/GcodeSampling);
	block_w = max_step/MaxBlockCount;


    std::ofstream ofs(path);
	ofs << std::endl;
    ofs << "G90" << std::flush;

	Xpos[0] = 0; Ypos[0] = 0;
    //////
    for (unsigned long i = 1; i<MaxBlockCount; i++)
    {

            B_time = GcodeSampling * i;
            DatalogCount = (double) floor(B_time / SAMPLING_TIME);
            delta = B_time-DatalogCount*SAMPLING_TIME;
            Xpos[i] = (1-delta/SAMPLING_TIME)*(*datalogptr)(10,DatalogCount)
                        + delta/SAMPLING_TIME
                        *(*datalogptr)(10,DatalogCount + 1);
            Ypos[i] = (1-delta / SAMPLING_TIME)*(*datalogptr)(18,DatalogCount)
                        + delta / SAMPLING_TIME
                        *(*datalogptr)(18,DatalogCount + 1);
            }
/*	for (int i = 1; i<MaxBlockCount; i++)
	{
			B_time = GcodeSampling * i;
			DatalogCount = (int) floor(B_time / SAMPLING_TIME);
			delta = B_time-DatalogCount*SAMPLING_TIME;
            Xpos[i] = (*datalogptr)[10][DatalogCount] + delta/SAMPLING_TIME
                        *((*datalogptr)[10][DatalogCount + 1]
                    - (*datalogptr)[10][DatalogCount]);
            Ypos[i] = (*datalogptr)[18][DatalogCount] + delta / SAMPLING_TIME
                        *((*datalogptr)[18][DatalogCount + 1]
                    - (*datalogptr)[10][DatalogCount]);
            }*/
    //////
    for (unsigned long i = MaxBlockCount - 1; i > 0;i--){
        switch (option){
        case 0:
        case 3:
            dl = sqrt(pow(Xpos[i+1] - Xpos[i], 2) + pow(Ypos[i+1] - Ypos[i], 2));
            F[i] = (dl - 0.5*F[i + 1] * AccTime) / (GcodeSampling - 0.5*AccTime);
            break;
        case 1:
            dl = abs(Xpos[i+1] - Xpos[i]);
            F[i] = (dl - 0.5*F[i + 1] * AccTime) / (GcodeSampling - 0.5*AccTime);
            break;
        case 2:
            dl = abs(Ypos[i+1] - Ypos[i]);
            F[i] = (dl - 0.5*F[i + 1] * AccTime) / (GcodeSampling - 0.5*AccTime);
            break;
    }}
    //////
    for (unsigned long i = 1; i < MaxBlockCount+1 ; i++){

        if (F[i-1] != 0 && Xpos[i-1] != Xpos[i] && Ypos[i-1] != Ypos[i] )
         {   ofs << fixed << setprecision(6)<< "G01";

        switch (option){
        case 0:
                ofs << "X" << -Xpos[i] * pow(10.0, 3.0);
                ofs << "Y" << -Ypos[i] * pow(10.0, 3.0);
            break;
        case 1:
				ofs << "X" << -Xpos[i] * pow(10.0, 3.0);

            break;
        case 2:
				ofs << "Y" << -Ypos[i] * pow(10.0, 3.0);
            break;}
        switch(option){
        case 0:
        case 1:
        case 2:
				ofs<< setprecision(2)
				<< "F"	<< F[i-1] * pow(10.0, 3.0) * 60 
                << std::endl;
            break;}
       if (option==3)
            ofs << fixed << setprecision(6)
                <<","
                << Xpos[i] << ","
                << Ypos[i] << ","
                << F[i - 1] << std::endl;
    }}

	ofs << "%" << std::endl;

	ofs.close();
    path+=".xml";
    return path;

}
/*
void OutputFile::GcodeGenerate::G01ManualContouringMotion(String^ filename, array<double, 2>^ datalog, int max_step){

}*/

/*
void OutputFile::OutPutGraph::GeneratePath(unsigned int max_step ,array <double, 2>^datalog){

#define GNUPath "D:/gnuplot/bin/gnuplot.exe -persist"
	FILE *fp ,*data;
	char *data_file,*fullpath,Fullpath[_MAX_PATH];
	std::string a,b;
	fullpath = _fullpath(Fullpath, NULL, _MAX_PATH);
	a = Fullpath;

	

	System::String^ aa = gcnew String(a.c_str());
	//fprintf(gnup, "trajectory");
	Debug::WriteLine(aa);
	data_file = "D:/gnuplot/bin/out.dat";
	data = fopen("D:/gnuplot/bin/out.dat", "w");
	
	for (unsigned int i = 0; i < max_step; i++){
		fprintf(data, "%f\t%f\n", datalog[10, i], datalog[18, i]);
	}
	fclose(data);


	fp = _popen(GNUPath, "w");

	if (fp == NULL){ Debug::Write(1); }
	
	fprintf(fp, "set xrange [0:0.05]\n");
	fprintf(fp, "set yrange [-0.05:0.05]\n");
	fprintf(fp, "unset kye\n"); //凡例を非表示
	//fprintf(fp, "set style line\n");


	fprintf(fp, "plot 'D:/gnuplot/bin/out.dat' with lines lw 2 lc 3 \n");

	//fprintf(gnup, "e\n");
	//fprintf(fp, "plot sin(x)\n");
	
	//_sleep(5000);
	//system("pause");
	fprintf(fp, "exit\n");
	//fflush(fp);
	
	_pclose(fp);
}*/


std::string ExpeOutputFile::defaultNamegenerator(){
    #if basesystem == 0
    std::string filename;

    boost::posix_time::ptime tick;
            tick= boost::posix_time::second_clock::local_time();

    std::cout<<tick<<std::endl;
    filename = boost::posix_time::to_simple_string(tick);
#else
    std::string filename="teest";
    /*
    errno_t err;
    time_t t;
    struct tm t_st;
    _time64(&t);
    err = localtime_s(&t_st,&t);
    t_st.tm_year += 1900;
    t_st.tm_mon += 1;

    filename = boost::lexical_cast<std::string>(t_st.tm_year);
    filename += '_';
    if(t_st.tm_mon < 10)
        filename += '0';
    filename += boost::lexical_cast<std::string>(t_st.tm_mon);
    if(t_st.tm_mday < 10)
        filename += '0';
    filename += boost::lexical_cast<std::string>(t_st.tm_mday);
    filename += '_';
    if(t_st.tm_hour < 10)
        filename += '0';
    filename += boost::lexical_cast<std::string>(t_st.tm_hour);
    if(t_st.tm_min < 10)
        filename += '0';
    filename += boost::lexical_cast<std::string>(t_st.tm_min);
    if(t_st.tm_sec < 10)
        filename += '0';
    filename += boost::lexical_cast<std::string>(t_st.tm_sec);
*/
#endif
return filename;
}
