#ifndef CAMERA_H
#define CAMERA_H

#include "EngineUtils.h"
#include <vector>

class Camera {
    
    private:
        Vector3 _position;

    public:
        Camera();
        Camera(Vector3 position);

        void setPosition(Vector3 position);
        Vector3 getPosition();

        std::vector<Point2D> projectObjectToPlane(std::vector<Vector3> vertices);
        Point2D Vector3ToPoint2D(Vector3 vertex);
};


#endif