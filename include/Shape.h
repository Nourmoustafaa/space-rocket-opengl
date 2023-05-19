#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <unordered_map>
#include <utility>

/**
 * @brief A class representing a shape with a set of vertices and a color.
 */
class Shape
{
    private:
        std::vector<std::pair<float,float>> vertices_; /**< The vertices of the shape. */
        std::unordered_map<char,float> color_; /**< The color of the shape. */
        std::vector<std::pair<float,float>> initValues_;

    public:
        /**
         * @brief Default constructor for Shape.
         *
         * Initializes the color of the shape to white.
         */
        Shape(){
            this->color_ = {
                {'r',1 },
                {'g',1 },
                {'b',1 },
            };
        }

        /**
         * @brief Constructor for Shape.
         *
         * @param vertics The vertices of the shape.
         * @param color The color of the shape.
         */
        Shape(std::vector<std::pair<float,float>> vertices, std::unordered_map<char,float> color){
            this->vertices_ = vertices;
            this->initValues_ = vertices_;
            this->color_ = color;
        }

        /**
         * @brief Sets the vertices of the shape.
         *
         * @param vertices The vertices of the shape.
         */
        void setVertices(std::vector<std::pair<float,float>> vertices){
            this->vertices_ = vertices;
            this->initValues_ = this->vertices_;
        }

        /**
         * @brief Returns the vertices of the shape.
         *
         * @return The vertices of the shape.
         */
        std::vector<std::pair<float,float>> getVertices(){
            return this->vertices_;
        }

        /**
         * @brief Sets the color of the shape.
         *
         * @param color The color of the shape.
         */
        void setColor(std::unordered_map<char,float> color){
            this->color_ = color;
        }

        /**
         * @brief Returns the color of the shape.
         *
         * @return The color of the shape.
         */
        std::unordered_map<char,float> getColor (){
            return this->color_;
        }

        /**
         * @brief Moves the shape by a given offset.
         *
         * @param x The horizontal offset.
         * @param y The vertical offset.
         */
        void moveShape(float newX, float newY) {
            int i = 0;
            for (auto & vertex : vertices_){
                    vertex.first = newX + initValues_[i].first; // x coordinate = x-coordinate + mouseX
                    vertex.second = newY + initValues_[i].second; // y coordinate = y-coordinate + mouseY
                    std::cout<<vertex.first<<"+"<<newX<<"="<<vertex.first+newX<<std::endl;
                    ++i;
            }

        }
};

#endif // SHAPE_H
