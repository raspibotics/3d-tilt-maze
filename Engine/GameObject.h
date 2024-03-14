//
// Created by Harry Brenton on 04/03/2024.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <utility>
#include <string>

// Generic 3D GameObject class - Primitive types such as Box can inherit from this class
template <typename T> class GameObject {
    protected:
        std::string _name;
        T _position;
    public:
        GameObject(std::string name, T position);
        // Accessor member functions
        std::string getName();
        T getPosition();
        // Mutator member functions
        void setName(std::string name);
        void setPosition(T position);
};

template <typename T>
GameObject<T>::GameObject(std::string name, T position) : _name(std::move(name)), _position(position) {}

// Accessor member functions
template <typename T> std::string GameObject<T>::getName() { return _name; }
template <typename T> T GameObject<T>::getPosition() { return _position; }

// Mutator member functions
template <typename T> void GameObject<T>::setName(std::string name) { _name = std::move(name); }
template <typename T> void GameObject<T>::setPosition(T position) { _position = position; }

#endif //GAME_OBJECT_H
