//
// Created by Harry Brenton on 05/03/2024.
//

#include "Vector3.h"
#include "Quaternion.h"
#include <cmath>

const float pi = 3.141592;

// Default constructor initialises Vector3 with {0, 0, 0}
Vector3::Vector3() : x(0), y(0), z(0) {}

// Generic constructor
Vector3::Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

// Magnitude of Vector3
float Vector3::magnitude() const { return sqrt(x * x + y * y + z * z); }

// Dot product of two Vector3 objects
float Vector3::dot(Vector3 rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z;}

// Normalise vector
void Vector3::normalise() {
    *this /= this->magnitude();
}

// Cross product of two vectors (argument is RHS)
Vector3 Vector3::cross(Vector3 rhs) const {
    return {y * rhs.z - z * rhs.y,  // {x
            z * rhs.x - x * rhs.z,  //  y
            x * rhs.y - y * rhs.x}; //  z}
}

// TODO Not the most efficient implementation of this - maths can be simplified but will do for now
Vector3 Vector3::rotate(float t_degrees, Vector3 axis) {
    float t_rad = t_degrees*pi/180; // Convert to radians
    Quaternion vec = {0, (*this)}; // Create a pure quaternion from current Vector3
    axis.normalise(); 
    Quaternion rotationQuaternion(cosf(t_rad/2), sinf(t_rad/2)*axis);
    Quaternion result = rotationQuaternion * vec * rotationQuaternion.inverse();
    return {result.v.x, result.v.y, result.v.z};
}

// -------------------------------
// Vector3 operator overloading
// -------------------------------

// Addition of two vectors
Vector3 Vector3::operator+(Vector3 obj) const {return {x + obj.x, y + obj.y, z + obj.z};}
void Vector3::operator+=(Vector3 obj) { x+=obj.x; y+=obj.y; z+=obj.z;}

// Subtraction of two vectors
Vector3 Vector3::operator-(Vector3 obj) const {return {x - obj.x, y - obj.y, z - obj.z};}
void Vector3::operator-=(Vector3 obj) { x-=obj.x; y-=obj.y; z-=obj.z;}
// Unary - operator
Vector3 Vector3::operator-() const  { return {-x, -y, -z}; }

// Scalar multiplication
Vector3 Vector3::operator*(float scalar) const {return {x * scalar, y * scalar, z * scalar};}
void Vector3::operator*=(float scalar) { x*=scalar; y*=scalar; z*=scalar;}
Vector3 operator*(float scalar, Vector3 obj) {return {scalar * obj.x, scalar * obj.y, scalar * obj.z};}
// Scalar Division
Vector3 Vector3::operator/(float scalar) const {return {x / scalar, y / scalar, z / scalar};}
void Vector3::operator/=(float scalar) { x/=scalar; y/=scalar; z/=scalar;}

// Print Vector3 object
void Vector3::print() const{
    std::cout << "{" << x << ", " << y << ", " << z << "}";
}