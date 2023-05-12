#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;
    class Triangle: public Shape
    {
        public:
            Triangle(): Shape(){
                vector<pair<float,float>> triangleVertices = {
                    make_pair(0,0),
                    make_pair(10,0),
                    make_pair(5,5)
                };
                setVertices(triangleVertices);
            }
            Triangle(vector<pair<float,float>> vertices, unordered_map<char,float> color): Shape(vertices, color){
            }
        private:
    };

    #endif // TRIANGLE_H
