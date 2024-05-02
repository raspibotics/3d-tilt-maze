#include "EngineUtils.h"
#include <cmath>
#include <vector>

const float pi = 3.141592;

/* ------------------------------ 
   POINT2D IMPLEMENTATION - Use for coords
--------------------------------- */
Point2D::Point2D(int x, int y) : x(x), y(y) {}

/* ------------------------------ 
   VECTOR2 IMPLEMENTATION - Use for vector maths then cast to Point2D
--------------------------------- */
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}
float Vector2::magnitude() const { return sqrt(x*x + y*y); }
float Vector2::dot(Vector2 rhs) const { return x*rhs.x + y*rhs.y; }

void Vector2::rotate(float angle) {
    angle *= pi/180;
    x = (x*cosf(angle) - y*sinf(angle));
    y = (x*sinf(angle) + y*cosf(angle));
}

void Vector2::print() { std::cout << "{" <<  x << ", " << y << "}" << "\n"; }

Vector2 Vector2::operator+(Vector2 obj) const { return {x+obj.x, y+obj.y}; }
void Vector2::operator+=(Vector2 obj) { x+= obj.x; y+= obj.y; }

Vector2 Vector2::operator-(Vector2 obj) const { return {x-obj.x, y-obj.y}; }
void Vector2::operator-=(Vector2 obj) { x-= obj.x; y-= obj.y; }

void Vector2::operator*=(float scalar) { x*=scalar; y*=scalar; }
Vector2 operator*(float scalar, Vector2 obj) { return {scalar * obj.x, scalar * obj.y}; }
Vector2 Vector2::operator*(float scalar) const { return {scalar*x, scalar*y}; }

Vector2 Vector2::operator/(float scalar) const { return {x/scalar, y/scalar}; }
void Vector2::operator/=(float scalar) { x/=scalar; y/=scalar; }

/* ------------------------------ 
   VECTOR3 IMPLEMENTATION
--------------------------------- */
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
void Vector3::rotate(float t_degrees, Vector3 axis) {
    float t_rad = t_degrees*pi/180; // Convert to radians
    Quaternion vec = {0, (*this)}; // Create a pure quaternion from current Vector3
    axis.normalise(); 
    Quaternion rotationQuaternion(cosf(t_rad/2), sinf(t_rad/2)*axis);
    Quaternion result = rotationQuaternion * vec * rotationQuaternion.inverse();
    x = result.v.x; y = result.v.y; z = result.v.z;
}
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

/* ------------------------------ 
   QUATERNION (Vector4) IMPLEMENTATION
--------------------------------- */
Quaternion::Quaternion() : s(0), v() {}
Quaternion::Quaternion(float s_, Vector3 v_) : s{s_}, v(v_) {}

// Quaternion functions
float Quaternion::magnitude() const { return sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z); }
void Quaternion::normalise() {s/=magnitude(); v/=magnitude();}

// Returns a Quaternion with the inverse of the current object 
Quaternion Quaternion::inverse() const {
    Quaternion conjugate = {s, -v};
    return {conjugate/powf(magnitude(), 2)};
}

// Dot product of Quaternion
float Quaternion::dot(Quaternion rhs) const {
    return s*rhs.s + v.x*rhs.v.x + v.y*rhs.v.y + v.z*rhs.v.z;
}

// Addition and subtraction rules
Quaternion Quaternion::operator+(Quaternion obj) const { return {s+obj.s, v+obj.v}; }
void Quaternion::operator+=(Quaternion obj) { s+=obj.s; v+=obj.v; }
Quaternion Quaternion::operator-(Quaternion obj) const { return {s-obj.s, v-obj.v}; }
void Quaternion::operator-=(Quaternion obj) { s-=obj.s; v-=obj.v; }

// scalar * Quaternion multiplication rules
Quaternion Quaternion::operator*(float scalar) const { return {s*scalar, v*scalar}; }
Quaternion operator*(float scalar, Quaternion rhs) { return {scalar*rhs.s, scalar*rhs.v}; }
Quaternion Quaternion::operator/(float scalar) const { return {s/scalar, v/scalar}; }
// Quaternion * Quaternion multiplication rules

// TODO - this expression can be expanded and simplified to reduce computation
Quaternion Quaternion::operator*(Quaternion rhs) const {
    return {s*rhs.s-v.dot(rhs.v),
            s*rhs.v + rhs.s*v + v.cross(rhs.v)};
}