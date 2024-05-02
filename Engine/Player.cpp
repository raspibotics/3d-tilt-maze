#include "Player.h"

// Player constructor 
Player::Player(Vector2 position) : _position(position) {}
// Player position Mutator and accessors
Vector2 Player::getPosition() { return _position; }
void Player::setPosition(Vector2 position) { _position = position; }

bool Player::getAlive() { return _alive; }
void Player::setAlive(bool status) { _alive = status; }


// Can draw any single loop polygon - should be ok to represent a simple player
void Player::drawPlayer(N5110 &screen) {
    // Same method as drawing cube
    for (size_t i = 0; i < _points.size(); i++) {
        Vector2 currentVertex = _points[i]+_position;
        Vector2 nextVertex = _points[(i + 1) % _points.size()]+_position; // Next vertex (wrap around for last vertex)
        screen.drawLine(currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y, 1);
     }
}

void Player::rotatePlayer(float angle) {  
    // rotate all points in player
    for (size_t i = 1; i < _points.size(); i++) {
        (_points[i]+_position).rotate(angle);
    }
}