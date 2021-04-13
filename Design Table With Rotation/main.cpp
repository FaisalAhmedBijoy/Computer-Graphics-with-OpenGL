#include<GL/gl.h>
#include<windows.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
typedef int ll;
ll height=600,width=600;

void triangle()
{
    glBegin(GL_TRIANGLES);
    usleep(10);
    glColor3f(0.0,1.0,1.0);
    glVertex2f(2.0,2.0);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(2.0,0.0);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(0.0,0.0);
    glEnd();
}

void rectangle(float xl, float yl,float width,float height)
{
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,1.0);
    glVertex2f(xl,yl);
    glColor3f(1.0,0.0,1.0);
    glVertex2f(xl+width,yl);
    glColor3f(0.0,1.0,1.0);
    glVertex2f(xl+width,yl+height);
    glColor3f(0.0,1.0,1.0);
    glVertex2f(xl,yl+height);
    glEnd();
}

void block(float x)
{
    glBegin(GL_QUADS);
usleep(1000);
//Front
   glColor3f(1,0.7,0.5);
    glBegin(GL_QUADS);
        glVertex3f(-3.0, 0, 1.5);
        glVertex3f(3.0, 0, 1.5);
        glVertex3f(3.0, 0, -3.0);
        glVertex3f(-3.0, 0, -3.0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-3.0, -0.1, 1.5);
        glVertex3f(3.0, -0.1, 1.5);
        glVertex3f(3.0, -0.1, -3.0);
        glVertex3f(-3.0, -0.1, -3.0);
    glEnd();


    //tables edges
    glColor3f(1,0.7,0.5);

    glBegin(GL_QUAD_STRIP);
        glVertex3f(-3.0, 0, 1.5);
        glVertex3f(-3.0, -0.1, 1.5);
        glVertex3f(3.0, 0, 1.5);
        glVertex3f(3.0, -0.1, 1.5);
        glVertex3f(3.0, 0, -3.0);
        glVertex3f(3.0, -0.1, -3.0);
        glVertex3f(-3.0, 0, -3.0);
        glVertex3f(-3.0, -0.1, -3.0);
        glVertex3f(-3.0, 0, 1.5);
        glVertex3f(-3.0, -0.1, 1.5);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(-2.5, -.1, 1.0);
        glVertex3f(-2.5, -3.0, 1.0);
        glVertex3f(-2.2, -.1, 1.0);
        glVertex3f(-2.2, -3.0, 1.0);
        glVertex3f(-2.2, -.1, 0.7);
        glVertex3f(-2.2, -3.0, 0.7);
        glVertex3f(-2.5, -.1, 0.7);
        glVertex3f(-2.5, -3.0, 0.7);
        glVertex3f(-2.5, -.1, 1.0);
        glVertex3f(-2.5, -3.0, 1.0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.5, -.1, 1.0);
        glVertex3f(2.5, -3.0, 1.0);
        glVertex3f(2.2, -.1, 1.0);
        glVertex3f(2.2, -3.0, 1.0);
        glVertex3f(2.2, -.1, 0.7);
        glVertex3f(2.2, -3.0, 0.7);
        glVertex3f(2.5, -.1, 0.7);
        glVertex3f(2.5, -3.0, 0.7);
        glVertex3f(2.5, -.1, 1.0);
        glVertex3f(2.5, -3.0, 1.0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(-2.5, -.1, -2.5);
        glVertex3f(-2.5, -3.0, -2.5);
        glVertex3f(-2.2, -.1, -2.5);
        glVertex3f(-2.2, -3.0, -2.5);
        glVertex3f(-2.2, -.1, -2.2);
        glVertex3f(-2.2, -3.0, -2.2);
        glVertex3f(-2.5, -.1, -2.2);
        glVertex3f(-2.5, -3.0, -2.2);
        glVertex3f(-2.5, -.1, -2.5);
        glVertex3f(-2.5, -3.0, -2.5);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3f(2.5, -.1, -2.5);
        glVertex3f(2.5, -3.0, -2.5);
        glVertex3f(2.2, -.1, -2.5);
        glVertex3f(2.2, -3.0, -2.5);
        glVertex3f(2.2, -.1, -2.2);
        glVertex3f(2.2, -3.0, -2.2);
        glVertex3f(2.5, -.1, -2.2);
        glVertex3f(2.5, -3.0, -2.2);
        glVertex3f(2.5, -.1, -2.5);
        glVertex3f(2.5, -3.0, -2.5);
    glEnd();



}
ll val=3,move1;


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(-6, 6, -6, 6, -6, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch ( val )
    {
    case 0:
        break;
    case 1:
        glPushMatrix();
        glViewport(0, 0,width,height);
        glTranslatef(-1.5,0,0);
        rectangle(0, 0, 1, 2);
        glPopMatrix ();
        break;
    case 2:
        glPushMatrix();
        glViewport(0, 0,400,300);
        glRotatef(move1,0,-10,-10);
        triangle();
        glPopMatrix();
        break;
    case 3:
        glPushMatrix();
        glViewport(0, 0,width,height);
        glTranslatef(-0.5,-0.5,-2);

        glRotatef(-45,1,0,0);
        glRotatef(45,0,0,1);
        glTranslatef(0.5,0.5,0.5);
        glRotatef(move1,-10,0,10);
        glTranslatef(-0.5,-0.5,-0.5);

        block(1.5);
        glPopMatrix();
        break;
    }

    glFlush();
    glutSwapBuffers();
}

void KeyboardFunc(unsigned char key, ll x, ll y)
{

    switch(key)
    {
    case '1':
        val=1;
        break;
    case '2':
        val=2;
        move1=0;
        break;
    case '3':
        val=3;
        move1=0;
        break;
    case 27:
        exit(1);
    }
    glutPostRedisplay();
}
void animate()
{
    move1++;
    glutPostRedisplay();
}



int main()
{



    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(width,height);
    glutCreateWindow("Shapes");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(KeyboardFunc);
    glutIdleFunc(animate);

    glutMainLoop();

    return 0;

}
