#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<iostream>
using namespace std;

int windowWidth=500;
int windowHeight=500;
int state=0;
bool flagRotate=true;
int rotation=0;

void triangle()
{
    /*
    Coordinate: (2,2),(2,0),(0,0)
    */
    glBegin(GL_TRIANGLES);//Denotes the primitive

    glColor3f(1.0,1.0,1.0);
    glVertex2f(2.0,2.0);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(2.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.0,0.0);
    glEnd(); //Terminates a primitive

}
void rectangle()
{
    /*
    Coordinate: (0,0),(1,0),(1,2),(0,2)
    Colors: (1,0,0),(1,0,0),(0,1,0),(0,1,0)
    */
    glBegin(GL_QUADS);//Denotes the QL_QUADS
    glColor3f(1.0,0.0,0.0);
    glVertex2f(0.0,0.0);

    glColor3f(1.0,0.0,0.0);
    glVertex2f(1.0,0.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(1.0,2.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.0,2.0);
    glEnd();
}

/*
    Draw Cube with 6 rectangle
    Coordinate: (0,0,0),(0,1,0),(1,1,0),(1,0,0) -> z axis: 0
    Coordinate: (0,0,1),(0,1,1),(1,1,1),(1,0,1) -> z axis: 1
    Coordinate: (0,0,0),(1,0,0),(1,0,1),(0,0,1) -> y axis: 0
    Coordinate: (0,1,0),(1,1,0),(1,1,1),(0,1,1) -> y axis: 1
    Coordinate: (0,0,0),(0,0,1),(0,1,1),(0,1,0) -> x axis: 0
    Coordinate: (1,0,0),(1,0,1),(1,1,1),(1,1,0) -> x axis: 1

    Colors
    rectangle 1: RGB(0,0,1)
    rectangle 2: RGB(0,1,0)
    rectangle 3: RGB(0,1,1)
    rectangle 4: RGB(1,0,0)
    rectangle 5: RGB(1,0,1)
    rectangle 6: RGB(1,1,0)


*/
void cube()
{
    /*
    Coordinate: (0,0,0),(0,1,0),(1,1,0),(1,0,0) -> z axis: 0
    */
    glBegin(GL_QUADS);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glEnd();
    /*
    Coordinate: (0,0,1),(0,1,1),(1,1,1),(1,0,1) -> z axis: 1
    */


    glBegin(GL_QUADS);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,0.0,1.0);
    glEnd();
    /*
    Coordinate: (0,0,0),(1,0,0),(1,0,1),(0,0,1) -> y axis: 0
    */

    glBegin(GL_QUADS);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(0.0,0.0,1.0);
    glEnd();

    /*
        Coordinate: (0,1,0),(1,1,0),(1,1,1),(0,1,1) -> y axis: 1
    */
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0, 0.0);
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,0.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(0.0,1.0,1.0);
    glEnd();

    /*
        Coordinate: (0,0,0),(0,0,1),(0,1,1),(0,1,0) -> x axis: 0
    */
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);
    glVertex3f(0.0,1.0,1.0);
    glVertex3f(0.0,1.0,0.0);
    glEnd();

    /*
        Coordinate: (1,0,0),(1,0,1),(1,1,1),(1,1,0) -> x axis: 1
        */
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glVertex3f(1.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,0.0);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8, 8, -8, 8, -8, 8);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, 500, 500);
    glTranslatef(-1,3,0);


    //top
    glPushMatrix();
    glScalef(6,.5,0.5);
    cube();
    glPopMatrix();

    //left: column 1
    glPushMatrix();
    glTranslatef(0,-4.5,0);
    glRotatef(90,0,0,1);
    glScalef(5.0,0.5,0.5);
    cube();
    glPopMatrix();

    //right: column 2
    glPushMatrix();
    glTranslatef(3,0.5,0.5);
    glRotatef(-90,0,0,1);
    glScalef(5.0,0.5,0.5);
    cube();
    glPopMatrix();

    //right: column 3
    glPushMatrix();
    glTranslatef(6,0.5,0.5);
    glRotatef(-90,0,0,1);
    glScalef(5.0,0.5,0.5);
    cube();
    glPopMatrix();


    //middle: row 1
    glPushMatrix();
    glTranslatef(0,-2.0,0);
    glScalef(3.0,0.5,0.5);
    cube();
    glPopMatrix();

    //middle: row 2
    glPushMatrix();
    glTranslatef(3,-3.5,0);
    glScalef(3.0,0.5,0.5);
    cube();
    glPopMatrix();

    //middle: row 3
    glPushMatrix();
    glTranslatef(3,-4.5,0);
    glScalef(3.0,0.5,0.5);
    cube();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}
int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Lab work 2: 1607048");
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    //glutIdleFunc(animate);
    //glutKeyboardFunc(myKeyboardFunc);
    glutMainLoop();
}
