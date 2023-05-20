/**
 * @file main.cpp
 *
 * @brief This program is a simple game implemented using OpenGL and GLUT.
 *        The objective of the game is to control a rocket and shoot down
 *        randomly appearing asteroids with a laser beam. The score increases
 *        with each successful collision.
 */

#include <GL/glut.h>
#include <iostream>
#include <random>
#include <unordered_map>
#include <string>
#include <sstream>
#include "Triangle.h"
#include "Circle.h"
#include "Quad.h"
#include "Rocket.h"
#include "view/TriangleViewer.h"
#include "view/RocketViewer.h"
#include "view/CircleViewer.h"

using namespace std;

int phyWidth = 500;                /**< Physical width of the window */
int phyHeight = 500;               /**< Physical height of the window */
int logWidth = 100;                /**< Logical width of the window */
int logHeight = 100;               /**< Logical height of the window */
int limit = 110;                   /**< Limit for asteroid appearance */
float mouseX;                      /**< Mouse X-coordinate */
float randX = 20;                  /**< Random X-coordinate for asteroid appearance */
int score = 0;                     /**< Game score */
bool isCollided = false;           /**< Flag to indicate collision */
float mouseY;                      /**< Mouse Y-coordinate */
Rocket rocket;                     /**< Rocket object */
Circle asteroid;                   /**< Asteroid object */
CircleViewer asteroidViewer(asteroid);   /**< Viewer for asteroid */
RocketViewer rocketViewer(rocket);       /**< Viewer for rocket */
float rRandom = asteroid.getColor()['r'];   /**< Random value for red channel of asteroid color */
float gRandom = asteroid.getColor()['g'];   /**< Random value for green channel of asteroid color */
float bRandom = asteroid.getColor()['b'];   /**< Random value for blue channel of asteroid color */
int currentRandomAsteroidColorChannel = 0;  /**< Current random channel index for asteroid color */
vector<float> currentLaserBeamColor = {
    rocket.getLaserBeam().getColor()['r'],   /**< Current color of the laser beam */
    rocket.getLaserBeam().getColor()['g'],
    rocket.getLaserBeam().getColor()['b']
};
vector<float> currentAsteroidRandomColor = {1, 0, 0};   /**< Current random color of the asteroid */
int currentIndex = 0;               /**< Current index for laser beam color selection */

/**
 * @brief Timer function to update the display
 *
 * @param value The timer value
 */
void Timer(int value);

/**
 * @brief Function to draw text on the screen
 *
 * @param str The text to be displayed
 * @param x The X-coordinate of the text position
 * @param y The Y-coordinate of the text position
 */
void Text(const string& str, int x, int y);

/**
 * @brief Function to generate random stars on the screen
 *
 * @param xRange The range of X-coordinates for the stars
 * @param yRange The range of Y-coordinates for the stars
 * @param pointSize The size of the stars
 * @param intensity The number of stars to generate
 */
void generateRandomStars(int xRange, int yRange, int pointSize, int intensity);

/**
 * @brief Function to generate a random number between 0 and 1
 *
 * @return The generated random number
 */
double generateRandomZeroToOne();

/**
 * @brief Function to check for collision between the rocket's laser beam and the asteroid
 */
void checkCollision();

/**
 * @brief Function to generate a random RGB color
 *
 * @return The generated random color as a vector of floats
 */
vector<float> randomRGB();

/**
 * @brief Display callback function
 *        Draws the game objects and updates their positions
 */
void display();

/**
 * @brief Keyboard callback function
 *        Handles keyboard events for changing the laser beam color
 *
 * @param key The pressed key
 * @param x The X-coordinate of the mouse
 * @param y The Y-coordinate of the mouse
 */
void keyboardHandler(unsigned char key, int x, int y);

/**
 * @brief Mouse callback function
 *        Handles mouse events for moving the rocket
 *
 * @param x The X-coordinate of the mouse
 * @param y The Y-coordinate of the mouse
 */
void mouseHandler(int x, int y);

/**
 * @brief Initialization function
 *        Sets up the OpenGL environment and configurations
 */
void init();

/**
 * @brief Main function
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 *
 * @return The exit status of the program
 */
int main(int argc, char* argv[]);

/**
 * @brief Timer function to update the display
 *
 * @param value The timer value
 */
void Timer(int value) {
    glutTimerFunc(50, Timer, value);
    glutPostRedisplay();
}

/**
 * @brief Function to draw text on the screen
 *
 * @param str The text to be displayed
 * @param x The X-coordinate of the text position
 * @param y The Y-coordinate of the text position
 */
void Text(const string& str, int x, int y) {
    glColor3f(1, 1, 1);
    glRasterPos2d(x, y);
    for (auto c : str)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glFlush();
}

