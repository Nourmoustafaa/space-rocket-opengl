#ifndef SHAPEVIEWER_H
#define SHAPEVIEWER_H
#include <Triangle.h>
#include <Circle.h>
#include <Quad.h>
#include <GL/glut.h>

class ShapeViewer
{
    private:
    public:
        virtual void draw() = 0;
    protected:

};

#endif // SHAPEVIEWER_H
