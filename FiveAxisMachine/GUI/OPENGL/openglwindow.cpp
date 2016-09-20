#include "openglwindow.h"
#include "ui_openglwindow.h"
#include <GL/freeglut.h>
boost::numeric::ublas::matrix<double> *openglwindow::GLdatalog;

openglwindow::openglwindow(QWidget *parent) :
    QMainWindow(parent)
{
    glutInit;
    window_GL.reset(new Ui::openglwindow);

    this->move(0,0);
}
void openglwindow::ready
(boost::numeric::ublas::matrix<double> *datalogptr){
       GLdatalog = datalogptr;
       window_GL->setupUi(this);
       show();
}

openglwindow::~openglwindow()
{

}

void openglwindow::on_pushButton_Close_openglwindow_clicked()
{
    close();
}
