#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

namespace Engine { 

    // Templated GameObject should take Vector2 or Vector3 to act as a 2D or 3D GameObject
    // meant to act as a base class for common in game objects e.g cube, square etc.
     template <typename T> class GameObject {
        protected:
            std::string _name; 
            T _position;
        public: 
            // Constructors
            GameObject(std::string name, T position);

            // Accessors and mutators
            std::string getName();
            T getPosition(); 
            void setName(std::string new_name);
            void setPosition(T new_pos);
        };

}

using namespace Engine;

// Constructor
template <typename T> 
GameObject<T>::GameObject(std::string name, T position) :  _name(name), _position(position) {} 
// Get name of GameObject
template <typename T>  std::string GameObject<T>::getName() { return _name; }
// Get position of GameObject
template<typename T> T GameObject<T>::getPosition() { return _position; }
// Set name of GameObject
template<typename T> void GameObject<T>::setName(std::string new_name) { _name = new_name; }
// Set position of GameObject
template<typename T> void GameObject<T>::setPosition(T new_pos) { _position = new_pos; }

#endif