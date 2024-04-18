#include "Camera.h"
#include "Vector2.h"
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
        projected_points.push_back({vertex.x, vertex.z});
    }
    // Remove duplicate vertices for efficiency - TODO will need to overload comparison operators for Vectors first

    return projected_points;
}