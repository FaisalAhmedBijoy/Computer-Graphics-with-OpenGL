#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#include <fstream>
#include <iostream>
using namespace std;


const int window_width = 1200;
const int window_height = 750;
int mx,my;

GLfloat eye[] = {0,40,50};
GLfloat look[] = {0,40,-500};
//GLfloat eye[] = {0,5,20};
//GLfloat look[] = {0,5,-100};

float nipa_z = 10,nipa_x = 0;
float theta_right = 0, theta_left=0, theta =0;
bool leg_rot_x = 0,leg_rot_y = 0,leg_rot_z = 0;

int b_rot = 0;


float rot = 0;

unsigned int ID;
#define GL_CLAMP_TO_EDGE 0x812F

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

static GLubyte c_ind[6][4] =
{
//    {0,2,6,4},
//    {5,7,3,1},
//    {0,4,5,1},
//    {3,7,6,2},
//    {0,1,3,2},
//    {6,7,5,4}

//    {2,3,7,6}, //top
//    {1,0,4,5}, //bottom
//    {2,0,1,3}, //left
//    {7,5,4,6}, //right
//    {3,1,5,7}, //front
//    {6,4,0,2} //back


// {0,2,6,4},
// {3,1,5,7},
// {2,3,7,6},
// {1,0,4,5},
// {2,0,1,3},
// {7,5,4,6}

    {3,1,5,7}, //front
    {2,0,1,3}, //left
    {7,5,4,6}, //r
    {2,3,7,6}, //top
    {1,0,5,4}, //bot
    {6,4,0,2}, //back


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

void material_property(float R, float G, float B)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { R, G, B, 1.0 };
    //GLfloat mat_ambient[] = { 0, 0, 0, 1.0 };
    GLfloat mat_diffuse[] = { R, G, B, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {255};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

}




void cube(float R=0.5, float G=0.5, float B=0.5 )
{
    material_property(R,G,B);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //        glColor3f(R,G,B);
        //
        //        R += 0.05;
        //        G += 0.05;
        //        B += 0.05;
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

//        for (GLint j=0; j<4; j++)
//        {
//            glVertex3fv(&v_cube[c_ind[i][j]][0]) ;
//            glTexCoord2f(1,1);
//        }
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);

    }
    glEnd();
}



void LoadTexture(const char*filename, int rep = 1)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(rep)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void buiding()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);

    glPushMatrix();
    glTranslatef(0,30,0);
    glScalef(20,60,20);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);

    glPushMatrix();
    glTranslatef(50,30,0);
    glScalef(20,60,20);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //roof
    glPushMatrix();
    glTranslatef(50,60,0);
    glScalef(20,1,20);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    //main road
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);

    glPushMatrix();
    glTranslatef(0,0.5,20);
    glScalef(100,1,10);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //side road
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);

    glPushMatrix();
    glTranslatef(-50,0.5,0);
    glRotatef(90,0,1,0);
    glScalef(100,1,10);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);



}

void _light()
{
    //GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 50.0, 0, 1.0 };

    glEnable( GL_LIGHT7);

    glLightfv( GL_LIGHT7, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT7, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT7, GL_SPECULAR, light_specular);

    glLightfv( GL_LIGHT7, GL_POSITION, light_position);


    /*GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);*/
}
void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0); //RED Line
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,1,0); //GREEN Line
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0,0,1); //BLUE Line
    glPopMatrix();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    //for light


    case 't':

        eye[1]++;
        look[1]++;

        break;
    case 'g':

        eye[1]--;
        look[1]--;
        break;
    case 'h':
        look[0]++;
        break;
    case 'f':
        look[0]--;
        break;

    case 'e':
        rot--;
        break;
    case 'r':
        rot++;
        break;
    case 'l':

            eye[0]++;
            look[0]++;

        break;
    case 'j':

            eye[0]--;
            look[0]--;

        break;
    case '+':
        eye[2]--;
        break;
    case 'i':

            eye[2]--;

        break;
    case '-':
        eye[2]++;
        break;
    case 'k':

            eye[2]++;


        break;
    case ' ':
        b_rot += 20;
        break;
    case '5':
        nipa_z +=  2;
        leg_rot_x = 1;
        leg_rot_y = 0;
        leg_rot_z = 0;
        eye[2] +=1;
        look[2] +=1;
    if(theta>0)
        theta -=10;
    else
        theta +=10;
