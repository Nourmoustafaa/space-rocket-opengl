#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
    class Circle: public Shape
    {
        private:
            float radius_;
            float segments_;
        public:
            Circle(): Shape(), radius_(5), segments_(100){
                vector<pair<float,float>> circleCenter = {make_pair(50,50)};
                setVertices(circleCenter);
            }
            Circle(vector<pair<float,float>> vertices, unordered_map<char,float> color, float radius, float segments): Shape(vertices, color), radius_(radius), segments_(segments){
            }
        float getSegments(){
        return this->segments_;
        }
        float getRadius(){
        return this->getRadius();
        }
        void setSegments(float segments){
        this->segments_ = segments;
        }
        void setRadius(float radius){
            this->radius_ = radius;
        }
    };

    #endif // CIRCLE_H
