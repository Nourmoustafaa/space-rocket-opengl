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

    void draw() override {
        float cx = this->circle_.getVertices()[0].first;
        float cy = this->circle_.getVertices()[0].second;
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < this->circle_.getSegments(); i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(this->circle_.getSegments());
            float x = this->circle_.getRadius() * cosf(theta);
            float y = this->circle_.getRadius() * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
    }
};

#endif
