#ifndef ENGINEUTILS_H
#define ENGINEUTILS_H

#include <iostream>
#include <vector>
#include "N5110.h"

// Coordinate class for LCD
class Point2D {
    public:
        int x;
        int y;
        Point2D(int x, int y);
};

class Circle {
    public:
        // Make public for easier access
        Point2D centre;
        int radius;

        Circle(Point2D c, int r);
        // Draws circle (passes to existing method)
        void draw(N5110 &screen);
        // Circle collider
        bool isCollidingWith(Circle other_circle);

};

// Vector2 works with floats (used for 2D rotations and maths) - use Point2D for screen coordinates
class Vector2 {
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x_, float y_);
        [[nodiscard]] float magnitude() const;
        [[nodiscard]] float dot(Vector2 rhs) const;
        void rotate(float angle);
        void print();

        Vector2 operator+(Vector2 obj) const;
        void operator+=(Vector2 obj);
        Vector2 operator-(Vector2 obj) const;
        void operator-=(Vector2 obj );
        Vector2 operator*(float scalar) const;
        void operator*=(float scalar);
        Vector2 operator/(float scalar) const;
        void operator/=(float scalar);
};

Vector2 operator*(float scalar, Vector2 obj);

Point2D Vector2ToPoint2D(Vector2 vec);

// Class for 3D coordinates 
class Vector3 {
    public:
        float x;
        float y;
        float z;

        Vector3();
        Vector3(float x_, float y_, float z_);
        // Vector maths functions
        [[nodiscard]] float magnitude() const;
        [[nodiscard]] float dot(Vector3 rhs) const;
        [[nodiscard]] Vector3 cross(Vector3 rhs) const;
        void rotate(float t_degrees, Vector3 axis);
        void normalise();
        // Vector operator overloading
        // TODO - add comparison operators and << for printing
        Vector3 operator+(Vector3 obj) const;
        void operator+=(Vector3 obj);
        Vector3 operator-(Vector3 obj) const;
        Vector3 operator-() const;
        void operator-=(Vector3 obj );
        Vector3 operator*(float scalar) const;
        void operator*=(float scalar);
        Vector3 operator/(float scalar) const;
        void operator/=(float scalar);
        // Print out vector in readable format
        void print() const;
};

Vector3 operator*(float scalar, Vector3 obj);

// Projection (orthographic) function for single point
Point2D Vector3ToPoint2D(Vector3 vertex);

class Quaternion {
    public:
        float s;
        Vector3 v;
        // Constructors
        Quaternion();
        Quaternion(float s_, Vector3 v_);
        // Quaternion functions
        [[nodiscard]] float magnitude() const;
        void normalise();
        [[nodiscard]] Quaternion inverse() const;
        [[nodiscard]] float dot(Quaternion rhs) const;

        // TODO - implement SLERP for interpolating between rotations
    
        // Operator overloading for Quaternions:

        // Addition and subtraction operations
        Quaternion operator+(Quaternion obj) const;
        void operator+=(Quaternion obj);
        Quaternion operator-(Quaternion obj) const;
        void operator-=(Quaternion obj);
        // Multiplication/Division operations
        Quaternion operator*(Quaternion rhs) const;
        Quaternion operator*(float scalar) const;
        Quaternion operator/(float scalar) const;
};

Quaternion operator*(float scalar, Quaternion rhs);

#endif