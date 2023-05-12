#ifndef TRIANGLEVIEWER_H
#define TRIANGLEVIEWER_H
#include "Triangle.h"
#include "Circle.h"
#include "Quad.h"
#include "ShapeViewer.h"
#include <GL/glut.h>
class TriangleViewer: public ShapeViewer
{
    private:
        Triangle triangle_;
    public:
        TriangleViewer(): triangle_(){}
        TriangleViewer(Triangle triangle): triangle_(triangle){}
        void draw () override{
           unordered_map<char,float> color = this->triangle_.getColor();
           vector <pair<float,float>> vertices = this->triangle_.getVertices();
           glColor3f(color['r'],color['g'],color['b']);
           glColor3f(.1,.3,.5);
           glBegin(GL_TRIANGLES);
           for (auto v : vertices){
            glVertex2f(v.first, v.second);
           }
           glEnd();
        }
    protected:

};

#endif
