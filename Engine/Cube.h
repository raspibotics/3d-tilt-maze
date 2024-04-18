#ifndef CUBE_H
#define CUBE_H

#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Camera.h"

class Cube {

    private:
        Vector3 _position;
        int width;
        int height; 
        int length; 

    public:
        // Constructor for unit cube
        Cube();

        Cube(Vector3 position, int width, int height, int length);
};


#endif