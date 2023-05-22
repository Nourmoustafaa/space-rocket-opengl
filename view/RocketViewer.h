#ifndef ROCKETVIEWER_H
#define ROCKETVIEWER_H

#include "Triangle.h"
#include "Circle.h"
#include "Quad.h"
#include "Rocket.h"
#include "TriangleViewer.h"
#include "CircleViewer.h"
#include "QuadViewer.h"
#include <GL/glut.h>

/**
 * @brief A class responsible for drawing a Rocket using OpenGL
 */
class RocketViewer
{
    private:
        Rocket rocket_; ///< The Rocket to be drawn

    public:
        /**
         * @brief Default constructor for RocketViewer
         */
        RocketViewer(): rocket_(){}
        RocketViewer(Rocket rocket): rocket_(rocket) {}

        /**
         * @brief Draws the Rocket using OpenGL
         */
        void draw(){
          TriangleViewer nozzleViewer(rocket_.getNozzle());
          nozzleViewer.draw();
          QuadViewer laserBeamViewer(rocket_.getLaserBeam());
          laserBeamViewer.draw();
            unordered_map<char,float> color2 = {
            {'r',0},{'g',1},{'b',1}
            };
          //cout<<"laser beam viewer"<<laserBeamViewer.getQuad().getColor()['r'];
          TriangleViewer coneView(rocket_.getCone());
          coneView.draw();
          QuadViewer bodyView(rocket_.getBody());
          bodyView.draw();
        }
        void moveRocket(float x, float y){
            this->rocket_.moveRocket(x, y);
            //cout<<"rocket viewer; "<<this->rocket_.getLaserBeam().getVertices()[0].first;

        }
        void changeBeamColor(float r, float g, float b){
            unordered_map<char,float> color = {
            {'r',r},{'g',g},{'b',b}
            };
            cout<<"====== Previous ROCKET VIEWER COLOR IS ======"<<this->rocket_.getLaserBeam().getColor()['r']<<endl;
            this->rocket_.changeLaserBeamColor(color);
            cout<<"CURRENT COLOR ISSSSSSSSSSSS"<<color['r']<<endl;
            cout<<"====== ROCKET VIEWER COLOR IS ======"<<this->rocket_.getLaserBeam().getColor()['r'];
        }
        Rocket getRocket(){
            return this->rocket_;
        }
        Quad getLaserBeam(){
            return this->rocket_.getLaserBeam();
        }

    protected:

};

#endif // ROCKETVIEWER_H
