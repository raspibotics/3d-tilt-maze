#ifndef CUBE_H
#define CUBE_H

#include "EngineUtils.h"
#include "N5110.h"
#include "Camera.h"
#include <vector>

class Cube {

    private:
        Vector3 _position; // Centre of the cube 

        // Dimensions of the cube 
        float _width;
        float _depth;
        float _height;  

        // Basically wether to render cube or not, should probs call destructor but would need to restructure game loop
        bool _destroyed = false;

        std::vector<Vector3> _bottomFace = {{_position.x-_width/2,_position.y-_height/2, _position.z-_depth/2}, 
        {_position.x-_width/2,_position.y-_height/2,_position.z+_depth/2}, 
        {_position.x+_width/2,_position.y-_height/2, _position.z+_depth/2}, 
        {_position.x+_width/2,_position.y-_height/2,_position.z-_depth/2}};

        // Points of top face of cube with respect to _position which is treated as the centroid point
        std::vector<Vector3> _topFace = {{_position.x-_width/2, _position.y+_height/2, _position.z-_depth/2}, 
        {_position.x-_width/2, _position.y+_height/2, _position.z+_depth/2}, 
        {_position.x+_width/2, _position.y+_height/2, _position.z+_depth/2}, 
        {_position.x+_width/2, _position.y+_height/2,  _position.z-_depth/2}};

    public:
        // Constructor for unit cube
        Cube();

        Cube(Vector3 position, float width, float depth, float height);

        void updateFaces();

        Vector3 getPosition();
        void setPosition(Vector3 newPositionXYZ);
        bool isDestroyed();
        void destroyCube(bool destroyed); 

        void setWidthDepthHeight(float width, float height, float depth);

        // TODO - probs can pass by reference here
        void drawCube(Camera &camera, N5110 &screen);

        void translateCube(Vector3 translationVector);
        void rotateCube(float theta, Vector3 axis);
};


#endif