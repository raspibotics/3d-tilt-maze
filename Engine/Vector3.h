//
// Created by Harry Brenton on 01/03/2024.
//

#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

namespace Engine {

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

}



#endif //VECTOR3_H
