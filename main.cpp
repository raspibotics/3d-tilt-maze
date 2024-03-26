#include "Quaternion.h"
#include "mbed.h"
#include <vector>
#include <iostream>

// Include Game Engine
#include "Engine.h"

// main() runs in its own thread in the OS
int main() {
    Vector3 v = {3,4,5};
    std::cout << "Vector before rotation: " << "\n";
    v.print();
    std::cout << "\n";

    Vector3 axis = {2,3,4};
    std::cout << "Vector after rotation around axis ";
    axis.print();
    std::cout << "\n";

    v.rotate(21.0, {5,4,3});
    v.print();
    
    // Create a camera
    Camera mainCamera({0,0,10});

    // Define a unit cube
    std::vector<Vector3> cube = {
        {0,0,0}, {1,0,0}, {0,0,1}, {1,0,1}, 
        {0,1,0}, {1,1,0}, {0,1,1}, {1,1,1}
    };

    mainCamera.renderObject3D(cube);
    // TODO Create an interpolation method
}