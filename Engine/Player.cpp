#include "Player.h"

// Player constructor 
Player::Player(Vector2 position, std::vector<Vector2> points) : _position(position), _points(points) {}
// Player position Mutator and accessors
Vector2 Player::getPosition() { return _position; }
void Player::setPosition(Vector2 position) { _position = position; }

