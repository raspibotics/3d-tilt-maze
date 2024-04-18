#ifndef CAMERA_H
#define CAMERA_H


#include "Vector3.h"
#include "Vector2.h"
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
        std::vector<Vector3> rotateGameObject(std::vector<Vector3> gameObj, Vector3 axis, float theta);
};


#endif