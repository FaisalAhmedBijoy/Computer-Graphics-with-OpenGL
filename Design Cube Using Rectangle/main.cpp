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
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //gluOrtho2D(-3, 3, -3, 3); // x min, x max, y min, y max
    glOrtho(-3, 3, -3, 3, -3, 3); // left, right, bottom, top, zNear, zFar
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glViewport(0, 0,windowWidth,windowHeight);
    //triangle();
    //rectangle();
    switch (state)
    {
    case 0:
        //printf('Insert Number: 1 or 2 or 3');
        break;

    case 1:

        //printf('1: Rectangle');
        glPushMatrix();
        glTranslatef(-1.5,0,0);
        rectangle();
        glPopMatrix();
        break;

    case 2:

        // printf('2: Rotation ');
        glPushMatrix();
        //Rotation
        glRotatef(rotation*0.1,0,0,1); // rotation over z axis
        rectangle();
        //triangle();
        glPopMatrix();
        break;

    case 3:
        // cube
        glPushMatrix();

        glRotatef(45,1,0,0); // rotate x axis with positive 45 degree
        glRotatef(-45,0,0,1); // rotate z axis with negative 45 degree
        glRotatef(rotation*0.1,1,1,1); // rotate x,y,z axis

        cube();
        glPopMatrix();
        break;
    }



    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch(key)
    {
    case '0':
        state=0;
        break;
    case '1':
        state=1;
        break;
    case '2':
        state=2;
        flagRotate=true;
        rotation=0;
        break;
    case '3':
        state=3;
        flagRotate=true;
        rotation=0;
        break;
    case 's':
        flagRotate=false;
        break;
    case 27:
        exit(1);
    }
    glutPostRedisplay();
}
void animate()
{
    if (flagRotate == true)
    {
        rotation=(rotation+1);

    }
    glutPostRedisplay();
}

int main (int argc, char **argv)
{
    cout<<"Enter any key"<<endl;
    cout<<"1: Draw the rectangle"<<endl;
    cout<<"2: Rotation the rectangle"<<endl;
    cout<<"3: Draw a cube with 6 rectangle"<<endl;
    cout<<"---------------------------------"<<endl;
    cout<<"---------------------------------"<<endl;
    cout<<"Press: key 's' to stop the rotation"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB
                        | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowWidth,
                       windowHeight);
    glutCreateWindow("Assignment 1607048");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutIdleFunc(animate);

    glutMainLoop();
    return 0;
}
