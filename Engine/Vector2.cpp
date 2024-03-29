//
// Created by Harry Brenton on 05/03/2024.
//

#include "Vector2.h"
#include <cmath>

const float pi = 3.141592;

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

float Vector2::magnitude() const { return sqrt(x*x + y*y); }

float Vector2::dot(Vector2 rhs) const { return x*rhs.x + y*rhs.y; }

void Vector2::rotate(float angle) {
    angle *= pi/180;
    x = (x*cos(angle) - y*sin(angle));
    y = (x*sin(angle) + y*cos(angle));
}

Vector2 Vector2::operator+(Vector2 obj) const { return {x+obj.x, y+obj.y}; }
void Vector2::operator+=(Vector2 obj) { x+= obj.x; y+= obj.y; }
void Vector2::operator-=(Vector2 obj) { x-= obj.x; y-= obj.y; }
Vector2 Vector2::operator*(float scalar) const { return {scalar*x, scalar*y}; }
Vector2 Vector2::operator/(float scalar) const { return {x/scalar, y/scalar}; }
void Vector2::operator/=(float scalar) { x/=scalar; y/=scalar; }
Vector2 Vector2::operator-(Vector2 obj) const { return {x-obj.x, y-obj.y}; }
void Vector2::operator*=(float scalar) { x*=scalar; y*=scalar; }
Vector2 operator*(float scalar, Vector2 obj) { return {scalar * obj.x, scalar * obj.y}; }