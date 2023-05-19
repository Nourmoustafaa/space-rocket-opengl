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
        Triangle nozzle_;
        Quad laserbeam_;

    public:
        /**
            @brief Constructs a new Rocket object with default cone, body, nozzle
        */
        Rocket(){
            ///Initializes nozzle vertices
            vector<pair<float,float>> nozzleVertices = {
            make_pair(-2,3.5), make_pair(7,3.5), make_pair(2.5,10)
            };
            this->nozzle_.setVertices(nozzleVertices);

            ///Initializes body vertices
            vector<pair<float,float>> bodyVertices = {
            make_pair(0,3),make_pair(5,3),make_pair(5,10),make_pair(0,10)
            };
            this->body_.setVertices(bodyVertices);

            /// Initializes the cone vertices
            vector<pair<float,float>> coneVertices = {
            make_pair(0,10),make_pair(5,10),make_pair(2.5,13)
            };
            this->cone_.setVertices(coneVertices);

            vector <pair<float,float>> beamVertices = {
            make_pair(1, 10), make_pair(4, 10), make_pair(4,100), make_pair(1,100)
            };
            this->laserbeam_.setVertices(beamVertices);
            unordered_map <char,float> laserColor = {
                {'r',1}, {'g',0}, {'b',0}
            };
            this->laserbeam_.setColor(laserColor);

        }
        /**
            * @brief Constructs a new Rocket object with the specified cone, body, and nozzle.
            * @param cone The cone of the rocket.
            * @param body The body of the rocket.
            * @param nozzle The nozzle of the rocket.
        */
        Rocket(Triangle cone, Quad body, Triangle nozzle) : cone_(cone), body_(body), nozzle_(nozzle){

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
        Triangle getNozzle(){
            return this->nozzle_;
        }
        /**
            * @brief Gets the laser beam of the rocket.
            * @return The beam of the rocket.
        */
        Quad getLaserBeam(){
            return this->laserbeam_;
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
            this->cone_.moveShape(x,y);
            this->body_.moveShape(x,y);
            this->laserbeam_.moveShape(x,y);
            this->nozzle_.moveShape(x, y);
        }

};

#endif // ROCKET_H
