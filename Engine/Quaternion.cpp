//
// Created by Harry Brenton on 05/03/2024.
//

#include "Quaternion.h"
#include <cmath>

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

// -------------------------------
// Quaternion operator overloading
// -------------------------------

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