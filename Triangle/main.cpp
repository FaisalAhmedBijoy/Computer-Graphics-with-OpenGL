#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int windowWidth=500;
int windowHeight=500;
double Txval=0;
double Tyval=0;
bool flagScale=true;
double sval=0;


void triangle()
{
    glBegin(GL_TRIANGLES); //Primitive Declaration
    glColor3f(1.0,1.0,1.0); //RGB
    glVertex2f(2.0,2.0); // Coordinates

    glColor3f(0.0,1.0,0.0);
    glVertex2f(2.0,0.0);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.0,0.0);

    glEnd(); // Primitive End

}

void display()
{
    // Clear the buffers
    /*
    Color buffer
    stores the color of each pixel of the projected scene. And depth buffer
    stores the depth information of each pixel for multiple overlapping
    objects. Both needs to cleared before creating new scene.
    */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    /*
    glMatrixMode() - This function determines which matrix stack
    (GL_MODELVIEW, GL_PROJECTION, or GL_TEXTURE) is used for matrix operations.
    GL_MODELVIEW Matrix operations affect the modelview matrix stack. (Used to move objects
    around the scene.)
    GL_PROJECTION Matrix operations affect the projection matrix stack. (Used to define clipping
    volume.)
    GL_TEXTURE Matrix operations affect the texture matrix stack. (Manipulates texture
    coordinates.)

    Every operations of each category are
    stored by multiplying the current operation matrix with the stored
    matrix.
    */
    glMatrixMode(GL_PROJECTION);
    /*
     glMatrixMode()function selects the required matrix stack and then
    glLoadIdentity()function replaces the current transformation
    matrix with the identity matrix of the stack.
    */
    glLoadIdentity();
    /*
    The projection matrix stack is used store the clipping volume defined
    by gluOrtho2D(-3, 3, -3, 3) function. Therefore


    gluOrtho2D(Xmin, Xmax, Ymin, Ymax) defines a rectangular
    clipping volume from world space specifies by the parameters Xmin,
    Xmax and Ymin, Ymax.
    */
    gluOrtho2D(-3,3,-3,3);
    /*
    glMatrixMode(GL_MODELVIEW); and glLoadIdentity();
    are also used to select the modelview matrix stack and replace the
    current matrix with the identity matrix.
    creating an object and applying transformations on that object must have to be done
    after selecting the modelview matrix stack.
    */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*
    glViewport(0, 0 ,windowWidth ,windowHeight) - sets
    the region within a window that is used for mapping the clipping
    volume coordinates to physical window coordinates. First two
    parameters are the x and y coordinate values of the lower left corner
    of the window and the last two are the width and height of that
    window, must be less than or equal to the original window width and
    height
    */
    glViewport(0,0,windowWidth,windowHeight);
    /*
    1. glTranslatef(Xval,Yval,Zval) – this function forms a
    translation matrix that translate (simply adds) the current
    object’s x, y, z coordinate values by Xval, Yval, Zval
    respectively. This matrix is multiplied with modelview matrix
    stored in modelview matrix stack.

    2. glScalef(Xval,Yval,Zval) – this function forms a scale
    matrix that scale (simply multiply) the current object’s x, y, z
    coordinate values by Xval, Yval, Zval respectively. This matrix
    is multiplied with modelview matrix stored in modelview matrix
    stack.

    3. glRotatef(theta,Xval,Yval,Zval) – this function forms
    a rotation matrix that rotate the current object’s x, y, z coordinate
    values by theta degree in anti-clockwise direction with respect to
    vector formed by Xval, Yval, Zval and centered at origin. This
    matrix is multiplied with modelview matrix stored in modelview
    matrix stack.
    */

    /*
    Suppose, we want to translate the triangle 1unit in right and 1unit
    down to its current position
    */

    //glTranslatef(1,-1,0);
    //glTranslatef(-1,1,0);

    //glRotatef(45,0,0,1);
    /*
    This will translate the triangle first and then rotate 45 degree anti clockwise with respect to Z axis.
    Remember, the order of placing the transformation function is
    important. Because, the output of first translation, then rotation is not
    the same for the output of first rotation, then translation
    */
    //triangle();
    /*
    glFlush()is used to ensure the drawing commands are
    actually executed rather than stored in a buffer waiting additional
    OpenGL commands.
    */

    /*
    glPushMatrix() - pushes the current matrix onto the current matrix
    stack. This function is most often used to save the current
    transformation matrix so that it can be restored later with a call to
    glPopMatrix().
    glPopMatrix() - Pops the current matrix off the matrix stack.
    */
    glPushMatrix();

    glTranslatef(-2,-1,0);
    glRotatef(45,0,0,1);
    triangle();

    glPopMatrix();


    glPushMatrix();
    //glRotatef(45,0,0,1);
    glTranslatef(Txval,Tyval,0);
    triangle();
    glPopMatrix();

    glPushMatrix();
    //glViewport(400, 300 ,400 ,300);
    glScalef(sval,sval,1);
    triangle();
    glPopMatrix();


    glFlush();
    /*
    glutSwapBuffers()performs a buffer swap on the layer in use for
    the current window. Specifically, glutSwapBuffers promotes the
    contents of the BACK BUFFER of the layer in use of the current
    window to become the contents of the FRONT BUFFER. The contents
    of the back buffer then become undefined. The update typically takes
    place during the vertical retrace of the monitor, rather than
    immediately after glutSwapBuffers is called.
    */
    glutSwapBuffers();

}
/*
the purpose of keyboard function is to listen a key press and perform
an action with respect to that key press. It needs to define a user
defined function, where we define the actions for a specific key press.
Say, we want to translate the first triangle left, right, up and down
using key L, R, U and D respectively.
*/
void myKeyboardFunc( unsigned char key, int x, int
                     y )
{
    switch ( key )
    {
    case 'r':
        Txval+=0.2;
        break;
    case 'l':
        Txval-=0.2;
        break;
    case 'u':
        Tyval+=0.2;
        break;
    case 'd':
        Tyval-=0.2;
        break;
    case 'a':
        flagScale=true;
        break;
    case 's':
        flagScale=false;
        break;
    case 27: // Escape key
        exit(1);
    }
    /*
     glutPostRedisplay().
    This function informs the GLUT library that the current window needs
    to be refreshed. Multiple calls to this function before the next refresh
    result in only one repainting of the window. Therefore, without this
    function you cannot see the keyboard actions
    */
    glutPostRedisplay();
}

