#ifndef ROCKET_H
#define ROCKET_H
#include "Quad.h"
#include <Triangle.h>
#include <iostream>
/**
    @brief A class representing the rocket which is composed of a:
    1. Cone.
    2. Body.
    3. Nozzle.
*/
class Rocket
{
    private:
        Triangle cone_;
        Quad body_;
        Quad nozzle_;

    public:
        /**
            @brief Constructs a new Rocket object with default cone, body, nozzle
        */
        Rocket(){
            ///Initializes nozzle vertices
            vector<pair<float,float>> nozzleVertices = {
            make_pair(5,5), make_pair(15,5), make_pair(12,10), make_pair(8,10)
            };
            this->nozzle_.setVertices(nozzleVertices);

            ///Initializes body vertices
            vector<pair<float,float>> bodyVertices = {
            make_pair(8,5),make_pair(12,5),make_pair(12,15),make_pair(8,15)
            };
            this->body_.setVertices(bodyVertices);

            /// Initializes the cone vertices
            vector<pair<float,float>> coneVertices = {
            make_pair(6,15),make_pair(14,15),make_pair(10,20)
            };
            this->cone_.setVertices(coneVertices);

        }
        /**
            * @brief Constructs a new Rocket object with the specified cone, body, and nozzle.
            * @param cone The cone of the rocket.
            * @param body The body of the rocket.
            * @param nozzle The nozzle of the rocket.
        */
        Rocket(Triangle cone, Quad body, Quad nozzle) : cone_(cone), body_(body), nozzle_(nozzle){

        }
        /**
            * @brief Gets the cone of the rocket.
            * @return The cone of the rocket.
        */
        Triangle getCone(){
            return this->cone_;
        }
        /**
            * @brief Gets the body of the rocket.
            * @return The body of the rocket.
        */
        Quad getBody(){
            return this->body_;
        }
        /**
            * @brief Gets the nozzle of the rocket.
            * @return The nozzle of the rocket.
        */
        Quad getNozzle(){
            return this->nozzle_;
        }

        /**
            * @brief Sets the cone of the rocket.
            * @param cone The new cone of the rocket.
        */
        void setCone(Triangle &cone){
            this->cone_=cone;
        }
        /**
            * @brief Moves the rocket by the specified amount in the x and y directions.
            * @param x The amount to move the rocket in the x direction.
            * @param y The amount to move the rocket in the y direction.
        */
        void moveRocket(float x, float y){
            float rectBottomLeftXNozzleBottomLeftX =  body_.getVertices()[0].first -  nozzle_.getVertices()[0].first;
            float coneBottomLeftXNozzleBottomLeftX = cone_.getVertices()[0].first - nozzle_.getVertices()[0].first;
            this->cone_.moveShape(x + coneBottomLeftXNozzleBottomLeftX, y + this->cone_.getVertices()[0].second - this->nozzle_.getVertices()[0].second);
            this->body_.moveShape(x+rectBottomLeftXNozzleBottomLeftX, y + this->body_.getVertices()[0].second - this->nozzle_.getVertices()[0].second);
            this->nozzle_.moveShape(x, y);
        }

};

#endif // ROCKET_H
