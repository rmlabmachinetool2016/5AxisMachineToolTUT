#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
//#include <gl/freeglut.h>
#include <QElapsedTimer>
#include <boost/shared_ptr.hpp>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    ~GLWidget();
protected slots:
    void    onTimer();
    void MainShaftRot(int rotationZ);
private:
    boost::shared_ptr<QTimer> m_timer;
    boost::shared_ptr<QElapsedTimer> calcTime;

    void cylinder(float radius
                  ,float height
                  ,int sides
                  ,GLuint targetID);
    int     m_r,step,rotZ;
    double xpos,ypos,apos,cpos,zpos;
    GLuint ListID=0;
 double pi = 3.1415;

};

#endif // GLWIDGET_H
