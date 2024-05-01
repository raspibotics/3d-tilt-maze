#ifndef CUBE_H
#define CUBE_H

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

        // Vertices of the cube with respect to the upper-leftmost corner vertex [TESTING]
        //std::vector<Vector3> _bottomFace = {{0,0,0}, {0,0,_depth}, {_width,0,_depth}, {_width,0,0}};
        //std::vector<Vector3> _topFace = {{0,_height,0}, {0,_height,_depth}, {_width,_height,_depth}, {_width,_height,0}};

        // Vertices of bottom face of cube with respect to _position which is treated as the centroid point
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

        // TODO - probs can pass by reference here
        void drawCube(Camera &camera, N5110 &screen);

        void translateCube(Vector3 translationVector);
        void rotateCube(float theta, Vector3 axis);
};


#endif