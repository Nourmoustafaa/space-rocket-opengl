#ifndef QUADVIEWER_H
#define QUADVIEWER_H

#include "Quad.h"
#include <GL/glut.h>
using namespace std;
class QuadViewer
{
private:
    Quad quad_;

public:
    QuadViewer() : quad_() {}
    QuadViewer(Quad quad) : quad_(quad){}

    void draw()
    {
        unordered_map<char, float> color = this->quad_.getColor();
        glColor3f(color['r'], color['g'], color['b']);
        glBegin(GL_QUADS);
        for (auto v : this->quad_.getVertices()) {
            glVertex2f(v.first, v.second);
        }
        glEnd();
    }
};

#endif // QUADVIEWER_H