/**
 * @brief Function to generate random stars on the screen
 *
 * @param xRange The range of X-coordinates for the stars
 * @param yRange The range of Y-coordinates for the stars
 * @param pointSize The size of the stars
 * @param intensity The number of stars to generate
 */
void generateRandomStars(int xRange, int yRange, int pointSize, int intensity) {
    glColor3f(1, 1, 1);
    default_random_engine generator;
    uniform_int_distribution<int> distributionX(0, 100);
    uniform_int_distribution<int> distributionY(0, 100);
    glPointSize(pointSize); // Set the point size
    for (int i = 0; i < intensity; i++) {
        int randomX = distributionX(generator);
        int randomY = distributionY(generator);
        glBegin(GL_POINTS);
        glVertex2f(randomX, randomY);
        glEnd();
    }
}

/**
 * @brief Function to generate a random number between 0 and 1
 *
 * @return The generated random number
 */
double generateRandomZeroToOne() {
    return static_cast<double>(std::rand()) / RAND_MAX;
}

/**
 * @brief Function to check for collision between the rocket's laser beam and the asteroid
 */
void checkCollision() {
    float asteroidLeftBound = asteroid.getVertices()[0].first - asteroid.getRadius();
    float asteroidRightBound = asteroid.getVertices()[0].first + asteroid.getRadius();
    vector<pair<float, float>> laserBeamVertices = rocketViewer.getRocket().getLaserBeam().getVertices();
    bool sameColor = rocketViewer.getRocket().getLaserBeam().getColor()['r'] == asteroid.getColor()['r'];
    if (laserBeamVertices[0].first > asteroidLeftBound && laserBeamVertices[1].first < asteroidRightBound && !isCollided && sameColor) {
        isCollided = true;
        score++;
    }
}

/**
 * @brief Function to generate a random RGB color
 *
 * @return The generated random color as a vector of floats
 */
vector<float> randomRGB() {
    static default_random_engine generator;
    static uniform_int_distribution<int> distribution(0, 2);
    int randomChannelIndex = distribution(generator);
    vector<float> color(3, 0);
    color[randomChannelIndex] = 1;
    return color;
}

/**
 * @brief Display callback function
 *        Draws the game objects and updates their positions
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    generateRandomStars(0, 100, .5, 100);
    stringstream ss;
    ss << score;
    string s;
    ss >> s;
    Text("Score: " + s, 5, 90);
    rocketViewer.draw();
    vector<pair<float, float>> center = {make_pair(randX, limit)};
    asteroid.setVertices(center);
    checkCollision();
    unordered_map<char, float> color = {
        {'r', rRandom}, {'g', gRandom}, {'b', bRandom}
    };
    unordered_map<char, float> asteroidColor = {
        {'r', currentAsteroidRandomColor[0]},
        {'g', currentAsteroidRandomColor[1]},
        {'b', currentAsteroidRandomColor[2]},
    };
    asteroid.setColor(asteroidColor);
    checkCollision();
    asteroidViewer.setCircle(asteroid);
    asteroidViewer.draw();
    --limit;
    if (limit <= -6) {
        limit = 110;
        randX = 20 + rand() % 90;
        currentAsteroidRandomColor = randomRGB();
        isCollided = false;
    }
    glutSwapBuffers();
}

/**
 * @brief Keyboard callback function
 *        Handles keyboard events for changing the laser beam color
 *
 * @param key The pressed key
 * @param x The X-coordinate of the mouse
 * @param y The Y-coordinate of the mouse
 */
void keyboardHandler(unsigned char key, int x, int y) {
    if (key == ' ') {
        currentIndex++;
        currentIndex = currentIndex % 3;
        for (auto& c : currentLaserBeamColor)
            c = 0;
        currentLaserBeamColor[currentIndex] = 1;
        rocketViewer.changeBeamColor(currentLaserBeamColor[0], currentLaserBeamColor[1], currentLaserBeamColor[2]);
    }
}

/**
 * @brief Mouse callback function
 *        Handles mouse events for moving the rocket
 *
 * @param x The X-coordinate of the mouse
 * @param y The Y-coordinate of the mouse
 */
void mouseHandler(int x, int y) {
    mouseX = x;
    mouseX = 0.5 + 1.0 * mouseX * logWidth / phyWidth;
    mouseY = phyHeight - y;
    mouseY = 0.5 + 1.0 * mouseY * logHeight / phyHeight;
    rocketViewer.moveRocket(mouseX, mouseY);
    glutPostRedisplay();
}

/**
 * @brief Initialization function
 *        Sets up the OpenGL environment and configurations
 */
void init() {
    glClearColor(0.0, 0.0, 0, 1.0);   // Set clear color to black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

/**
 * @brief Main function
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 *
 * @return The exit status of the program
 */
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(phyWidth, phyHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rocket Game");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutPassiveMotionFunc(mouseHandler);
    glutTimerFunc(50, Timer, 0);
    glutMainLoop();
    return 0;
}