void animate()
{
    if (flagScale == true)
    {
        sval+=0.005;
        if (sval>3)
        {
            sval=0.005;
        }
    }
    glutPostRedisplay();
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv); // glutInit(&argc, argv) - This initializes the GLUT library
    /*
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |
    GLUT_DEPTH) - Initial parameters for the display. In this case, we are
    specifying a RGB display (GLUT_RGB) along with double-buffering
    (GLUT_DOUBLE), so the screen won't flicker when we redraw it.
    GLUT_DEPTH specifies a 32-bit depth buffer
    */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100,100); // Start with upper left corner
    glutInitWindowSize(windowWidth,windowHeight); // initial window size
    glutCreateWindow("Triangle");

    /*
    glShadeModel( GL_SMOOTH ) - Sets the default shading to flat or
    smooth. OpenGL primitives are always shaded, but the shading model
    can be flat (GL_FLAT) or smooth (GL_SMOOTH).
    */

    glShadeModel(GL_SMOOTH);
    /*
    glEnable( GL_DEPTH_TEST ) - glEnable enables an OpenGL
    drawing feature. Here it enables the depth test features for depth
    buffer
    */
    glEnable(GL_DEPTH_TEST);
    /*
    glutDisplayFunc(display) - This function tells GLUT which
    function to call whenever the windows contents must be drawn. This
    can occur when the window is resized or uncovered or when GLUT is
    specifically asked to refresh with a call to the glutPostRedisplay
    function
    */
    glutDisplayFunc(display);
    // Sets the keyboard callback function for the current window
    glutKeyboardFunc(myKeyboardFunc);
    // animation
    glutIdleFunc(animate);
    /*
    glutMainLoop() - This function begins the main GLUT event handling loop. The event loop is the place where all keyboard, mouse,
    timer, redraw, and other window messages are handled. This function
    does not return until program termination.
    */
    glutMainLoop();
    return 0;
}
/*
Now, we want to display the same triangle twice. Very simple, call the
triangle() function again just after the first one. But in output you
will see only one triangle (same as previous output). Why?
Actually the second triangle is also drawn along with first one and they
completely overlapped. But why they overlap? We did not apply any
transformations for the second triangle.
Remember, all the transformations defined before the object will
affect the object (mentioned above).
But, we don’t want to apply the transformations on the second triangle.
What could be the solution? You can push the transformation matrices
along with first triangle in the modelview matrix stack and pop the
matrix when to display using glPushMatrix() and glPopMatrix()

*/
