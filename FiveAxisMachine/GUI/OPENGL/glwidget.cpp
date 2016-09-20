#include "stdafx.h"
#include "glwidget.h"
#include "openglwindow.h"
#include <QtWidgets>
#include <QtOpenGL>
#include <GL/freeglut.h>

GLWidget::GLWidget(QWidget *parent):
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    step = 0;rotZ=0;
    calcTime.reset(new QElapsedTimer());
    calcTime->start();
    m_timer.reset(new QTimer());
    connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer->start(20);     //  50fps 0.02s
}
GLWidget::~GLWidget(){

}

void GLWidget::initializeGL()
{
    //float sides= 20;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        qglClearColor(Qt::lightGray);

        GLfloat lightPos[] = { -1000.0, 0.0, 900.0, 1 };
        glLightfv(GL_LIGHT0 , GL_POSITION , lightPos);
        ListID = glGenLists(15);

        GLdouble workpiece[][3] = {
            {-100.0,-37.0,-95.0}, // A
            { 100.0,-37.0,-95.0}, // B
            { 100.0, -25.0,-95.0}, // C
            {-100.0, -25.0,-95.0}, // D
            {-100.0,-37.0, 95.0}, // E
            { 100.0,-37.0, 95.0}, // F
            { 100.0, -25.0, 95.0}, // G
            {-100.0, -25.0, 95.0}  // H
        };
        GLdouble vertexCube[8][3] = {
            {-0.5,1.1,-0.5 }, // A
            { 0.5,1.1,-0.5 }, // B
            { 0.5, 10.0,-0.5 }, // C
            {-0.5, 10.0,-0.5 }, // D
            {-0.5,1.1, 0.5 }, // E
            { 0.5,1.1, 0.5 }, // F
            { 0.5, 10.0, 0.5 }, // G
            {-0.5, 10.0, 0.5 }  // H
        };
        GLdouble sideblock[8][3] = {
            {0.0,-200.0,-170.0}, // A
            { 80.0,-200.0,-170.0}, // B
            { 80.0, 120.0,-170.0}, // C
            {0.0, 120.0,-170.0}, // D
            {0.0,-200.0, 170.0}, // E
            { 80.0,-200.0, 170.0}, // F
            { 80.0, 120.0, 170.0}, // G
            {0.0, 120.0, 170.0}  // H
        };
        GLdouble mover[8][3]{
            {0.0,120.0,0.0}, // A
            { 80.0,120.0,0.0}, // B
            { 80.0, 300.0,0.0}, // C
            {0.0, 300.0,0.0}, // D
            {0.0,120.0, 150.0}, // E
            { 80.0,120.0, 150.0}, // F
            { 80.0, 140.0, 150.0}, // G
            {0.0, 140.0, 150.0}  // H
        };
        GLdouble board_mainshaft[8][3]{
            {-240.0,120.0,-10.0}, // A
            { 240.0,120.0,-10.0}, // B
            { 240.0, 300.0,-10.0}, // C
            {-240.0, 300.0,-10.0}, // D
            {-240.0,120.0, 0.0}, // E
            { 240.0,120.0, 0.0}, // F
            { 240.0, 300.0, 0.0}, // G
            {-240.0, 300.0, 0.0}  // H
        };
        GLdouble cover_mainshaft[8][3]{
            {-30.0,-200.0,10.0}, // A
            { 30.0,-200.0,10.0}, // B
            { 30.0, 0.0,10.0}, // C
            {-30.0, 0.0,10.0}, // D
            {-30.0,-200.0,20.0}, // E
            { 30.0,-200.0,20.0}, // F
            { 30.0, 0.0,20.0}, // G
            {-30.0, 0.0,20.0}  // H
        };
        GLdouble BackIron_mainshaft[8][3]{
            {-40.0,-200.0,-10.0}, // A
            { 40.0,-200.0,-10.0}, // B
            { 40.0, 0.0,-10.0}, // C
            {-40.0, 0.0,-10.0}, // D
            {-40.0,-200.0,10.0}, // E
            { 40.0,-200.0,10.0}, // F
            { 40.0, 0.0,10.0}, // G
            {-40.0, 0.0,10.0}  // H
        };
        /*GLdouble Normal[6][3]{
            {0.0,0.0,-1.0},
            {0.0,-1.0,0.0},
            {1.0,0.0,0.0},
            {0.0,1.0,0.0},
            {-1.0,0.0,0.0},
            {0.0,0.0,1.0}
        };*/

        enum {
            A = 0, B, C, D, E, F, G, H,
        };
        int col[][3] = {
            {204, 204, 255},
            {51, 51, 102},
            {51, 255, 102},
            {51, 51, 102},
            {204, 204, 255},
            {204, 204, 255},

        };
        int col2[][3] = {
            {204, 204, 255},
            {51, 51, 102},
            {51, 255, 102},
            {51, 51, 102},
            {204, 204, 255},
            {254, 254, 255},

        };

        int face[][4] = {
            {A, B, C, D},
            {A, E, F, B},
            {B, F, G, C},
            {C, G, H, D},
            {D, H, E, A},
            {E, F, G, H},
        };
        int edge[][2] = {
            { A, B },
            { B, C },
            { C, D },
            { D, A },
            { E, F },
            { F, G },
            { G, H },
            { H, E },
            { A, E },
            { B, F },
            { C, G },
            { D, H },
        };


        glNewList(ListID,GL_COMPILE);//workpiece

        for (int i = 0; i < 6; ++i) {
            glColor3ub(col[i][0], col[i][1], col[i][2]);
            glVertex3dv(workpiece[face[i][0]]);
            glVertex3dv(workpiece[face[i][1]]);
            glVertex3dv(workpiece[face[i][2]]);
            glVertex3dv(workpiece[face[i][3]]);
        }
        glEndList();

        glNewList(ListID+1,GL_COMPILE);//tool

        for (int i = 0; i < 12; ++i) {
            glVertex3dv(vertexCube[edge[i][0]]);
            glVertex3dv(vertexCube[edge[i][1]]);
        }
        glEndList();
        glNewList(ListID+2,GL_COMPILE);//cuttingface
        glColor3ub(204,51,51);
        glVertex3dv(vertexCube[face[1][0]]);
        glVertex3dv(vertexCube[face[1][1]]);
        glVertex3dv(vertexCube[face[1][2]]);
        glVertex3dv(vertexCube[face[1][3]]);
        glEndList();



        cylinder(70,-25,20,ListID+3);//table 3-5
        cylinder(5,80,20,ListID+6);//tool 6-8
        cylinder(95,60,20,ListID+9);//side cylinder 9-11

        glNewList(ListID+12,GL_COMPILE);//side block 12
        for (int i = 0; i < 6; ++i) {
            glColor3ub(col[i][0], col[i][1], col[i][2]);
            glVertex3dv(sideblock[face[i][0]]);
            glVertex3dv(sideblock[face[i][1]]);
            glVertex3dv(sideblock[face[i][2]]);
            glVertex3dv(sideblock[face[i][3]]);
        }
        glEndList();

        glNewList(ListID+13,GL_COMPILE);//mover 13
        for (int i = 0; i < 6; ++i) {

            glColor3ub(col[i][0], col[i][1], col[i][2]);
            glVertex3dv(mover[face[i][0]]);
            glVertex3dv(mover[face[i][1]]);
            glVertex3dv(mover[face[i][2]]);
            glVertex3dv(mover[face[i][3]]);
        }

        glEndList();

            glNewList(ListID+14,GL_COMPILE);//board_mainshaft 14
            for (int i = 0; i < 6; ++i) {
            //glNormal3f(Normal[i][0],Normal[i][1],Normal[i][2]);
                glColor3ub(col[i][0], col[i][1], col[i][2]);
                glVertex3dv(board_mainshaft[face[i][0]]);
                glVertex3dv(board_mainshaft[face[i][1]]);
                glVertex3dv(board_mainshaft[face[i][2]]);
                glVertex3dv(board_mainshaft[face[i][3]]);
            }

            glEndList();
            glNewList(ListID+15,GL_COMPILE);//cover_mainshaft 15
            for (int i = 0; i < 6; ++i) {
            //glNormal3f(Normal[i][0],Normal[i][1],Normal[i][2]);
                glColor3ub(col2[i][0], col2[i][1], col2[i][2]);
                glVertex3dv(cover_mainshaft[face[i][0]]);
                glVertex3dv(cover_mainshaft[face[i][1]]);
                glVertex3dv(cover_mainshaft[face[i][2]]);
                glVertex3dv(cover_mainshaft[face[i][3]]);
            }
            glEndList();


            glEndList();
            glNewList(ListID+16,GL_COMPILE);//backiron_mainshaft 16
            for (int i = 0; i < 6; ++i) {
            //glNormal3f(Normal[i][0],Normal[i][1],Normal[i][2]);
                glColor3ub(col2[i][0], col2[i][1], col2[i][2]);
                glVertex3dv(BackIron_mainshaft[face[i][0]]);
                glVertex3dv(BackIron_mainshaft[face[i][1]]);
                glVertex3dv(BackIron_mainshaft[face[i][2]]);
                glVertex3dv(BackIron_mainshaft[face[i][3]]);
            }
            glEndList();
}

