/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include "Triangle.h"
#include "Circle.h"
#include "Quad.h"
#include "Rocket.h"
#include "view/TriangleViewer.h"
#include "view/RocketViewer.h"
using namespace std;
int phyWidth= 1000;
int phyHeight= 1000;
int logWidth=100;
int logHeight=100;
float mouseX;
float mouseY;
Triangle cone;
TriangleViewer coneView(cone);
Rocket rocket;
RocketViewer rocketViewer;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    rocketViewer.draw();
    glutSwapBuffers();
}
void keyboardHandler(unsigned char key, int x, int y){

}

void mouseHandler(int x, int y){
    mouseX = x;
    cout<<"x is"<<x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    mouseY = phyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
    cout<<"x: "<<mouseX<<endl;
    cout<<mouseY<<endl;
    rocketViewer.moveRocket(mouseX, mouseY);
        cout<<"fff:";
    cout<<rocketViewer.getRocket().getBody().getVertices()[0].first<<endl;
    glutPostRedisplay();
}

void init()
{
glClearColor( 0.0, 0.0, 0, 1.0); // COLOR
glMatrixMode(GL_PROJECTION);
gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth,phyHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutPassiveMotionFunc(mouseHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
