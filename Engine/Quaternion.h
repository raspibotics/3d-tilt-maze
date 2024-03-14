//
// Created by Harry Brenton on 05/03/2024.
//

#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3.h"


namespace Engine {

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

}


#endif //QUATERNION_H
