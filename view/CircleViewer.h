#ifndef CIRCLEVIEWER_H
#define CIRCLEVIEWER_H

#include "Circle.h"
#include <unordered_map>
#include <vector>
#include <utility>
#include "ShapeViewer.h"
#include <cmath>
using namespace std;
class CircleViewer : public ShapeViewer
{
private:
    Circle circle_;

public:
    CircleViewer() : circle_() {}
    CircleViewer(Circle circle): circle_(circle){}

    void draw() override {
        unordered_map<char,float> color = this->circle_.getColor();
        glColor3f(color['r'], color['g'], color['b']);
        float cx = this->circle_.getVertices()[0].first;
        float cy = this->circle_.getVertices()[0].second;
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(100);
            float x = 3 * cosf(theta);
            float y = 3 * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }

        glEnd();
    }
    Circle getCircle(){
        return this->circle_;
    }
    void setCircle(Circle circle){
        this->circle_ = circle;
    }
    void setVertices(vector<pair<float,float>> vertices){
        this->circle_.setVertices(vertices);
    }
};

#endif
