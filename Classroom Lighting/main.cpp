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
const float windowHeight=1000, windowWidth=800;
GLfloat theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
GLfloat eyeX=0;
GLfloat eyeY=10;
GLfloat eyeZ=40;
GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;
float rotation = 0, fan_rt = 0;

bool light_switch_0=false;
bool light_switch_1=false;
bool spot_light_switch=false;

const float aspect_ratio = 1.0 * windowWidth / windowHeight;

static void resize(int windowWidth, int windowHeight)
{

    //glViewport(0, 0, windowWidth, windowHeight/aspect_ratio);
    const float ar = (float) windowWidth / (float) windowHeight;

    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}

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


static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void cube(float color_red = 0.5, float color_green = 0.5, float color_blue = 0.5)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { color_red, color_green, color_blue, 1.0 };
    GLfloat mat_diffuse[] = { color_red, color_green, color_blue, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {10};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for(GLint i = 0; i<6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

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

    // x-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1.0,0.1,0.1);
    glPopMatrix();

    // y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,1.0,0.1);
    glPopMatrix();

    // z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,1.0);
    glPopMatrix();
}
void wall_light()
{
    float length=48;
    float width=1;
    //right light
    glPushMatrix();
    glTranslatef(length/2,length/2,0);
    glScalef(1,3,10);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();


    // left light
    glPushMatrix();
    glTranslatef(-length/2,length/2,0);
    glScalef(1,3,10);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.9,0.9,0.9);
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

void fan_rotation()
{
    fan_rt = fan_rt+1;
    if(fan_rt>360)
        fan_rt =0;
    glutPostRedisplay();
}
void fan()
{
    float base = 5;

    glPushMatrix();
    glRotatef(fan_rt,0,1,0);

    //head
    int head_rot = 0;
    for(int i=0; i<100; i++)
    {
        glPushMatrix();
        glTranslatef(0,base/4,0);
        glRotatef(head_rot,0,1,0);
        glScalef(base/4,base*2,base/4);
        glTranslatef(-0.5,0.0,-0.5);
        cube(1.000, 0.5, 0.5);
        glPopMatrix();
        head_rot+=5;
    }

    //round-base
    int base_rot = 0;
    for (int i=0; i<100; i++)
    {
        glPushMatrix();
        glRotatef(base_rot,0,1,0);
        glScalef(base,base/4,base);
        glTranslatef(-0.5,0.0,-0.5);
        cube(0.8, 0.3, 0.3);
        glPopMatrix();
        base_rot+=5;
    }
    //fan-leg
    for(int i=0; i<=2; i++)
    {
        glPushMatrix();
        glRotatef(120*i,0,1,0);
        glTranslatef((2*base)/2+base/2,base/8,0);
        glScalef(2*base,0.002*base,base/2);
        glTranslatef(-0.5,0.0,-0.5);
        cube(0.000, 0.000, 0.545);
        glPopMatrix();
    }

    fan_rotation();
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

void light_function_0(float x, float y, float z)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable( GL_LIGHT0);
    if (light_switch_0)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);

    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

    }


    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

}

void light_function_1(float x, float y, float z)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable( GL_LIGHT1);
    if (light_switch_1)
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);

    }
    else
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);

    }


    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

}


void spot_light_function(float x, float y, float z)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {0.0, 0.5, 0.0, 1.0};
    GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable( GL_LIGHT2);
    if (spot_light_switch)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);

    }
    else
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);

    }


    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat direction[]= {0,-1,0,1};
    GLfloat cut_off=60;
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,cut_off);

}
void display_setting()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // xmin, xmax, ymin, ymax, near, far
    glFrustum(-5,5,-5,5, 4, 100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    // eye, look, head
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

    //glViewport(0, 0, windowHeight, windowWidth);
    glRotatef(theta,axis_x,axis_y,0);
    glTranslatef(0,0,Tzval);
}
void display(void)
{
    display_setting();

    axes();
    glPushMatrix();
    glTranslatef(0,-1,0);
    wall_floor();
    glPopMatrix();
    weardrobe();
    wall_light();
    glPushMatrix();
    glTranslatef(0,40,-15);
    fan();
    glPopMatrix();

    // left light
    glPushMatrix();
    light_function_0(-23,25,0);
    glTranslatef(-23,25,0);
    glScalef(2,2,2);
    glTranslatef(-0.5,-0.5,-0.5);
    //cube(1.0,0.0,0.0);
    glPopMatrix();

    // right light
    glPushMatrix();
    light_function_1(23,25,0);
    glTranslatef(23,25,0);
    glScalef(2,2,2);
    glTranslatef(-0.5,-0.5,-0.5);
    //cube(1.0,0.0,0.0);
    glPopMatrix();

    //Spot light
    glPushMatrix();
    spot_light_function(0,40,-10);
    glTranslatef(0,40,-10);
    glScalef(2,2,2);
    glTranslatef(-0.5,-0.5,-0.5);
    //cube(0.0,1.0,0.0);
    glPopMatrix();



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
        //theta++;
        //axis_y=1;
        //axis_x=0;
        eyeX--;
        lookX--;
        break;
    case 'r': // right
        //theta--;
        //axis_y=1;
        //axis_x=0;
        eyeX++;
        lookX++;
        break;
    case 'd': // down
        //theta++;
        eyeY--;
        lookY--;
        break;
    case 'u': // up
        //theta--;
        //axis_x=1;
        //axis_y=0;
        eyeY++;
        lookY++;
        break;

    case '1':
        light_switch_0 =! light_switch_0;
        break;
    case '2':
        light_switch_1 =! light_switch_1;
        break;
    case '3':
        spot_light_switch =! spot_light_switch;
        break;
    case '+': // zoom in
        eyeZ--;
        lookZ--;
        //Tzval+=0.2;
        break;
    case '-': // zoom out
        eyeZ++;
        lookZ++;
        //Tzval-=0.2;
        break;
    }


    glutPostRedisplay();
}


int main(int argc, char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(windowHeight,windowWidth);
    glutCreateWindow("Classroom 3D: 1607048");

    cout<<"--------------------------"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"-- 3D Classroom Design ---"<<endl;
    cout<<"-- Faisal Ahmed ----------"<<endl;
    cout<<"-- Roll: 1607048 ---------"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"--------------------------"<<endl;

    cout<<"Press : 1 -> Left Light ON"<<endl;
    cout<<"Press : 2 -> Right Light ON"<<endl;
    cout<<"Press : 3 -> Spotlight Light ON"<<endl;

    cout<<"--------------------------"<<endl;
    cout<<"--------------------------"<<endl;

    cout<<"Press : u -> Rotate Up"<<endl;
    cout<<"Press : d -> Rotate Down"<<endl;
    cout<<"Press : l -> Rotate left"<<endl;
    cout<<"Press : r -> Rotate Right"<<endl;
    cout<<"Press : r -> Rotate Right"<<endl;
    cout<<"Press : + -> Zoom In"<<endl;
    cout<<"Press : - -> Zoom Out"<<endl;

    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutReshapeFunc(resize);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);



    glutMainLoop();
}
