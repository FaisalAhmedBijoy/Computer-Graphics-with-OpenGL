/*
3D Classroom Design
Faisal Ahmed
Roll: 1607048
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<iostream>
using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;



static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte quadIndices[6][4] =
{
    {3, 1, 5, 7},
    {2, 0, 4, 6},
    {2, 0, 1, 3},
    {6, 4, 5, 7},
    {2, 3, 7, 6},
    {0, 1, 5, 4}
};

void cube(float color_red = 0.5, float color_green = 0.5, float color_blue = 0.5)
{
    glBegin(GL_QUADS);
    for(GLint i = 0; i<6; i++)
    {
        glColor3f(color_red,color_green,color_blue);

        for(GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[quadIndices[i][j]][0]);
        }
    }
    glEnd();
}

void axes()
{
    float length = 10;
    float width = 1;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1.0,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,1.0,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,1.0);
    glPopMatrix();
}

void wall_floor()
{
    float length = 50;
    float width = 1;
    //floor
    glPushMatrix();
    glScalef(length,width,length);
    glTranslatef(-0.5,-1,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();
    //left
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(width,length,length);
    glTranslatef(0,0,-0.5);
    cube(0.3,0.7,0.7);
    glPopMatrix();
    // right
    glPushMatrix();
    glTranslatef(-length/2,0,0);
    glScalef(width,length,length);
    glTranslatef(0,0,-0.5);
    cube(0.3,0.7,0.7);
    glPopMatrix();
    // Up
    glPushMatrix();
    glTranslatef(0,length,0);
    glScalef(length,width,length);
    glTranslatef(-0.5,0,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // Front
    glPushMatrix();
    glTranslatef(0,0,-length/2);
    glScalef(length,length,width);
    glTranslatef(-0.5,0,0);
    cube(0,1.0,0);
    glPopMatrix();

    // Black board
    glPushMatrix();
    glTranslatef(0,length/3,-(length/2 -1));
    glScalef(length/2,length/3,width);
    glTranslatef(-0.5,0,0);
    cube(0.0,0.0,0.0);
    glPopMatrix();
}

void chair()
{

    float length=20;
    float width=1;

    //base seat
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(length,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    // leg base 1
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // leg base 2
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // leg base 3
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,+ length/2 -width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // leg  base 4
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();

    // upper  1
    glPushMatrix();
    glTranslatef(length/2 -width/2,length,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,1,0);
    glPopMatrix();
    // upper 2
    glPushMatrix();
    glTranslatef(-length/2 -width/2,length,length/2+width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,1,0);
    glPopMatrix();

    // upper close 1
    glPushMatrix();
    glTranslatef(0,length,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,0,1);
    glPopMatrix();
    // upper close 2
    glPushMatrix();
    glTranslatef(0,length+5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,1);
    glPopMatrix();

    // upper close 3
    glPushMatrix();
    glTranslatef(0,length-5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,1);
    glPopMatrix();


}


void table()
{
    float length=20;
    float width=1;

    //base
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(length,width+1,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    // base 1
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // base 2
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // base 3
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,+ length/2 -width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();
    // base 4
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();


}

void weardrobe()
{
    float length=20;
    float width=10;

    // base
    glPushMatrix();
    glTranslatef(length,0,-15);
    glScalef(width,length,width);
    glTranslatef(-0.5,0,-0.5);
    cube(0.5,0,0);
    glPopMatrix();

    // divider
    glPushMatrix();
    glTranslatef(length,0,-10);
    glScalef(1,length,1);
    glTranslatef(-0.5,0,-0.5);
    cube(0.54,0.27,0.075);
    glPopMatrix();

}
void display_setting()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5,5,-5,5, 4, 70);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    // eye, look, head
    gluLookAt(10,10,40, 1,5,1, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);
    glRotatef(theta,axis_x,axis_y,0);
    glTranslatef(0,0,Tzval);
}
void display(void)
{
    display_setting();

    axes();
    wall_floor();
    weardrobe();
    //table();
    //chair();

    // First table chair
    for(int i=-20; i<=20; i+=10)
    {
        glPushMatrix();
        glTranslatef(i,3,10);
        glScalef(0.2,0.2,0.2);
        chair();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i,3,0);
        glScalef(0.3,0.3,0.3);
        table();
        glPopMatrix();
    }
    // Second table chair
    for(int i=-20; i<=20; i+=10)
    {
        glPushMatrix();
        glTranslatef(i,3,25);
        glScalef(0.2,0.2,0.2);
        chair();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i,3,15);
        glScalef(0.3,0.3,0.3);
        table();
        glPopMatrix();
    }


    glFlush();
    glutSwapBuffers();

}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case 'l': // left
        theta++;
        axis_y=1;
        axis_x=0;
        break;
    case 'r': // right
        theta--;
        axis_y=1;
        axis_x=0;
        break;
    case 'd': // down
        theta++;
        axis_x=1;
        axis_y=0;
        break;
    case 'u': // up
        theta--;
        axis_x=1;
        axis_y=0;
    case '+': // zoom in
        Tzval+=0.2;
        break;
    case '-': // zoom out
        Tzval-=0.2;
        break;
    }

    glutPostRedisplay();
}


int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(700,700);
    glutCreateWindow("Classroom 3D: 1607048");

    cout<<"--------------------------"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"-- 3D Classroom Design ---"<<endl;
    cout<<"-- Faisal Ahmed ----------"<<endl;
    cout<<"-- Roll: 1607048 ---------"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"Press : u -> Rotate Up"<<endl;
    cout<<"Press : d -> Rotate Down"<<endl;
    cout<<"Press : l -> Rotate left"<<endl;
    cout<<"Press : r -> Rotate Right"<<endl;
    cout<<"Press : r -> Rotate Right"<<endl;
    cout<<"Press : + -> Zoom In"<<endl;
    cout<<"Press : - -> Zoom Out"<<endl;

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();
}
