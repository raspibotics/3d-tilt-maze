#include "Camera.h"
#include "Vector3.h"
#include "Vector2.h"

Camera::Camera() : _position({0,0,0}) {}
Camera::Camera(Vector3 position) : _position(position) {}

void Camera::setPosition(Vector3 position) { _position = position; }
Vector3 Camera::getPosition() { return _position; }

// 3D renderer
void Camera::renderObject3D(std::vector<Vector3> vertices) {
    // Loop through vertices
    for (Vector3 vertex : vertices) {
        // Project points into 2D - orthographic projection 
        Vector2 point = {vertex.x, vertex.z};
    }
}