void GLWidget::resizeGL(int width, int height)
{
    //  ビューポートの指定
    glViewport(0, 0, width, height);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);   //  カラーバッファをクリア
    glMatrixMode( GL_PROJECTION );  //  射影行列
    glLoadIdentity();               //  変換行列を初期化
    gluPerspective(30.0,            //  視野角
                    (double)width() / (double)height(),     //  アスペクト比
                    1.0, 3000.0);    //  視野範囲（近距離・遠距離）
    gluLookAt(  300.0, 600.0, 900.0,      //  視点位置
                20.0, 100.0, 0.0,      //  目標位置
                0.0, 70.0, 0.0);     //  上方向
    glMatrixMode( GL_MODELVIEW );   //  モデルビュー行列

    /////////////////tool //////////////////////////////
    glLoadIdentity();
    qglColor(Qt::red);
    glTranslated(xpos,20.0, ypos);
    glRotated((double)m_r, 0.0, 1.0, 0.0);
    glTranslated(0.0,zpos, 0.0);
/*
    glBegin(GL_LINES);
    glCallList(ListID+1);
    glEnd();*/
    glNormal3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glCallList(ListID+6);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glCallList(ListID+7);
    glEnd();
    glBegin(GL_POLYGON);
    glCallList(ListID+8);
    glEnd();

    //cover_mainshaft
        glLoadIdentity();
        glTranslated(0.0,300.0,0.0);
        glTranslated(xpos,0.0, ypos);
        glTranslated(0.0,zpos, 0.0);
        glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
        glCallList(ListID+15);
        glEnd();
    //board_mainshaft
        glLoadIdentity();
        glTranslated(0.0,0.0,-20.0);
        glTranslated(0.0,0.0, ypos);
        glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
        glCallList(ListID+14);
        glEnd();
    //backiron_mainshaft
            glLoadIdentity();
            glTranslated(0.0,300.0,0.0);
            glTranslated(xpos,0.0, ypos);
            glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
            glCallList(ListID+16);
            glEnd();


