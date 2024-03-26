#ifndef CAMERA_H
#define CAMERA_H


#include "Vector3.h"
#include <vector>

class Camera {
    
    private:
        Vector3 _position;

    public:
        Camera();
        Camera(Vector3 position);

        void setPosition(Vector3 position);
        Vector3 getPosition();

        void renderObject3D(std::vector<Vector3> vertices);

};


#endif