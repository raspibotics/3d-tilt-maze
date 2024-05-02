#include "Camera.h"
#include "EngineUtils.h"
#include <vector>

Camera::Camera() : _position({0,0,0}) {}
Camera::Camera(Vector3 position) : _position(position) {}

void Camera::setPosition(Vector3 position) { _position = position; }
Vector3 Camera::getPosition() { return _position; }


// Projection (orthographic) function for single point
Point2D Camera::Vector3ToPoint2D(Vector3 vertex) {
    return {static_cast<int>(vertex.x), static_cast<int>(vertex.z)};
}

// TODO - Adapt this to project onto a specific plane, will need later for maze
std::vector<Point2D> Camera::projectObjectToPlane(std::vector<Vector3> vertices) {
    std::vector<Point2D> projected_points = {};
    // Loop through vertices
    for (Vector3 vertex : vertices) {
        // Project points into 2D - orthographic projection and handle type conversion 
        projected_points.push_back({static_cast<int>(vertex.x), static_cast<int>(vertex.z)});
    }
    return projected_points;
}