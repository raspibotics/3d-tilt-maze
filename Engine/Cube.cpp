#include "Cube.h"
#include "EngineUtils.h"
#include <vector>

// Create a unit cube
Cube::Cube() : _position(0,0,0), _width(1), _depth(1), _height(1) {}
// Custom constructor for cube/cuboid
Cube::Cube(Vector3 position, float width, float depth, float height) : _position(position), _width(width), _depth(depth), _height(height) {
    // Offset by position - Not really needed anymore (Legacy top corner positioning)
    /*for (size_t i = 0; i < _topFace.size(); i++) {
        _topFace[i] += _position;
        _bottomFace[i] += _position;
    } */
}

Vector3 Cube::getPosition() { return _position; }
void Cube::setPosition(Vector3 newPositionXYZ) {_position = newPositionXYZ; }

void Cube::drawCube(Camera &camera, N5110 &screen) {
    std::vector<Vector2> cubeBottomFacePoints = camera.projectObjectToPlane(_bottomFace);
    std::vector<Vector2> cubeTopFacePoints = camera.projectObjectToPlane(_topFace);
    // Draw the bottom face
     for (size_t i = 0; i < cubeBottomFacePoints.size(); i++) {
        // Draw bottom face
        Vector2 currentVertex = cubeBottomFacePoints[i];
        Vector2 nextVertex = cubeBottomFacePoints[(i + 1) % cubeBottomFacePoints.size()]; // Next vertex (wrap around for last vertex)
        screen.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);
     }
    // Draw the edges
    for (size_t i = 0; i < cubeBottomFacePoints.size(); i++) {
        Vector2 currentVertex = cubeBottomFacePoints[i];            
        Vector2 nextVertex = cubeTopFacePoints[i]; 
        screen.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1); 
    }
    // Draw the top face
    for (size_t i = 0; i < cubeTopFacePoints.size(); i++) {
        Vector2 currentVertex = cubeTopFacePoints[i];
        Vector2 nextVertex = cubeTopFacePoints[(i + 1) % cubeTopFacePoints.size()]; // Next vertex (wrap around for last vertex)
        screen.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);
    }

    // Draw the centre of the cube (Hitbox centre)
    Vector2 centroid_pos = camera.Vector3ToVector2(_position);
    screen.setPixel(centroid_pos.x, centroid_pos.y);
}

void Cube::rotateCube(float theta, Vector3 axis) { 
    // Rotate faces
    for (size_t i = 0; i < _topFace.size(); i++){
        _topFace[i].rotate(theta, axis);
        _bottomFace[i].rotate(theta, axis);
    }
    // Rotate centre point
    _position.rotate(theta, axis);
}
void Cube::translateCube(Vector3 translationVector) {
    for (size_t i = 0; i < _topFace.size(); i++) {
        _topFace[i] += translationVector;
        _bottomFace[i] += translationVector;
    }
}