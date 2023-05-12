#ifndef QUAD_H
#define QUAD_H

#include "Shape.h"
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

/**
 * @brief The Quad class represents a four-sided polygon with straight sides.
 *
 * This class inherits from the Shape class and adds functionality specific to quadrilaterals.
 * A quad can be initialized with its vertices and color, or it can be initialized with a default set of vertices.
 *
 */
class Quad: public Shape
{
    public:
        /**
         * @brief Default constructor that initializes the quad with default vertices.
         *
         * The default vertices form a square with side length of 10 units and the bottom left corner at the origin.
         *
         */
        Quad(): Shape(){
            vector <pair<float,float>> quadVertices = { make_pair(0,0), make_pair(10,0), make_pair(10,10), make_pair(0,10) };
            setVertices(quadVertices);
        }

        /**
         * @brief Constructor that initializes the quad with specified vertices and color.
         *
         * @param vertices A vector of pairs of floats representing the vertices of the quad.
         * @param color An unordered map that stores the RGB color values of the quad as floats.
         *
         */
        Quad(vector<pair<float,float>> vertices, unordered_map<char,float> color): Shape(vertices, color){
        }


};

#endif // QUAD_H