//        if(theta_left>0)
//            theta_left -=10;
//        else
//            theta_left +=10;
//        if(theta_right>0)
//            theta_right +=10;
//        else
//            theta_right -=10;

        break;
    case '8':
        nipa_z -= 2;
        leg_rot_x = 1;
        leg_rot_y = 0;
        leg_rot_z = 0;
        eye[2] -=1;
        look[2] -=1;
        if(theta<0)
        theta +=10;
    else
        theta -=10;


//        if(theta_left<0)
//            theta_left +=10;
//        else
//            theta_left -=10;
//        if(theta_right<0)
//            theta_right -=10;
//        else
//            theta_right +=10;
        break;
    case '7':
        nipa_x -=1;
        leg_rot_x = 0;
        leg_rot_y = 0;
        leg_rot_z = 1;
        if(theta<0)
        theta +=10;
    else
        theta -=10;

        eye[0] -=1;
        look[0] -=1;
        break;
    case '9':
        nipa_x +=1;
        leg_rot_x = 0;
        leg_rot_y = 0;
        leg_rot_z = 1;
        eye[0] +=1;
        look[0] +=1;
         if(theta>0)
        theta -=10;
    else
        theta +=10;
        break;
    }

    glutPostRedisplay();
}

void robot()
{
    glPushMatrix();
    glTranslatef(nipa_x,0,nipa_z);

    glPushMatrix();
    glTranslatef(0,20,0);
    glutSolidSphere(5,16,16);
    glPopMatrix();
    //gola
    glPushMatrix();
    glTranslatef(0,15-2.5,0);
    glScalef(2,5,2);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();

    //body
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(10,10,5);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslatef((5-1),-(2.5),0);
    glRotatef(theta,leg_rot_x,leg_rot_y,leg_rot_z);
    glScalef(2,5,2);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,1,0);
    glPopMatrix();

    //left leg
    glPushMatrix();
    glTranslatef(-(5-1),-(2.5),0);
    glRotatef(-theta,leg_rot_x,leg_rot_y,leg_rot_z);
    glScalef(2,5,2);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,1,0);
    glPopMatrix();

    glPopMatrix();

}

void wall()
{
    float set_len = 200, set_width = 200;
    float wall_len = 50, wall_height = 50, wall_width = 5;

    glPushMatrix();
    glTranslatef(0,wall_height/2,0);
    glScalef(wall_len,wall_height,wall_width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube();
    glPopMatrix();

    //side wall
    for(int i=-1; i<=1; i+=2)
    {
        glPushMatrix();
        glTranslatef(i*set_len/2,wall_height/2,0);
        glTranslatef(i*(wall_len/2+wall_width/2),0,-wall_len);
        glScalef(wall_width,wall_height,2*wall_len);
        glTranslatef(-0.5,-0.5,-0.5);
        cube();
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(0,wall_height/2,-2*wall_len);
    glScalef(wall_len,wall_height,wall_width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,0,0);
    glPopMatrix();

}


static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int lim = 8;
    glFrustum(-lim, lim, -lim, lim, 4, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

    //gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    gluLookAt(eye[0],eye[1],eye[2], look[0],look[1],look[2], 0,1,0);
    //glViewport(0, 0, window_width, window_height);

    glRotatef(rot, 0,1,0);

//    axes();
//    wall();
//    robot();
buiding();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(window_width,window_height);
    glutInitWindowPosition(300,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Maze");

     LoadTexture("C:\\Users\\Shimul\\Documents\\CSE 4208 Computer Graphics\\graphics\\maze\\images\\building1.bmp",1);
      LoadTexture("C:\\Users\\Shimul\\Documents\\CSE 4208 Computer Graphics\\graphics\\maze\\images\\building2.bmp",2);
       LoadTexture("C:\\Users\\Shimul\\Documents\\CSE 4208 Computer Graphics\\graphics\\maze\\images\\road.bmp",3);
     //LoadTexture("C:\\Users\\Admin\\Desktop\\nipa\\project\\maze\\images\\building2.bmp",2);
     //LoadTexture("C:\\Users\\Admin\\Desktop\\nipa\\project\\maze\\images\\road.bmp",3);


    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    _light();
    glShadeModel( GL_SMOOTH );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glutMainLoop();

}