//////////////////////cutting face///////////////////////////ABEF
        glLoadIdentity();               //  変換行列を初期化

        glTranslated(xpos,0.0, ypos);
        glRotated((double)m_r, 0.0, 1.0, 0.0);

        glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始

        glCallList(ListID+2);
    glEnd();
    /////light mover
        glLoadIdentity();
        glTranslated(160.0,0.0,-20.0);
        glTranslated(0.0,0.0, ypos);
        glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
        glCallList(ListID+13);
        glEnd();

    ////left mover
        glLoadIdentity();
        glTranslated(-240.0,0.0,-20.0);
        glTranslated(0.0,0.0, ypos);
        glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
        glCallList(ListID+13);
        glEnd();

//////////////////////back_table////////////////////////////

    glLoadIdentity();               //  変換行列を初期化
    glRotated(apos, 1.0, 0.0, 0.0);
    glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
    glCallList(ListID);
    glEnd();                        //  線分（GL_LINES）描画終了

    /////////////////table///////////////
    /// \brief glLoadIdentity

    glLoadIdentity();
    glRotated(apos, 1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glCallList(ListID+3);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glCallList(ListID+4);
    glEnd();
    glBegin(GL_POLYGON);
    glCallList(ListID+5);
    glEnd();

    ////////////lightside cylinder/////////
    glLoadIdentity();
    glTranslated(160,0.0,0.0);
    glRotated(90, 0.0, 0, 1.0);

    glNormal3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glCallList(ListID+9);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glCallList(ListID+10);
    glEnd();
    glBegin(GL_POLYGON);
    glCallList(ListID+11);
    glEnd();
    ////////////leftside cylinder/////////
    glLoadIdentity();
    glTranslated(-100,0.0,0.0);
    glRotated(90, 0.0, 0, 1.0);

    glNormal3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glCallList(ListID+9);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glCallList(ListID+10);
    glEnd();
    glBegin(GL_POLYGON);
    glCallList(ListID+11);
    glEnd();
//light side block
    glLoadIdentity();
    glTranslated(160.0,0.0,0.0);
    glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
    glCallList(ListID+12);
    glEnd();

////left side block
    glLoadIdentity();
    glTranslated(-240.0,0.0,0.0);
    glBegin(GL_QUADS);              //  線分（GL_LINES）描画開始
    glCallList(ListID+12);
    glEnd();






    glFlush();                      //  OpenGL の命令をフラッシュ
}
void GLWidget::onTimer()
{
    int a  = calcTime->elapsed();
    double sampling = define::SAMPLING_TIME;

    step = (a/sampling)/1000;


    if(step <(int)openglwindow::GLdatalog->size2()){
    xpos=(*openglwindow::GLdatalog)(13,step)*1000;
    ypos=(*openglwindow::GLdatalog)(21,step)*1000;
    apos=(*openglwindow::GLdatalog)(53,step)*360/2/3.14;
    zpos=(*openglwindow::GLdatalog)(37,step)*1000;
    cpos=(*openglwindow::GLdatalog)(45,step)*360/2/3.14;

    }
    else {step = 0;
        calcTime->restart();}
   // step +=10;
    m_r = (m_r + rotZ)%360;
    update();       //  ウィジットを無効化して再描画
}
void GLWidget::MainShaftRot(int rotationZ){
    rotZ=rotationZ;

}

