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
#include "view/CircleViewer.h"
#include <random>
#include <unordered_set>
#include <cstdlib>
using namespace std;
int phyWidth= 1000;
int phyHeight= 1000;
int logWidth=100;
int logHeight=100;
int limit = 110;
float mouseX;
float randX=20;
float mouseY;
Rocket rocket;
Circle asteroid;
CircleViewer asteroidViewer(asteroid);
RocketViewer rocketViewer;
float rRandom = asteroid.getColor()['r'];
float gRandom = asteroid.getColor()['g'];
float bRandom = asteroid.getColor()['b'];
void Timer(int value){
    glutTimerFunc(15, Timer, value);
    glutPostRedisplay();
}
void Text(string str, int x, int y) {
    glColor3f(1, 1, 1);
    glRasterPos2d(x, y);
    for (auto c : str)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glFlush();
}
double generateRandomZeroToOne() {
    return static_cast<double>(std::rand()) / RAND_MAX;
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    Text("Score: ", 5, 90);
    rocketViewer.draw();
    // drawCircle(randX, limit, 5, 100);
    vector<pair<float,float>> center = {make_pair(randX,limit)};
    asteroid.setVertices(center);
    unordered_map <char, float> color = {
        {'r', rRandom},{'g', gRandom},{'b', bRandom}
    };
    asteroid.setColor(color);
    // cout<<asteroid.getColor()['r'];
    asteroidViewer.setCircle(asteroid);
    asteroidViewer.draw();
    --limit;
    if(limit <=-6){
        limit = 110;
        randX = 20 + rand()%90;
        rRandom = generateRandomZeroToOne();
        gRandom = generateRandomZeroToOne();
        bRandom = generateRandomZeroToOne();
    }
    glutSwapBuffers();
}
void keyboardHandler(unsigned char key, int x, int y){

}

void mouseHandler(int x, int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    mouseY = phyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyHeight;
    rocketViewer.moveRocket(mouseX, mouseY);
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
    Timer(0);
    glutMainLoop();
    return EXIT_SUCCESS;
}
