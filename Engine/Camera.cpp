#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include <vector>

Camera::Camera() : _position({0,0,0}) {}
Camera::Camera(Vector3 position) : _position(position) {}

void Camera::setPosition(Vector3 position) { _position = position; }
Vector3 Camera::getPosition() { return _position; }

// 3D renderer
std::vector<Vector2> Camera::projectObjectToPlane(std::vector<Vector3> vertices) {
    std::vector<Vector2> projected_points = {};
    // Loop through vertices
    for (Vector3 vertex : vertices) {
        // Project points into 2D - orthographic projection 
        projected_points.push_back({static_cast<int>(vertex.x), static_cast<int>(vertex.z)});
    }

    return projected_points;
}

// Iterate through points and rotate them 
std::vector<Vector3> Camera::rotateGameObject(std::vector<Vector3> gameObj, Vector3 axis, float theta){
    std::vector<Vector3> rotatedObj; 
    for (Vector3 vertex : gameObj) {
        rotatedObj.push_back(vertex.rotate(theta, axis));
    }
    return rotatedObj;
}