//円柱
void GLWidget::cylinder(float radius,float height,int sides,GLuint targetID)
{
 double pi = 3.1415;
 //上面
// glNormal3d(0.0, 1.0, 0.0);
// glBegin(GL_POLYGON);
glNewList(targetID,GL_COMPILE);//cylindertop
glNormal3d(0.0, 1.0, 0.0);
 for(double i = 0; i < sides; i++) {
  double t = pi*2/sides * (double)i;
  glVertex3d(radius * cos(t), height, radius * sin(t));
 }
 glEndList();
 //側面
 //glBegin(GL_QUAD_STRIP);
glNewList(targetID+1,GL_COMPILE);//cylinderside
 for(double i=0;i<=sides;i=i+1){
  double t = i*2*pi/sides;
  glNormal3f((GLfloat)cos(t),0.0,(GLfloat)sin(t));
  glVertex3f((GLfloat)(radius*cos(t)),0,(GLfloat)(radius*sin(t)));
  glVertex3f((GLfloat)(radius*cos(t)),height,(GLfloat)(radius*sin(t)));
 }
 glEndList();
 //下面
 //glNormal3d(0.0, -1.0, 0.0);
 //glBegin(GL_POLYGON);
glNewList(targetID+2,GL_COMPILE);//cylinderside
glNormal3d(0.0, -1.0, 0.0);
 for(double i = sides; i >= 0; --i) {
  double t = pi*2/sides * (double)i;
  glVertex3d(radius * cos(t), 0, radius * sin(t));
 }
 glEndList();
}



