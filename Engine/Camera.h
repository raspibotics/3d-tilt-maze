#ifndef CAMERA_H
#define CAMERA_H

#include "EngineMath.h"
#include <vector>

class Camera {
    
    private:
        Vector3 _position;

    public:
        Camera();
        Camera(Vector3 position);

        void setPosition(Vector3 position);
        Vector3 getPosition();

        std::vector<Vector2> projectObjectToPlane(std::vector<Vector3> vertices);
};


#endif