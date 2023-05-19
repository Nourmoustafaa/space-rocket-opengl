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
using namespace std;
int phyWidth= 1000;
int phyHeight= 1000;
int logWidth=100;
int logHeight=100;
int limit = 110;
float mouseX;
float randX;
float mouseY;
Triangle cone;
TriangleViewer coneView(cone);
Rocket rocket;
RocketViewer rocketViewer;
std::unordered_set<int> generatedCoordinates;
std::vector<float> obstaclePositions;  // Stores the Y positions of the obstacles
int generateUniqueRandomCoordinates(float& x) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(20, 90);
    x = distribution(generator);
    cout << "randomX" << x << endl;
    return x;
}
void generateObstacles() {
    generatedCoordinates.clear();
    obstaclePositions.clear();

    for (int i = 0; i < 7; i++) {
        float randomX;
        int randomCoord = generateUniqueRandomCoordinates(randomX);
        generatedCoordinates.insert(randomCoord);
        obstaclePositions.push_back(limit - i);
    }
}


 void drawCircle(float cx, float cy, float radius, int segments) {
     glColor3f(.1,.3,.4);
        glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(segments);
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
}
void Timer(int value){
    glutTimerFunc(70, Timer, value);
glutPostRedisplay();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    rocketViewer.draw();
    for (size_t i = 0; i < obstaclePositions.size(); i++) {
        drawCircle(obstaclePositions[i], obstaclePositions[i], 5, 100);
        obstaclePositions[i]--;
        if (obstaclePositions[i] <= -6) {
            obstaclePositions[i] = 110;
        }
    }

    cout << "randomX is " << randX;

    int x, y;
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
    generateObstacles();
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
