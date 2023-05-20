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
#include <string>
#include <sstream>
using namespace std;
int phyWidth= 500;
int phyHeight= 500;
int logWidth=100;
int logHeight=100;
int limit = 110;
float mouseX;
float randX=20;
int score = 0;
bool isCollided = false;
float mouseY;
Rocket rocket;
Circle asteroid;
CircleViewer asteroidViewer(asteroid);
RocketViewer rocketViewer(rocket);
float rRandom = asteroid.getColor()['r'];
float gRandom = asteroid.getColor()['g'];
float bRandom = asteroid.getColor()['b'];
int currentRandomAsteroidColorChanel = 0;
vector <float> currentLaserBeamColor = {
    rocket.getLaserBeam().getColor()['r'],
    rocket.getLaserBeam().getColor()['g'],
    rocket.getLaserBeam().getColor()['b']
};
vector <float> currentAsteroidRandomColor = {1, 0, 0};
int currentIndex = 0;
void Timer(int value){
    glutTimerFunc(50, Timer, value);
    glutPostRedisplay();
}
void Text(string str, int x, int y) {
    glColor3f(1, 1, 1);
    glRasterPos2d(x, y);
    for (auto c : str)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glFlush();
}
void generateRandomStars(int xRange,int yRange, int pointSize, int intensity) {
         glColor3f(1, 1, 1);
         default_random_engine generator;
         uniform_int_distribution <int>distributionX(0, 100);
         uniform_int_distribution <int>distributionY(0, 100);
         glPointSize(pointSize); // Set the point size
         for (int i = 0; i < intensity; i++) {
             int randomX = distributionX(generator);
             int randomY = distributionY(generator);
             glBegin(GL_POINTS);
             glVertex2f(randomX,randomY);
             glEnd();
         }
}
double generateRandomZeroToOne() {
    return static_cast<double>(std::rand()) / RAND_MAX;
}
void checkCollision(){
    float asteroidLeftBound = asteroid.getVertices()[0].first-asteroid.getRadius();
    float asteroidRightBound = asteroid.getVertices()[0].first+asteroid.getRadius();
    vector<pair<float,float>> laserBeamVertices = rocketViewer.getRocket().getLaserBeam().getVertices();
    // cout<<"laser: "<<rocketViewer.getRocket().getLaserBeam().getVertices()[0].first;
    bool sameColor = rocketViewer.getLaserBeam().getColor()['r'] == asteroid.getColor()['r'];
    if(laserBeamVertices[0].first > asteroidLeftBound && laserBeamVertices[1].first < asteroidRightBound && !isCollided && sameColor){
        //rocketViewer.changeBeamColor(asteroid.getColor());
        isCollided = true;
        score++;
    }
}
vector <float> randomRGB(){
         static default_random_engine generator;
         static uniform_int_distribution <int>distribution(0, 2);
         int randomChannelIndex = distribution(generator);
         cout<<"Chosen index: "<<randomChannelIndex;
         vector<float> color(3,0);
         color[randomChannelIndex] = 1;
        return color;
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    generateRandomStars(0,100,.5,100);
    stringstream ss;
    ss<<score;
    string s;
    ss>>s;
    Text("Score: " +s, 5, 90);
    rocketViewer.draw();
    // drawCircle(randX, limit, 5, 100);
    vector<pair<float,float>> center = {make_pair(randX,limit)};
    asteroid.setVertices(center);
    checkCollision();
    unordered_map <char, float> color = {
        {'r', rRandom},{'g', gRandom},{'b', bRandom}
    };
    unordered_map <char,float> asteroidColor = {
    {'r',currentAsteroidRandomColor[0]},
    {'g',currentAsteroidRandomColor[1]},
    {'b',currentAsteroidRandomColor[2]},
    };
    //cout<<"Color is"<<endl;
    //for(auto channel : currentAsteroidRandomColor){
        //cout<<channel<<" ";
    //}
    asteroid.setColor(asteroidColor);
    checkCollision();
    // cout<<asteroid.getColor()['r'];
    asteroidViewer.setCircle(asteroid);
    asteroidViewer.draw();
    --limit;
    if(limit <=-6){
        limit = 110;
        randX = 20 + rand()%90;
        // rRandom = generateRandomZeroToOne();
        // gRandom = generateRandomZeroToOne();
        // bRandom = generateRandomZeroToOne();
        currentAsteroidRandomColor = randomRGB();
        isCollided = false;
    }
    glutSwapBuffers();
}
void keyboardHandler(unsigned char key, int x, int y){
    if(key == ' '){
        currentIndex++;
        currentIndex = currentIndex % 3;
        for (auto & c : currentLaserBeamColor){
            c = 0;
        }
        currentLaserBeamColor[currentIndex] = 1;
        for (auto c : currentLaserBeamColor){
            cout<<c<<endl;
        }
        cout<<"Current index: "<<currentIndex<<endl;
        rocketViewer.changeBeamColor(currentLaserBeamColor[0], currentLaserBeamColor[1], currentLaserBeamColor[2]);
    }

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
