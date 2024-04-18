//
// Created by Harry Brenton on 04/03/2024.
//

#ifndef VECTOR2_H
#define VECTOR2_H

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

#endif //VECTOR2_H