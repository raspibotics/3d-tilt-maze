#ifndef ENGINEMATH_H
#define ENGINEMATH_H

#include <iostream>

// Take integers only as these relate to coordinates on the LCD screen 
class Vector2 {
    public:
        int x;
        int y;

        Vector2();
        Vector2(int x_, int y_);
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